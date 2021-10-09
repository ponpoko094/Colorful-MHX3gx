#include <3ds.h>

#include <CTRPluginFramework.hpp>

#include "cheats.hpp"
#include "libpon.hpp"
#include "offset.hpp"
#include "patch.hpp"
#include "team_and_conditions.hpp"

namespace CTRPluginFramework {

// This patch the NFC disabling the touchscreen when scanning an amiibo, which
// prevents ctrpf to be used
static void ToggleTouchscreenForceOn() {
  static u32 original = 0;
  static u32 *patchAddress = nullptr;

  if (patchAddress && original) {
    *patchAddress = original;
    return;
  }

  static const std::vector<u32> pattern = {
      0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000, 0xE5C40008, 0xE28DD03C,
      0xE8BD80F0, 0xE5D51001, 0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003};

  Result res;
  Handle processHandle;
  s64 textTotalSize = 0;
  s64 startAddress = 0;
  u32 *found;

  if (R_FAILED(svcOpenProcess(&processHandle, 16))) return;

  svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
  svcGetProcessInfo(&startAddress, processHandle, 0x10005);
  if (R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000,
                                     processHandle, (u32)startAddress,
                                     textTotalSize)))
    goto exit;

  found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

  if (found != nullptr) {
    original = found[13];
    patchAddress = (u32 *)PA_FROM_VA((found + 13));
    found[13] = 0xE1A00000;
  }

  svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
  svcCloseHandle(processHandle);
}

static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey) {
  if (entry != nullptr) {
    entry->Hotkeys += hotkey;
    entry->SetArg(new std::string(entry->Name()));
    entry->Name() += " " + hotkey.ToString();
    entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index) {
      std::string *name = reinterpret_cast<std::string *>(entry->GetArg());
      entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
    });
  }

  return (entry);
}

static MenuEntry *EntryWithHotkey(MenuEntry *entry,
                                  const std::vector<Hotkey> &hotkeys) {
  if (entry != nullptr) {
    for (const Hotkey &hotkey : hotkeys) entry->Hotkeys += hotkey;
  }

  return (entry);
}

static MenuEntry *EnableEntry(MenuEntry *entry) {
  if (entry != nullptr) {
    entry->SetArg(new std::string(entry->Name()));
    entry->Enable();
  }
  return (entry);
}

// This function is called before main and before the game starts
// Useful to do code edits safely
void PatchProcess(FwkSettings &settings) {
  ToggleTouchscreenForceOn();

  // プラグインの設定
  // アクションリプレイ
  settings.AllowActionReplay = true;
  // サーチ
  settings.AllowSearchEngine = true;
  // 起動時間
  settings.WaitTimeToBoot = Seconds(3);

  // UIの色
  // テキストの色
  // settings.WindowTitleColor = Color(colorUiWindowTitle);
  // タイトルの色
  // settings.MainTextColor = Color(colorUiMainText);
  // 普通のメニューの色
  // settings.MenuSelectedItemColor = Color(colorUiMenuSelectedItem);
  // ActionReplayとかの色
  // settings.MenuUnselectedItemColor = Color(colorUiMenuUnselectedItem);
  // 背景の色
  // settings.BackgroundMainColor = Color(colorUiBackgroundMain);
  // 背景の細線の色
  // settings.BackgroundSecondaryColor = Color(colorUiBackgroundSecondary);
  // 背景の枠線の色
  // settings.BackgroundBorderColor = Color(colorUiBackgroundBorder);

  // キーボードの色
  // キーボードの背景の色
  // settings.Keyboard.Background = Color(colorKeyboardBackground);
  // キーの色
  // settings.Keyboard.KeyBackground = Color(colorKeyboardKeyBackground);
  // 押された時のキーの背景の色
  // settings.Keyboard.KeyBackgroundPressed =
  // Color(colorKeyboardKeyBackgroundPressed); キー数字の色
  // settings.Keyboard.KeyText = Color(colorKeyboardKeyText);
  //押された時のキーの数字の色
  // settings.Keyboard.KeyTextPressed = Color(colorKeyboardKeyTextPressed);
  // カーソルの色
  // settings.Keyboard.Cursor = Color(colorKeyboardCursor);
  // 上に表示されてる数字の色
  // settings.Keyboard.Input = Color(colorKeyboardInput);

  // カスタムキーボードの色
  // カスタムキーボードの背景の色
  // settings.CustomKeyboard.BackgroundMain =
  // Color(colorCustomKeyboardBackgroundMain); カスタムキーボードの背景細線の色
  // settings.CustomKeyboard.BackgroundSecondary =
  // Color(colorCustomKeyboardBackgroundSecondary);
  // カスタムキーボードの枠線の色 settings.CustomKeyboard.BackgroundBorder =
  // Color(colorCustomKeyboardBackgroundBorder);
  // カスタムキーボードのメニューの色
  // settings.CustomKeyboard.KeyBackground =
  // Color(colorCustomKeyboardKeyBackground);
  // カスタムキーボードのメニューが押された時の色
  // settings.CustomKeyboard.KeyBackgroundPressed =
  // Color(colorCustomKeyboardKeyBackgroundPressed);
  // カスタムキーボードのキーの色
  // settings.CustomKeyboard.KeyText = Color(colorCustomKeyboardKeyText);
  // カスタムキーボードのキーが押された時の色
  // settings.CustomKeyboard.KeyTextPressed =
  // Color(colorCustomKeyboardKeyTextPressed); スクロールバーの背景の色
  // settings.CustomKeyboard.ScrollBarBackground =
  // Color(colorCustomKeyboardScrollBarBackground); スクロールバーの動く色
  // settings.CustomKeyboard.ScrollBarThumb =
  // Color(colorCustomKeyboardScrollBarThumb);
}

// This function is called when the process exits
// Useful to save settings, undo patchs or clean up things
void OnProcessExit() { ToggleTouchscreenForceOn(); }

// チートメニュー作成
void InitMenu(PluginMenu &menu) {
  const std::string stable = " : " << Color::Green << "安定";
  const std::string workInProgress = " : " << Color::Red << "作業中";

  MenuFolder *player = new MenuFolder("プレイヤー");
  {
    MenuFolder *statusV2 = new MenuFolder("ステータス変更");
    {
      *statusV2 += new MenuEntry("攻撃力変更" + stable, nullptr,
                                 AttackPowerOption, "攻撃力を変更できます。");
      *statusV2 += new MenuEntry("防御力変更" + stable, nullptr,
                                 DefencePowerOption, "防御力を変更できます。");
      *statusV2 += new MenuEntry("属性値変更" + stable, nullptr,
                                 AttributeOption, "属性値を変更できます。");
      *statusV2 += new MenuEntry("耐性値変更" + stable, nullptr,
                                 ResistanceOption, "耐性値を変更できます。");
    }
    *player += statusV2;

    MenuFolder *playerChange = new MenuFolder("プレイヤー情報変更");
    {
      MenuFolder *hunterArt = new MenuFolder("狩技変更");
      {
        *hunterArt +=
            new MenuEntry("狩技1番目変更" + stable, nullptr, HunterArt1Change,
                          "狩技の1番目を変更します。");
        *hunterArt +=
            new MenuEntry("狩技2番目変更" + stable, nullptr, HunterArt2Change,
                          "狩技の2番目を変更します。");
        *hunterArt +=
            new MenuEntry("狩技3番目変更" + stable, nullptr, HunterArt3Change,
                          "狩技の3番目を変更します。");
      }
      *playerChange += hunterArt;

      MenuFolder *skin = new MenuFolder(
          "肌の色変更",
          "RGBの値は、\nbit.ly/GetRGB\nを見て、入力してください。");
      {
        *skin += new MenuEntry("肌の色R値変更" + stable, nullptr, SkinRedChange,
                               "肌の色の赤色を変更します。");
        *skin += new MenuEntry("肌の色G値変更" + stable, nullptr,
                               SkinGreenChange, "肌の色の緑色を変更します。");
        *skin += new MenuEntry("肌の色B値変更" + stable, nullptr,
                               SkinBlueChange, "肌の色の青色を変更します。");
        *skin += new MenuEntry("肌の色変更" + stable, nullptr, SkinColorChange,
                               "肌の色を変更します。");
      }
      *playerChange += skin;

      MenuFolder *meal = new MenuFolder("食事");
      {
        MenuFolder *mealFlag = new MenuFolder("フラグ");
        {
          *mealFlag += new MenuEntry("食事無限" + stable, MealInfinite,
                                     "食事が無限にできます。");
          *mealFlag +=
              new MenuEntry("高級お食事券効果付与" + stable, LuxuryCouponGrant,
                            "高級お食事券の効果が付与されます。");
          *mealFlag += new MenuEntry("よろず焼きの依頼無限" + stable,
                                     MeetRequestInfinite,
                                     "よろず焼きの依頼が無限にできます。");
        }
        *meal += mealFlag;

        MenuFolder *mealStatus = new MenuFolder("ステータス");
        {
          MenuFolder *mealStatusResistance = new MenuFolder("耐性");
          {
            *mealStatusResistance +=
                new MenuEntry("火耐性UP" + stable, MealFireResistanceUp,
                              "火耐性が上昇します。");
            *mealStatusResistance +=
                new MenuEntry("水耐性UP" + stable, MealWaterResistanceUp,
                              "水耐性が上昇します。");
            *mealStatusResistance +=
                new MenuEntry("雷耐性UP" + stable, MealThunderResistanceUp,
                              "雷耐性が上昇します。");
            *mealStatusResistance +=
                new MenuEntry("氷耐性UP" + stable, MealIceResistanceUp,
                              "氷耐性が上昇します。");
            *mealStatusResistance +=
                new MenuEntry("龍耐性UP" + stable, MealDragonResistanceUp,
                              "龍耐性が上昇します。");
          }
          *mealStatus += mealStatusResistance;

          *mealStatus +=
              new MenuEntry("体力UP" + stable, MealHpUp, "体力が上昇します。");
          *mealStatus += new MenuEntry("スタミナUP" + stable, MealStaminaUp,
                                       "スタミナが上昇します。");
          *mealStatus += new MenuEntry("攻撃力UP" + stable, MealAttackPowerUp,
                                       "攻撃力が上昇します。");
          *mealStatus += new MenuEntry("防御力UP" + stable, MealDefencePowerUp,
                                       "防御力が上昇します。");
        }
        *meal += mealStatus;

        *meal += new MenuEntry("スキル" + stable, nullptr, MealSkillChange,
                               "食事スキルを変更します。");
      }
      *playerChange += meal;

      *playerChange += new MenuEntry("声変更" + stable, nullptr,
                                     PlayerVoiceChange, "声を変更します。");
      *playerChange +=
          new MenuEntry("目の色変更" + stable, nullptr, PlayerEyeColorChange,
                        "目の色を変更します。");
      *playerChange +=
          new MenuEntry("インナー変更" + stable, nullptr, PlayerInnerChange,
                        "インナーを変更します。");
      *playerChange += new MenuEntry("性別変更" + stable, nullptr,
                                     PlayerGenderChange, "性別を変更します。");
      *playerChange +=
          new MenuEntry("狩猟スタイル変更" + stable, nullptr,
                        PlayerHuntingStyleChange, "狩猟スタイルを変更します。");
      *playerChange +=
          new MenuEntry("髪型変更" + stable, nullptr, PlayerHearStyleChange,
                        "髪型を変更します。");
      *playerChange += new MenuEntry("顔変更" + stable, nullptr,
                                     PlayerFaceChange, "顔を変更します。");
      *playerChange +=
          new MenuEntry("メイク変更" + stable, nullptr, PlayerCosmeticsChange,
                        "メイクを変更します。");
    }
    *player += playerChange;

    *player += new MenuEntry("攻撃力倍率変更" + stable, nullptr,
                             PlayerAttackPowerMagnificationOption,
                             "攻撃力の倍率を変更します。");
    *player += new MenuEntry("防御力倍率変更" + stable, nullptr,
                             PlayerDefencePowerMagnificationOption,
                             "防御力の倍率を変更します。");
    *player += new MenuEntry("速度変更" + stable, nullptr, PlayerSpeedOption,
                             "速度を変更します。");
    *player +=
        new MenuEntry("プレイヤー座標移動" + stable, PlayerCoordinateModifier,
                      "A+十字キーで移動できます。");
    *player += new MenuEntry(
        "ムーンジャンプ" + stable, PlayerMoonJump,
        "R+Bでジャンプできます。\n"
        "上がり続けるにはリピートムーブもオンにして、R+B+Yを押してください。");
    *player +=
        new MenuEntry("保存式テレポート" + stable, Teleport,
                      "X + → 現在位置を読み込む。\nX + ← 現在位置に書き込む");
    *player += new MenuEntry(
        "他プレイヤーストーカー" + stable, Stalker,
        "R+十字キーで追跡設定ができます。\nR↑ P1を追跡有効\n"
        "R+→ P2を追跡有効\nR+↓ P3を追跡有効\nR+←で追跡無効にできます。");
    *player += new MenuEntry("リピートムーブ" + stable, Repeatmove,
                             "B+Yで動きを繰り返します。");
    *player += new MenuEntry("狩技解放" + stable, HunterArtRelease,
                             "狩技を全て解放します。");
    *player += new MenuEntry("腹減り無効" + stable, HungryInvalid,
                             "時間経過でスタミナが減らなくなります。");
    *player +=
        new MenuEntry("プレイヤーサイズ変更" + stable, nullptr,
                      HunterSizeOption, "ハンターのサイズを変更できます。");
    *player += new MenuEntry("HP無限" + stable, nullptr, InfiniteHP,
                             "HPを無限にします。");
    *player +=
        new MenuEntry("無敵" + stable, nullptr, Invincible, "無敵になります。");
    *player += new MenuEntry("スーパーアーマー" + stable, nullptr, SuperArmor,
                      "スーパーアーマーになります。\n"
                             "オンにした後オフにすると被弾したときに"
                             "のけぞりのモーションになります。");
    *player += new MenuEntry("スタミナ無限" + stable, nullptr, InfiniteStamina,
                             "スタミナを無限にします。");
    *player += new MenuEntry("狩技ゲージ無限" + stable, nullptr,
                             InfiniteHunterArt, "狩技ゲージが無限になります。");
    *player += new MenuEntry("全スタイルで狩技3つ装着可能" + stable, nullptr,
                             Always3HunterArtEquip,
                             "全スタイルで狩技を3つ装着可能になります。");
    *player += new MenuEntry("常時地図表示" + stable, nullptr, AlwaysDisplayMap,
                             "常に地図を表示します。");
    *player +=
        new MenuEntry("常にモンスターペイント" + stable, nullptr, AlwaysPaint,
                      "常にマップにモンスターが表示されます。");
    *player += new MenuEntry("スピードハック" + stable, nullptr, SpeedHack,
                             "速度の変更ができます。");
    *player +=
        new MenuEntry("クエスト中スピードハック" + stable, nullptr,
                      InQuestSpeedHack, "クエスト中での速度を変更できます。");
    *player +=
        new MenuEntry("走った時にムーンウォーク" + stable, nullptr,
                      IfRunMoonWalk, "走った時にムーンウォークをします。");
    *player += new MenuEntry(
        "プレイヤー名前変更" + stable, nullptr, HunterNameChange,
        "定型文では1ページ目の一番左下にある定型文を名前にコピーします。\n"
        "キーボードでは、メニュー内で直接変更することができます。\n"
        "変換候補変換の改行やタブが使えます。");
  }
  menu += player;

  MenuFolder *item = new MenuFolder("アイテム");
  {
    MenuFolder *equipment = new MenuFolder("装備");
    {
      MenuFolder *amulet =
          new MenuFolder("護石編集",
                         "編集したい護石を、装備BOX14ページ目の一番右下に"
                         "移動させてください。\n"
                         "14ページ目がない場合は、アイテムフォルダにある"
                         "「ボックス1400個に拡張」をオンにしてください。");
      {
        *amulet += new MenuEntry("新護石作成" + stable, nullptr, AmuletCreate,
                                 "新たに護石を作成できます。");
        *amulet += new MenuEntry("護石種類変更" + stable, nullptr,
                                 AmuletTypeChange, "護石の種類を変更します。");
        *amulet += new MenuEntry("スキル変更" + stable, nullptr,
                                 AmuletSkillChange, "スキルを変更します。");
        *amulet += new MenuEntry("スキルポイント変更" + stable, nullptr,
                                 AmuletSkillPointChange,
                                 "スキルポイントを変更します。");
        *amulet += new MenuEntry("スロット数変更" + stable, nullptr,
                                 AmuletSlotChange, "スロット数を変更します。");
      }
      *equipment += amulet;

      MenuFolder *insect =
          new MenuFolder("猟虫編集",
                         "編集したい猟虫がついている操虫棍を、装備BOX14ページ目"
                         "の一番下の右から4番目に移動させてください。\n"
                         "14ページ目がない場合は、アイテムフォルダにある「ボッ"
                         "クス1400個に拡張」をオンにしてください。");
      {
        *insect += new MenuEntry("猟虫種類変更" + stable, nullptr,
                                 InsectTypeChange, "猟虫の種類を変更します。");
        *insect +=
            new MenuEntry("猟虫レベル変更" + stable, nullptr, InsectLevelChange,
                          "猟虫のレベルを変更します。");
        *insect +=
            new MenuEntry("猟虫パワー補正変更" + stable, nullptr,
                          InsectPowerChange, "猟虫のパワー補正を変更します。");
        *insect += new MenuEntry("猟虫ウェイト補正変更" + stable, nullptr,
                                 InsectWeightChange,
                                 "猟虫のウェイト補正を変更します。");
        *insect += new MenuEntry("猟虫スタミナ補正変更" + stable, nullptr,
                                 InsectStaminaChange,
                                 "猟虫のスタミナ補正を変更します。");
        *insect += new MenuEntry("猟虫火属性変更" + stable, nullptr,
                                 InsectFireAttributeChange,
                                 "猟虫の火属性を変更します。");
        *insect += new MenuEntry("猟虫水属性変更" + stable, nullptr,
                                 InsectWaterAttributeChange,
                                 "猟虫の水属性を変更します。");
        *insect += new MenuEntry("猟虫雷属性変更" + stable, nullptr,
                                 InsectThunderAttributeChange,
                                 "猟虫の雷属性を変更します。");
        *insect += new MenuEntry("猟虫氷属性変更" + stable, nullptr,
                                 InsectIceAttributeChange,
                                 "猟虫の氷属性を変更します。");
        *insect += new MenuEntry("猟虫龍属性変更" + stable, nullptr,
                                 InsectDragonAttributeChange,
                                 "猟虫の龍属性を変更します。");
      }
      *equipment += insect;

      *equipment += new MenuEntry(
          "他プレイヤーの装備コピー" + stable, nullptr,
          OtherPlayerEquipmentCopy,
          "コピーしたいプレイヤーが猫の場合、コピーしないでください。");
    }
    *item += equipment;

    *item += new MenuEntry("爆弾を無限に置ける" + stable, InfiniteBombPut,
                           "見た目だけです。");
    *item += new MenuEntry("たんほれアイテムセット" + stable, TanhoreItemSet,
                           "ポーチの\n"
                           "1枠目を 燃石炭\n"
                           "2枠目を ネコタクチケット\n"
                           "3枠目を モドリ玉\n"
                           "にします。");
    *item += new MenuEntry("所持金最大" + stable, nullptr, MoneyChange,
                           "所持金を変更できます。");
    *item +=
        new MenuEntry("龍歴院ポイント最大" + stable, nullptr,
                      WycademyPointChange, "龍歴院ポイントを変更できます。");
    *item +=
        new MenuEntry("アイテム&弾丸無限" + stable, nullptr, InfiniteItemAmmo,
                      "アイテムと弾丸を無限にします。\n"
                      "しゃがみの弾は無限になりません。");
    *item +=
        new MenuEntry("素材無しで調合可能" + stable, nullptr,
                      NoMaterialCompound, "素材無しで調合を可能にします。");
    *item += new MenuEntry("運搬物を持たずにポーチに入れる" + stable, nullptr,
                           CargoPutInPorch, "運搬物がポーチに入ります。");
    *item += new MenuEntry("採取無限" + stable, nullptr, InfiniteCollect,
                           "採集ポイントで無限に採取ができます。");
    *item += new MenuEntry("装備を素材無しで作れる" + stable, nullptr,
                           NoMaterialEquipmentCreate,
                           "素材なしで装備生産をすることができます。");
    *item +=
        new MenuEntry("装備欄全て解放" + stable, nullptr, EquipmentAllRelease,
                      "装備生産リストを全て解放します。");
    *item +=
        new MenuEntry("全てのアイテム販売" + stable, nullptr, AllItemSold,
                      "全てのアイテムがギルドストアや雑貨屋に売り出されます。");
    *item += new MenuEntry("ボックス1400個に拡張" + stable, nullptr,
                           ItemBox1400Expansion,
                           "ボックスのページを1400個に拡張します。");
    *item += new MenuEntry("持てるアイテム99個" + stable, nullptr, HaveItem99,
                           "持てるアイテムの最大数を99個にします。");
    *item += new MenuEntry("アイテムボックス編集" + stable, nullptr,
                           ItemBoxEdit, "アイテムボックスの編集をします。");
    *item +=
        new MenuEntry("アイテムマイセットをポーチにコピー" + stable, nullptr,
                      MySetToPorchItemCopy,
                      "アイテムマイセットに登録されているアイテムを、アイテムポ"
                      "ーチにコピーします。");
    *item += new MenuEntry(
        "納品アイテムをポーチにコピー" + stable, nullptr,
        DeliveryItemToPorchCopy,
        "納品アイテムを、アイテムポーチの1番目と2番目にコピーします。\n"
        "空きを作ってください。");
    *item +=
        new MenuEntry("ポーチのアイテム全消去" + stable, nullptr, PorchAllClear,
                      "ポーチのアイテムを全消去します。\n"
                      "消せないアイテムや、ボックスにしまえないアイテムが"
                      "あるときに実行してください。");
    *item += new MenuEntry("特殊許可チケットの数変更" + stable, nullptr,
                           SpecialPermitQuestTicketChange,
                           "特殊許可チケットの枚数を変更します。");
  }
  menu += item;

  MenuFolder *weapon = new MenuFolder("武器");
  {
    MenuFolder *weaponType = new MenuFolder("武器別チート");
    {
      MenuFolder *gunlance = new MenuFolder("ガンランスチート");
      {
        *gunlance +=
            new MenuEntry("ヒートゲージ固定" + stable, nullptr,
                          GunlanceHeatGageOption, "ヒートゲージを固定します。");
        *gunlance +=
            new MenuEntry("ガンランスの弾無限" + stable, GunlanceAmmoInfinite,
                          "ガンランスの弾を無限にします。");
        *gunlance += new MenuEntry("オーバーヒート無効" + stable,
                                   GunlanceInvalidOverHeat,
                                   "オーバーヒートを無効にします。");
      }
      *weaponType += gunlance;

      MenuFolder *insectGlaive = new MenuFolder("操虫棍チート");
      {
        *insectGlaive += new MenuEntry("常時トリプルアップ" + stable,
                                       InsectGlaiveAlwaysTripleUp,
                                       "常時トリプルアップになります。");
        *insectGlaive += new MenuEntry("虫のスタミナ無限" + stable,
                                       InsectGlaiveInsectStaminaInfinite,
                                       "虫のスタミナが無限になります。");
      }
      *weaponType += insectGlaive;

      MenuFolder *bowgun = new MenuFolder("ボウガンチート");
      {
        *bowgun +=
            new MenuEntry("ボウガンの弾無限" + stable, BowgunAmmoInfinite,
                          "ボウガンの弾が無限になります。");
        *bowgun +=
            new MenuEntry("しゃがみの弾無限" + stable, BowgunCrouchingShot,
                          "しゃがみ撃ちの弾が無限になります。");
      }
      *weaponType += bowgun;
      *weaponType +=
          new MenuEntry("溜め段階固定" + stable, nullptr, ChageStageOption,
                        "大剣などの溜め段階を固定します。");
      *weaponType += new MenuEntry("武器ゲージ固定" + stable, WeaponGageFix,
                                   "太刀や双剣のゲージを固定します。");
      *weaponType +=
          new MenuEntry("チャージアックスビン固定" + stable, ChargeAxeBinFix,
                        "チャージアックスのビン数を固定します。");
      *weaponType += new MenuEntry("狩猟笛の全効果付与" + stable,
                                   HuntingHornAllEffectGrant,
                                   "反映されない効果があります。");
    }
    *weapon += weaponType;

    *weapon += new MenuEntry("属性値変更" + stable, nullptr,
                             AttributePointChange, "属性値を変更できます。");
    *weapon += new MenuEntry("モーション無し" + stable, nullptr, NoMotion,
                             "モーションを無くします。");
    *weapon += new MenuEntry("会心率100%" + stable, nullptr, CriticalRate100,
                             "会心率が100%になります。");
    *weapon +=
        new MenuEntry("ボウガン自動装填" + stable, nullptr, BowgunAutoReload,
                      "ボウガンの弾が自動で装填されます。");
    *weapon += new MenuEntry("斬れ味無限" + stable, nullptr, InfiniteSharpness,
                             "斬れ味が無限になります。");
    *weapon += new MenuEntry("斬れ味+2" + stable, nullptr, SharpnessPlus2,
                             "斬れ味レベル+2の効果を付与します。");
    *weapon += new MenuEntry("高速溜め短縮" + stable, nullptr, ChargeSpeedUp,
                             "大剣等の溜めが短縮されます。");
    *weapon += new MenuEntry("チャージゲージ最大" + stable, nullptr,
                             ChargeGageMax, "太刀等のゲージが最大になります。");
  }
  menu += weapon;

  MenuFolder *monster = new MenuFolder(
      "モンスター", "オンラインだとラグがあったり、使えない場合があります。");
  {
    MenuFolder *monsterDisplay = new MenuFolder("モンスター情報画面表示");
    {
      *monsterDisplay +=
          new MenuEntry("1番目のモンスターのHP表示" + stable, Monster1HpDisplay,
                        "1番目のモンスターのHPを画面上に表示します。");
      *monsterDisplay +=
          new MenuEntry("2番目のモンスターのHP表示" + stable, Monster2HpDisplay,
                        "2番目のモンスターのHPを画面上に表示します。");
      *monsterDisplay += new MenuEntry(
          "1番目のモンスターのサイズ倍率表示" + stable,
          Monster1SizeMagnificationDisplay,
          "1番目のモンスターのサイズ倍率を画面上に表示します。\n"
          "1.2付近がキンズサイズ、0.9付近がスモールサイズの目安です。");
      *monsterDisplay += new MenuEntry(
          "2番目のモンスターのサイズ倍率表示" + stable,
          Monster2SizeMagnificationDisplay,
          "2番目のモンスターのサイズ倍率を画面上に表示します。\n"
          "1.2付近がキングサイズ、0.9付近がスモールサイズの目安です。");
    }
    *monster += monsterDisplay;

    *monster += new MenuEntry("乗り成功" + stable, RideGageMax,
                              "ハンターの乗りゲージを最大にします。\nモンス"
                              "ターの乗りゲージが増えないようにします。");
    *monster +=
        new MenuEntry("モンスター座標移動" + stable, MonsterCoordinateModifier,
                      "1番目のモンスターはX+十字キーで操作できます。\n"
                      "2番目のモンスターはX+スライドパッドで操作できます。\n"
                      "操作したいモンスターと同じエリアにいてください。");
    *monster +=
        new MenuEntry("モンスターストーカー" + stable, MonsterStalker,
                      "1番目のモンスターはX+R+↑で追跡有効にできます。\n"
                      "2番目のモンスターはX+L+↑で追跡有効にできます。\n"
                      "X+R+↓で追跡停止できます。\n"
                      "追跡したいモンスターと同じエリアにいてください。");
    *monster += new MenuEntry(
        "モンスターリピートムーブ" + stable, nullptr, MonsterActionRepeatOption,
        "リピートムーブの挙動の変更と、操作のオンオフができます。\n"
        "1番目のモンスターはX+R+→で操作できます。\n"
        "2番目のモンスターはX+L+→で操作できます。\n"
        "操作したいモンスターと同じエリアにいてください。");
    *monster += new MenuEntry("1番目と2番目のモンスターの動き停止" + stable,
                              Monster1And2Stop,
                              "動き停止は、速度変更より優先されます。\n"
                              "当たり判定がなくなります。");
    *monster += new MenuEntry("1番目のモンスターのサイズ変更" + stable, nullptr,
                              Monster1SizeOption,
                              "1番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry("2番目のモンスターのサイズ変更" + stable, nullptr,
                              Monster2SizeOption,
                              "2番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry("1番目のモンスターの速度倍率変更" + stable,
                              nullptr, Monster1SpeedAttributeOption,
                              "1番目のモンスターの速度の変更ができます。");
    *monster += new MenuEntry("2番目のモンスターの速度倍率変更" + stable,
                              nullptr, Monster2SpeedAttributeOption,
                              "2番目のモンスターの速度の変更ができます。");
    *monster += new MenuEntry(
        "1番目と2番目のモンスター常時毒" + stable, Monster1And2AlwaysPoison,
        "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster +=
        new MenuEntry("1番目と2番目のモンスター常時麻痺" + stable,
                      Monster1And2AlwaysParalysis,
                      "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry(
        "1番目と2番目のモンスター常時睡眠" + stable, Monster1And2AlwaysSleep,
        "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster +=
        new MenuEntry("1番目と2番目のモンスター透明化" + stable, nullptr,
                      Monster1And2AlwaysInvisible,
                      "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry("瞬殺" + stable, nullptr, OneAttackKill,
                              "モンスターを瞬殺できます。");
  }
  menu += monster;

  MenuFolder *palico = new MenuFolder("ねこ");
  {
    MenuFolder *palicoEdit = new MenuFolder("ねこ編集");
    {
      *palicoEdit += new MenuEntry("ねこ選択" + stable, nullptr, PalicoChoice,
                                   "編集するねこを選択します。");
      *palicoEdit += new MenuEntry("装備サポート行動変更" + stable, nullptr,
                                   PalicoEquipmentSupportActionChanger,
                                   "ねこの装備サポート行動を変更します。");
      *palicoEdit += new MenuEntry("装備オトモスキル変更" + stable, nullptr,
                                   PalicoEquipmentSkillChanger,
                                   "ねこの装備オトモスキルを変更します。\n"
                                   "最大スキル枠を超えるとエラーになります。");
      *palicoEdit += new MenuEntry("習得サポート行動変更" + stable, nullptr,
                                   PalicoLearnSupportActionChanger,
                                   "ねこの習得サポート行動を変更します。");
      *palicoEdit += new MenuEntry("習得オトモスキル変更" + stable, nullptr,
                                   PalicoLearnSkillChanger,
                                   "ねこの習得オトモスキルを変更します。");

      MenuFolder *palicoAppearance = new MenuFolder("見た目");
      {
        MenuFolder *palicoAppearanceColor = new MenuFolder("見た目の色変更");
        {
          *palicoAppearanceColor += new MenuEntry(
              "毛色変更" + stable, nullptr, PalicoBodyHairColorChanger,
              "ねこの毛色を変更します。");
          *palicoAppearanceColor += new MenuEntry(
              "右目の色変更" + stable, nullptr,
              PalicoRightEyeColorChanger, "ねこの右目の色を変更します。");
          *palicoAppearanceColor += new MenuEntry(
              "左目の色変更" + stable, nullptr,
              PalicoLeftEyeColorChanger, "ねこの左目の色を変更します。");
          *palicoAppearanceColor += new MenuEntry(
              "インナーの色変更" + stable, nullptr,
              PalicoInnerColorChanger, "ねこのインナーの色を変更します。");
        }
        *palicoAppearance += palicoAppearanceColor;

        *palicoAppearance +=
            new MenuEntry("声変更" + stable, nullptr, PalicoVoiceChange,
                          "ねこの声を変更します。");
        *palicoAppearance +=
            new MenuEntry("目変更" + stable, nullptr, PalicoEyeChange,
                          "ねこの目を変更します。");
        *palicoAppearance +=
            new MenuEntry("インナー変更" + stable, nullptr, PalicoInnerChange,
                          "ねこのインナーを変更します。");
        *palicoAppearance +=
            new MenuEntry("毛並み変更" + stable, nullptr, PalicoFurCoatChange,
                          "ねこの毛並みを変更します。");
        *palicoAppearance +=
            new MenuEntry("耳変更" + stable, nullptr, PalicoEarChange,
                          "ねこの耳を変更します。");
        *palicoAppearance +=
            new MenuEntry("尻尾変更" + stable, nullptr, PalicoTailChange,
                          "ねこの尻尾を変更します。");
      }
      *palicoEdit += palicoAppearance;

      *palicoEdit +=
          new MenuEntry("経験値変更" + stable, nullptr,
                        PalicoExperienceChange, "ねこの経験値を変更します。");
      *palicoEdit +=
          new MenuEntry("レベル変更" + stable, nullptr,
                        PalicoLevelChange, "ねこのレベルを変更します。");
      *palicoEdit += new MenuEntry("サポート傾向変更" + stable, nullptr,
                                   PalicoSupportTrendChange,
                                   "ねこのサポート傾向を変更します。");
      *palicoEdit +=
          new MenuEntry("親密度変更" + stable, nullptr,
                        PalicoClosenessChange, "ねこの親密度を変更します。");
      *palicoEdit +=
          new MenuEntry("ターゲット変更" + stable, nullptr,
                        PalicoTargetChange, "ねこのターゲットを変更します。");
      *palicoEdit +=
          new MenuEntry("オトモコメント編集可能変更" + stable, nullptr,
                        PalicoCommentEditPossibleChange,
                        "ねこのオトモコメントを編集可能にするか選べます。");
      *palicoEdit += new MenuEntry("特別配信表示変更" + stable, nullptr,
                                   SpecialDeliveryDisplayChange,
                                   "ねこの特別配信の表示を変更します。");
      *palicoEdit += new MenuEntry(
          "名前変更" + stable, nullptr, PalicoNameChange,
          "ねこの名前を変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこの名前にコピーします"
          "。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
      *palicoEdit += new MenuEntry(
          "コメント変更" + stable, nullptr, PalicoCommentChange,
          "ねこのコメントを変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこのコメントにコピーし"
          "ます。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
      *palicoEdit += new MenuEntry(
          "名付け親変更" + stable, nullptr, PalicoGodParentChange,
          "ねこの名付け親を変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこの名付け親にコピーし"
          "ます。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
      *palicoEdit += new MenuEntry(
          "先代旦那さん変更" + stable, nullptr,
          PalicoPredecessorHusbandChange,
          "ねこの先代旦那さんを変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこの先代旦那さんにコピ"
          "ーします。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
    }
    *palico += palicoEdit;

    *palico += new MenuEntry(
        "ねこの攻撃力倍率変更" + stable, nullptr,
        PalicoAttackPowerMagnificationOption,
        "ねこの攻撃力の倍率を変更します。");
    *palico += new MenuEntry(
        "ねこの防御力倍率変更" + stable, nullptr,
        PalicoDefencePowerMagnificationOption,
        "ねこの防御力変更の倍率を変更します。");
    *palico += new MenuEntry(
        "ねこ吸収" + stable, PalicoAbsorption,
        "ねこをハンターに吸収させます。\n他プレイヤーからは見えません。");
    *palico += new MenuEntry("サポートゲージ最大" + stable,
                             ProwlerSupportGageMax,
                             "ニャンターのサポートゲージを最大にします。");
  }
  menu += palico;

  MenuFolder *other = new MenuFolder("その他");
  {
    MenuFolder *chat = new MenuFolder("チャット");
    {
      *chat += new MenuEntry("チャット無限" + stable, ChatInfinite,
                             "オンラインで赤文字を出現させなくします。");
      *chat += new MenuEntry("変換候補変換" + stable, ChatConversionChange,
                             "キーボードを開いて、Rを押しながら文字を打つ"
                             "ことで、変換候補の文字が変わります。");
      *chat += new MenuEntry(
          "変換候補変換対応文字一覧" + stable, nullptr, ChatConversionList,
          "変換対応文字が書かれています。\n"
          "変換しづらい文字や、改造でしか入力できない文字を入れています。");
    }
    *other += chat;

    MenuFolder *drunk =
        new MenuFolder("酔っぱらい", "クエスト中は酔っぱらえません。");
    {
      *drunk +=
          new MenuEntry("即酔っぱらい" + workInProgress, nullptr,
                        InstantDrunkOption, "酔っぱらいになるか変更できます。");
      *drunk += new MenuEntry("1回お酒を飲むと酔っぱらい" + workInProgress,
                              Drunk1, "1回お酒を飲むと酔っぱらいになります。");
    }
    *other += drunk;

    MenuFolder *hunterRank = new MenuFolder("ハンターランク");
    {
      *hunterRank +=
          new MenuEntry("ハンターランク変更" + workInProgress, nullptr,
                        HunterRankChange, "ハンターランクを変更できます。");
      *hunterRank += new MenuEntry(
          "ハンターランクポイント変更" + workInProgress, nullptr,
          HunterRankPointChange, "ハンターランクポイントを変更できます。");
    }
    *other += hunterRank;

    MenuFolder *fenyAndPugy = new MenuFolder("プーギー&フェニー");
    {
      *fenyAndPugy += new MenuEntry(
          "フェニー&プーギーの服変更" + workInProgress, nullptr,
          FenyAndPugyClothes, "フェニー&プーギーの服を変更できます。");
      *fenyAndPugy += new MenuEntry(
          "定型文でフェニー&プーギーの名前変更" + workInProgress, nullptr,
          FenyAndPugyNameChange,
          "1ページ目の一番左下にある定型文を名前にコピーします。\nフェニ"
          "ー&プーギーの名前を変更できます。");
    }
    *other += fenyAndPugy;

    MenuFolder *quest = new MenuFolder("クエスト");
    {
      *quest += new MenuEntry("クエストステータス変更" + workInProgress,
                              nullptr, QuestClearOption,
                              "クエストクリアか失敗を選択できます。");
      *quest += new MenuEntry("クエストクリア後即リザルト" + workInProgress,
                              QuestWaitSkip,
                              "クエストクリア後の待ち時間をスキップします。");
      *quest +=
          new MenuEntry("報酬画面スキップ" + workInProgress, QuestResultSkip,
                        "報酬受取の時間を0にし、スキップします。");
      *quest +=
          new MenuEntry("最大ダウン回数変更" + workInProgress, nullptr,
                        QuestDownMaxOption, "最大ダウン回数を変更できます。");
      *quest +=
          new MenuEntry("現在のダウン回数変更" + stable, nullptr,
                        QuestDownNowOption, "現在のダウン回数を変更します。");
      *quest += new MenuEntry(
          "クエスト残り時間表示" + workInProgress, QuestTimeDisplay,
          "QT = Quest Timeです。\n時:分:秒:フレーム\nと表示します。");
      *quest +=
          new MenuEntry("選択肢を固定" + stable, nullptr, SaveScreenOption,
                        "Rボタンを押すと固定できます。");
                              QuestTimeStop, "クエスト時間を停止します。");
      *quest += new MenuEntry(
          "全クエストクリア変更" + workInProgress, nullptr, AllQuestClearChange,
          "ストーリーに不具合が起きる可能性があります。\n予めバックアップ"
          "を取ったり、サブキャラクターで実行してください。");
    }
    *other += quest;

    MenuFolder *base = new MenuFolder("集会所");
    {
      MenuFolder *baseCreate = new MenuFolder("集会所を作る");
      {
        *baseCreate += new MenuEntry("ターゲット変更" + workInProgress, nullptr,
                                     BaseCreateTargetChange,
                                     "ターゲットを？？？？？にできます。");
        *baseCreate += new MenuEntry("クエスト形式変更" + workInProgress,
                                     nullptr, BaseCreateQuestTypeChange,
                                     "クエスト形式を変更できます。");
        *baseCreate +=
            new MenuEntry("募集HR下限変更" + workInProgress, nullptr,
                          BaseCreateRecruitmentHunterRankMinimumChange,
                          "募集HRの下限を変更できます。");
        *baseCreate +=
            new MenuEntry("募集HR上限変更" + workInProgress, nullptr,
                          BaseCreateRecruitmentHunterRankMaximumChange,
                          "募集HRの上限を変更できます。");
        *baseCreate += new MenuEntry("入室人数変更" + workInProgress, nullptr,
                                     BaseCreateEntryPeopleChange,
                                     "入室人数を変更できます。");
        *baseCreate += new MenuEntry("入室制限変更" + workInProgress, nullptr,
                                     BaseCreateEntryLimitChange,
                                     "入室制限を変更できます。");
        *baseCreate += new MenuEntry("パスワード有無変更" + workInProgress,
                                     nullptr, BaseCreatePasswordExistChange,
                                     "パスワードの有無を変更できます。");
        *baseCreate += new MenuEntry("募集文①変更" + workInProgress, nullptr,
                                     BaseCreateRecruitmentMessage1Change,
                                     "募集文①を変更できます。");
        *baseCreate += new MenuEntry("募集文②変更" + workInProgress, nullptr,
                                     BaseCreateRecruitmentMessage2Change,
                                     "募集文②を変更できます。");
        *baseCreate += new MenuEntry("募集文③変更" + workInProgress, nullptr,
                                     BaseCreateRecruitmentMessage3Change,
                                     "募集文③を変更できます。");
        *baseCreate += new MenuEntry("募集文④変更" + workInProgress, nullptr,
                                     BaseCreateRecruitmentMessage4Change,
                                     "募集文④を変更できます。");
      }
      *base += baseCreate;

      MenuFolder *baseSearch = new MenuFolder("集会所を探す");
      {
        *baseSearch +=
            new MenuEntry("ターゲット変更" + workInProgress, nullptr,
                          BaseSearchTargetChange, "ターゲットを変更できます。");
        *baseSearch += new MenuEntry("クエスト形式変更" + workInProgress,
                                     nullptr, BaseSearchQuestTypeChange,
                                     "クエスト形式を変更できます。");
        *baseSearch +=
            new MenuEntry("ホストHR下限変更" + workInProgress, nullptr,
                          BaseSearchHostHunterRankMinimumChange,
                          "ホストHRの下限を変更できます");
        *baseSearch +=
            new MenuEntry("ホストHR上限変更" + workInProgress, nullptr,
                          BaseSearchHostHunterRankMaximumChange,
                          "ホストHRの上限を変更できます");
        *baseSearch += new MenuEntry("クエスト中変更" + workInProgress, nullptr,
                                     BaseSearchInQuestChange,
                                     "クエスト中を変更できます。");
        *baseSearch += new MenuEntry("パスワード有無変更" + workInProgress,
                                     nullptr, BaseSearchPasswordExistChange,
                                     "パスワードの有無を変更できます。");
      }
      *base += baseSearch;
    }
    *other += base;

    *other += new MenuEntry("プレイヤーの現在座標表示" + stable,
                            DisplayPlayerCoordinate,
                            "プレイヤーの現在座標を表示します。");
    *other += new MenuEntry("クエスト中の視野角変更" + stable, nullptr,
                            ViewingAngleOption,
                            "視野角を変更します。\n(画面酔い注意)");
    *other += new MenuEntry("視野角変更改良版" + workInProgress, nullptr,
                            ViewingAngleChangeV2, "視野の倍率を変更できます。");
    *other += new MenuEntry("武器サイズ変更" + workInProgress, nullptr,
                            WeaponSizeChange, "武器のサイズを変更できます。");
    *other += new MenuEntry("画面の明るさ変更" + workInProgress, nullptr,
                            ContrastChange, "画面の明るさ変更を変更できます。");
    *other +=
        new MenuEntry("ギルドカード情報変更" + workInProgress, nullptr,
                      GuildCardChange, "ギルドカードの情報を変更できます。");
    *other += new MenuEntry("リージョン変更" + stable, nullptr, RegionChange,
                            "日本かヨーロッパに変更できます。");
    *other += new MenuEntry("村の貢献度変更" + workInProgress, nullptr,
                            VillageContributionPointChange,
                            "村の貢献度を変更します。");
    *other += new MenuEntry("ルームサービス変更" + stable, nullptr,
                            RoomServiceChange, "ルームサービスを変更します。");
    *other += new MenuEntry("障害物無視" + workInProgress, nullptr, WallThrough,
                            "障害物を無視するかどうか選択できます。");
    *other += new MenuEntry("最大FPS変更" + stable, nullptr, MaximumFpsChange,
                            "最大FPSを変更できます。");
  }
  menu += other;

  MenuFolder *bonus = new MenuFolder("おまけ");
  {
    MenuFolder *conversion = new MenuFolder("変換");
    {
      *conversion += new MenuEntry("32bit版符号あり16進数→10進数" + stable,
                                   nullptr, HexToDecd32);
      *conversion += new MenuEntry("32bit版符号なし16進数→10進数" + stable,
                                   nullptr, HexToDecu32);
      *conversion += new MenuEntry("16bit版符号あり16進数→10進数" + stable,
                                   nullptr, HexToDecd16);
      *conversion += new MenuEntry("16bit版符号なし16進数→10進数" + stable,
                                   nullptr, HexToDecu16);
      *conversion += new MenuEntry("8bit版符号あり16進数→10進数" + stable,
                                   nullptr, HexToDecd8);
      *conversion += new MenuEntry("8bit版符号なし16進数→10進数" + stable,
                                   nullptr, HexToDecu8);
      *conversion += new MenuEntry("10進数→16進数" + stable, nullptr, DecToHex);
    }
    *bonus += conversion;

    MenuFolder *calculator = new MenuFolder("電卓");
    {
      *calculator +=
          new MenuEntry("16進数電卓" + stable, nullptr, HexadecimalCalculator,
                        "16進数を計算することができます。");
      *calculator +=
          new MenuEntry("10進数電卓" + stable, nullptr, DecimalCalculator,
                        "10進数を計算することができます。");
      *calculator +=
          new MenuEntry("浮動小数点数電卓" + stable, nullptr, DoubleCalculator,
                        "浮動小数点数を計算することができます。");
    }
    *bonus += calculator;

    MenuFolder *patchProcessEditor = new MenuFolder("CTRPFの色を変更");
    {
      MenuFolder *patchProcessEditorUi = new MenuFolder("UI");
      {
        *patchProcessEditorUi +=
            new MenuEntry("Main Text Color" + stable, nullptr,
                          PatchProcessUiMainTextColorEditor);
        *patchProcessEditorUi +=
            new MenuEntry("Window Title Color" + stable, nullptr,
                          PatchProcessUiWindowTitleColorEditor);
        *patchProcessEditorUi +=
            new MenuEntry("Menu Selected Item Color" + stable, nullptr,
                          PatchProcessUiMenuSelectedItemColorEditor);
        *patchProcessEditorUi +=
            new MenuEntry("Menu Unselected Item Color" + stable, nullptr,
                          PatchProcessUiMenuUnselectedItemColorEditor);
        *patchProcessEditorUi +=
            new MenuEntry("Background Main Color" + stable, nullptr,
                          PatchProcessUiBackgroundMainColorEditor);
        *patchProcessEditorUi +=
            new MenuEntry("Background Secondary Color" + stable, nullptr,
                          PatchProcessUiBackgroundSecondaryColorEditor);
        *patchProcessEditorUi +=
            new MenuEntry("Background Border Color" + stable, nullptr,
                          PatchProcessUiBackgroundBorderColorEditor);
      }
      *patchProcessEditor += patchProcessEditorUi;

      MenuFolder *patchProcessEditorKeyboard = new MenuFolder("Keyboard");
      {
        *patchProcessEditorKeyboard +=
            new MenuEntry("Background" + stable, nullptr,
                          PatchProcessKeyboardBackgroundColorEditor);
        *patchProcessEditorKeyboard +=
            new MenuEntry("Key Background" + stable, nullptr,
                          PatchProcessKeyboardKeyBackgroundColorEditor);
        *patchProcessEditorKeyboard +=
            new MenuEntry("Key Background Pressed" + stable, nullptr,
                          PatchProcessKeyboardKeyBackgroundPressedColorEditor);
        *patchProcessEditorKeyboard +=
            new MenuEntry("Key Text" + stable, nullptr,
                          PatchProcessKeyboardKeyTextColorEditor);
        *patchProcessEditorKeyboard +=
            new MenuEntry("Key Text Pressed" + stable, nullptr,
                          PatchProcessKeyboardKeyTextPressedColorEditor);
        *patchProcessEditorKeyboard += new MenuEntry(
            "Cursor" + stable, nullptr, PatchProcessKeyboardCursorColorEditor);
        *patchProcessEditorKeyboard += new MenuEntry(
            "Input" + stable, nullptr, PatchProcessKeyboardInputColorEditor);
      }
      *patchProcessEditor += patchProcessEditorKeyboard;

      MenuFolder *patchProcessEditorCustomKeyboard =
          new MenuFolder("Custom Keyboard");
      {
        *patchProcessEditorCustomKeyboard +=
            new MenuEntry("Background Main" + stable, nullptr,
                          PatchProcessCustomKeyboardBackgroundMainColorEditor);
        *patchProcessEditorCustomKeyboard += new MenuEntry(
            "Background Secondary" + stable, nullptr,
            PatchProcessCustomKeyboardBackgroundSecondaryColorEditor);
        *patchProcessEditorCustomKeyboard += new MenuEntry(
            "Background Border" + stable, nullptr,
            PatchProcessCustomKeyboardBackgroundBorderColorEditor);
        *patchProcessEditorCustomKeyboard +=
            new MenuEntry("Key Background" + stable, nullptr,
                          PatchProcessCustomKeyboardKeyBackgroundColorEditor);
        *patchProcessEditorCustomKeyboard += new MenuEntry(
            "Key Background Pressed" + stable, nullptr,
            PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor);
        *patchProcessEditorCustomKeyboard +=
            new MenuEntry("Key Text" + stable, nullptr,
                          PatchProcessCustomKeyboardKeyTextColorEditor);
        *patchProcessEditorCustomKeyboard +=
            new MenuEntry("Key Text Pressed" + stable, nullptr,
                          PatchProcessCustomKeyboardKeyTextPressedColorEditor);
        *patchProcessEditorCustomKeyboard += new MenuEntry(
            "Scroll Bar Background" + stable, nullptr,
            PatchProcessCustomKeyboardScrollBarBackgroundColorEditor);
        *patchProcessEditorCustomKeyboard +=
            new MenuEntry("Scroll Bar Thumb" + stable, nullptr,
                          PatchProcessCustomKeyboardScrollBarThumbColorEditor);
      }
      *patchProcessEditor += patchProcessEditorCustomKeyboard;

      *patchProcessEditor += new MenuEntry("Set Default Theme" + stable,
                                           nullptr, PatchProcessDefaultTheme);
    }
    *bonus += patchProcessEditor;

    *bonus += new MenuEntry("RGBチェッカー" + stable, nullptr, RGBOutput,
                            "入力されたRGB値がどういう色かが分かります。");

    *bonus += EntryWithHotkey(
        new MenuEntry("アドレス監視" + stable, HexEditor,
                      "アドレスと値の監視ができます。\nA+"
                      "↑で上に移動できます。\nA+↓で下に移動できます。"),
        {Hotkey(Key::R | A, "アドレス変更"), Hotkey(Key::R | B, "値を入力")});
    *bonus += new MenuEntry("時刻を確認" + stable, nullptr, LocalTimeDisplay,
                            "時刻を表示します。");
    *bonus += new MenuEntry("3DSの情報を確認" + stable, nullptr, Information,
                            "3DSの情報を確認できます。");
    *bonus += new MenuEntry(
        "フレンドコードシード値確認" + stable, nullptr, [](MenuEntry *entry) {
          MessageBox(Utils::Format("%X", Security::GetFriendCodeSeed))();
        });
  }
  menu += bonus;
}

// Plugin menu
int main() {
  const std::string title = "MHX3gx";
  const std::string about =
      "データのバックアップは取ってください。\n"
      "プラグインを楽しんでください！\n"
      "Twitter @ponpoko094\n"
      "github.com/ponpoko094/MHX3gx";

  // タイトルやAbout等作成
  PluginMenu *menu = new PluginMenu(title, 3, 0, 6, about, 0);

  // Synchronize the menu with frame event
  menu->SynchronizeWithFrame(true);

  // HexEditorを無効化
  menu->SetHexEditorState(true);

  // Plugin Ready!を無効化
  menu->ShowWelcomeMessage(false);

  // 利用規約の表示
  menu->OnFirstOpening = TeamAndCondition;

  // Plugin Ready!の代わり
  OSD::Notify(Color(234, 145, 152) << "ponpoko094's 3gx!");

  // Init our menu entries & folders
  InitMenu(*menu);

  // Launch menu and mainloop
  menu->Run();
  delete menu;
  return (0);
}

}  // namespace CTRPluginFramework
