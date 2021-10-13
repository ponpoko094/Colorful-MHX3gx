#include <3ds.h>

#include <CTRPluginFramework.hpp>

#include "cheats.hpp"
#include "libpon.hpp"
#include "patch.hpp"
#include "team_and_conditions.hpp"

namespace CTRPluginFramework {

// This patch the NFC disabling the touchscreen when scanning an amiibo, which
// prevents ctrpf to be used
static void ToggleTouchscreenForceOn() {
  static u32 original = 0;
  static u32 *patch_address = nullptr;

  if (patch_address && original) {
    *patch_address = original;
    return;
  }

  static const std::vector<u32> kPattern = {
      0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000, 0xE5C40008, 0xE28DD03C,
      0xE8BD80F0, 0xE5D51001, 0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003};

  Result res;
  Handle process_handle;
  s64 text_total_size = 0;
  s64 start_address = 0;
  u32 *found;

  if (R_FAILED(svcOpenProcess(&process_handle, 16))) return;

  svcGetProcessInfo(&text_total_size, process_handle, 0x10002);
  svcGetProcessInfo(&start_address, process_handle, 0x10005);
  if (R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000,
                                     process_handle, (u32)start_address,
                                     text_total_size))) {
    goto exit;
  }

  found = (u32 *)Utils::Search<u32>(0x14000000, (u32)text_total_size, kPattern);

  if (found != nullptr) {
    original = found[13];
    patch_address = (u32 *)PA_FROM_VA((found + 13));
    found[13] = 0xE1A00000;
  }

  svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, text_total_size);
  exit:
  svcCloseHandle(process_handle);
}

static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey) {
  if (entry != nullptr) {
    entry->Hotkeys += hotkey;
    entry->SetArg(new std::string(entry->Name()));
    entry->Name() += " " + hotkey.ToString();
    entry->Hotkeys.OnHotkeyChangeCallback([](MenuEntry *entry, int index) {
      auto *name = reinterpret_cast<std::string *>(entry->GetArg());
      entry->Name() = *name + " " + entry->Hotkeys[0].ToString();
    });
  }
  return (entry);
}

static MenuEntry *EntryWithHotkey(MenuEntry *entry,
                                  const std::vector<Hotkey> &hotkeys) {
  for (const Hotkey &hotkey: hotkeys) {
    entry->Hotkeys += hotkey;
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

// This function is called before Main and before the game starts
// Useful to do code edits safely
void PatchProcess(FwkSettings &settings) {
  ToggleTouchscreenForceOn();
  GetPatchColorData();

  // プラグインの設定
  // アクションリプレイ
  settings.AllowActionReplay = true;
  // サーチ
  settings.AllowSearchEngine = true;
  // 起動時間
  settings.WaitTimeToBoot = Seconds(3);
}

// This function is called when the process exits
// Useful to save settings, undo patchs or clean up things
void OnProcessExit() {
  ToggleTouchscreenForceOn();
}

// チートメニュー作成
void InitMenu(PluginMenu &menu) {
  const std::string kStable = " : " << Color::Green << "安定";
  const std::string kWorkInProgress = " : " << Color::Red << "作業中";

  auto *player = new MenuFolder("プレイヤー");
  {
    auto *status_v_2 = new MenuFolder("ステータス変更");
    {
      *status_v_2 += new MenuEntry("攻撃力変更" + kStable, nullptr,
                                   AttackPowerOption, "攻撃力を変更できます。");
      *status_v_2 += new MenuEntry("防御力変更" + kStable, nullptr,
                                   DefencePowerOption, "防御力を変更できます。");
      *status_v_2 += new MenuEntry("属性値変更" + kStable, nullptr,
                                   AttributeOption, "属性値を変更できます。");
      *status_v_2 += new MenuEntry("耐性値変更" + kStable, nullptr,
                                   ResistanceOption, "耐性値を変更できます。");
    }
    *player += status_v_2;

    auto *player_change = new MenuFolder("プレイヤー情報変更");
    {
      auto *hunter_art = new MenuFolder("狩技変更");
      {
        *hunter_art +=
            new MenuEntry("狩技1番目変更" + kStable, nullptr, HunterArt1Change,
                          "狩技の1番目を変更します。");
        *hunter_art +=
            new MenuEntry("狩技2番目変更" + kStable, nullptr, HunterArt2Change,
                          "狩技の2番目を変更します。");
        *hunter_art +=
            new MenuEntry("狩技3番目変更" + kStable, nullptr, HunterArt3Change,
                          "狩技の3番目を変更します。");
      }
      *player_change += hunter_art;

      auto *skin = new MenuFolder(
          "肌の色変更",
          "RGBの値は、\nbit.ly/GetRGB\nを見て、入力してください。");
      {
        *skin += new MenuEntry("肌の色R値変更" + kStable, nullptr, SkinRedChange,
                               "肌の色の赤色を変更します。");
        *skin += new MenuEntry("肌の色G値変更" + kStable, nullptr,
                               SkinGreenChange, "肌の色の緑色を変更します。");
        *skin += new MenuEntry("肌の色B値変更" + kStable, nullptr,
                               SkinBlueChange, "肌の色の青色を変更します。");
        *skin += new MenuEntry("肌の色変更" + kStable, nullptr, SkinColorChange,
                               "肌の色を変更します。");
      }
      *player_change += skin;

      auto *meal = new MenuFolder("食事");
      {
        auto *meal_flag = new MenuFolder("フラグ");
        {
          *meal_flag += new MenuEntry("食事無限" + kStable, MealInfinite,
                                      "食事が無限にできます。");
          *meal_flag +=
              new MenuEntry("高級お食事券効果付与" + kStable, LuxuryCouponGrant,
                            "高級お食事券の効果が付与されます。");
          *meal_flag += new MenuEntry("よろず焼きの依頼無限" + kStable,
                                      MeetRequestInfinite,
                                      "よろず焼きの依頼が無限にできます。");
        }
        *meal += meal_flag;

        auto *meal_status = new MenuFolder("ステータス");
        {
          auto *meal_status_resistance = new MenuFolder("耐性");
          {
            *meal_status_resistance +=
                new MenuEntry("火耐性UP" + kStable, MealFireResistanceUp,
                              "火耐性が上昇します。");
            *meal_status_resistance +=
                new MenuEntry("水耐性UP" + kStable, MealWaterResistanceUp,
                              "水耐性が上昇します。");
            *meal_status_resistance +=
                new MenuEntry("雷耐性UP" + kStable, MealThunderResistanceUp,
                              "雷耐性が上昇します。");
            *meal_status_resistance +=
                new MenuEntry("氷耐性UP" + kStable, MealIceResistanceUp,
                              "氷耐性が上昇します。");
            *meal_status_resistance +=
                new MenuEntry("龍耐性UP" + kStable, MealDragonResistanceUp,
                              "龍耐性が上昇します。");
          }
          *meal_status += meal_status_resistance;

          *meal_status +=
              new MenuEntry("体力UP" + kStable, MealHpUp, "体力が上昇します。");
          *meal_status += new MenuEntry("スタミナUP" + kStable, MealStaminaUp,
                                        "スタミナが上昇します。");
          *meal_status += new MenuEntry("攻撃力UP" + kStable, MealAttackPowerUp,
                                        "攻撃力が上昇します。");
          *meal_status += new MenuEntry("防御力UP" + kStable, MealDefencePowerUp,
                                        "防御力が上昇します。");
        }
        *meal += meal_status;

        *meal += new MenuEntry("スキル" + kStable, nullptr, MealSkillChange,
                               "食事スキルを変更します。");
      }
      *player_change += meal;

      *player_change += new MenuEntry("声変更" + kStable, nullptr,
                                      PlayerVoiceChange, "声を変更します。");
      *player_change +=
          new MenuEntry("目の色変更" + kStable, nullptr, PlayerEyeColorChange,
                        "目の色を変更します。");
      *player_change +=
          new MenuEntry("インナー変更" + kStable, nullptr, PlayerInnerChange,
                        "インナーを変更します。");
      *player_change += new MenuEntry("性別変更" + kStable, nullptr,
                                      PlayerGenderChange, "性別を変更します。");
      *player_change +=
          new MenuEntry("狩猟スタイル変更" + kStable, nullptr,
                        PlayerHuntingStyleChange, "狩猟スタイルを変更します。");
      *player_change +=
          new MenuEntry("髪型変更" + kStable, nullptr, PlayerHearStyleChange,
                        "髪型を変更します。");
      *player_change += new MenuEntry("顔変更" + kStable, nullptr,
                                      PlayerFaceChange, "顔を変更します。");
      *player_change +=
          new MenuEntry("メイク変更" + kStable, nullptr, PlayerCosmeticsChange,
                        "メイクを変更します。");
    }
    *player += player_change;

    *player += new MenuEntry("攻撃力倍率変更" + kStable, nullptr,
                             PlayerAttackPowerMagnificationOption,
                             "攻撃力の倍率を変更します。");
    *player += new MenuEntry("防御力倍率変更" + kStable, nullptr,
                             PlayerDefencePowerMagnificationOption,
                             "防御力の倍率を変更します。");
    *player += new MenuEntry("速度変更" + kStable, nullptr, PlayerSpeedOption,
                             "速度を変更します。");
    *player +=
        new MenuEntry("プレイヤー座標移動" + kStable, PlayerCoordinateModifier,
                      "A+十字キーで移動できます。");
    *player += new MenuEntry(
        "ムーンジャンプ" + kStable, PlayerMoonJump,
        "R+Bでジャンプできます。\n"
        "上がり続けるにはリピートムーブもオンにして、R+B+Yを押してください。");
    *player +=
        new MenuEntry("保存式テレポート" + kStable, Teleport,
                      "X + → 現在位置を読み込む。\nX + ← 現在位置に書き込む");
    *player += new MenuEntry(
        "他プレイヤーストーカー" + kStable, Stalker,
        "R+十字キーで追跡設定ができます。\nR↑ P1を追跡有効\n"
        "R+→ P2を追跡有効\nR+↓ P3を追跡有効\nR+←で追跡無効にできます。");
    *player += new MenuEntry("リピートムーブ" + kStable, RepeatMove,
                             "B+Yで動きを繰り返します。");
    *player += new MenuEntry("狩技解放" + kStable, HunterArtRelease,
                             "狩技を全て解放します。");
    *player += new MenuEntry("腹減り無効" + kStable, HungryInvalid,
                             "時間経過でスタミナが減らなくなります。");
    *player +=
        new MenuEntry("プレイヤーサイズ変更" + kStable, nullptr,
                      HunterSizeOption, "ハンターのサイズを変更できます。");
    *player += new MenuEntry("HP無限" + kStable, nullptr, InfiniteHp,
                             "HPを無限にします。");
    *player +=
        new MenuEntry("無敵" + kStable, nullptr, Invincible, "無敵になります。");
    *player += new MenuEntry("スーパーアーマー" + kStable, nullptr, SuperArmor,
                             "スーパーアーマーになります。\n"
                             "オンにした後オフにすると被弾したときに"
                             "のけぞりのモーションになります。");
    *player += new MenuEntry("スタミナ無限" + kStable, nullptr, InfiniteStamina,
                             "スタミナを無限にします。");
    *player += new MenuEntry("狩技ゲージ無限" + kStable, nullptr,
                             InfiniteHunterArt, "狩技ゲージが無限になります。");
    *player += new MenuEntry("全スタイルで狩技3つ装着可能" + kStable, nullptr,
                             Always3HunterArtEquip,
                             "全スタイルで狩技を3つ装着可能になります。");
    *player += new MenuEntry("常時地図表示" + kStable, nullptr, AlwaysDisplayMap,
                             "常に地図を表示します。");
    *player +=
        new MenuEntry("常にモンスターペイント" + kStable, nullptr, AlwaysPaint,
                      "常にマップにモンスターが表示されます。");
    *player += new MenuEntry("スピードハック" + kStable, nullptr, SpeedHack,
                             "速度の変更ができます。");
    *player +=
        new MenuEntry("クエスト中スピードハック" + kStable, nullptr,
                      InQuestSpeedHack, "クエスト中での速度を変更できます。");
    *player +=
        new MenuEntry("走った時にムーンウォーク" + kStable, nullptr,
                      IfRunMoonWalk, "走った時にムーンウォークをします。");
    *player += new MenuEntry(
        "プレイヤー名前変更" + kStable, nullptr, HunterNameChange,
        "定型文では1ページ目の一番左下にある定型文を名前にコピーします。\n"
        "キーボードでは、メニュー内で直接変更することができます。\n"
        "変換候補変換の改行やタブが使えます。");
    *player += new MenuEntry("被弾したときのダメージ変更" + kStable,
                             nullptr, PlayerReceivedDamageChange,
                             "プレイヤーが被弾したときのダメージを変更します。\n"
                             "即死を選ぶと他のプレイヤーの攻撃でも即死します。");
  }
  menu += player;

  auto *item = new MenuFolder("アイテム");
  {
    auto *equipment = new MenuFolder("装備");
    {
      auto *amulet =
          new MenuFolder("護石編集",
                         "編集したい護石を、装備BOX14ページ目の一番右下に"
                         "移動させてください。\n"
                         "14ページ目がない場合は、アイテムフォルダにある"
                         "「ボックス1400個に拡張」をオンにしてください。");
      {
        *amulet += new MenuEntry("新護石作成" + kStable, nullptr, AmuletCreate,
                                 "新たに護石を作成できます。");
        *amulet += new MenuEntry("護石種類変更" + kStable, nullptr,
                                 AmuletTypeChange, "護石の種類を変更します。");
        *amulet += new MenuEntry("スキル変更" + kStable, nullptr,
                                 AmuletSkillChange, "スキルを変更します。");
        *amulet += new MenuEntry("スキルポイント変更" + kStable, nullptr,
                                 AmuletSkillPointChange,
                                 "スキルポイントを変更します。");
        *amulet += new MenuEntry("スロット数変更" + kStable, nullptr,
                                 AmuletSlotChange, "スロット数を変更します。");
      }
      *equipment += amulet;

      auto *insect =
          new MenuFolder("猟虫編集",
                         "編集したい猟虫がついている操虫棍を、装備BOX14ページ目"
                         "の一番下の右から4番目に移動させてください。\n"
                         "14ページ目がない場合は、アイテムフォルダにある「ボッ"
                         "クス1400個に拡張」をオンにしてください。");
      {
        *insect += new MenuEntry("猟虫種類変更" + kStable, nullptr,
                                 InsectTypeChange, "猟虫の種類を変更します。");
        *insect +=
            new MenuEntry("猟虫レベル変更" + kStable, nullptr, InsectLevelChange,
                          "猟虫のレベルを変更します。");
        *insect +=
            new MenuEntry("猟虫パワー補正変更" + kStable, nullptr,
                          InsectPowerChange, "猟虫のパワー補正を変更します。");
        *insect += new MenuEntry("猟虫ウェイト補正変更" + kStable, nullptr,
                                 InsectWeightChange,
                                 "猟虫のウェイト補正を変更します。");
        *insect += new MenuEntry("猟虫スタミナ補正変更" + kStable, nullptr,
                                 InsectStaminaChange,
                                 "猟虫のスタミナ補正を変更します。");
        *insect += new MenuEntry("猟虫火属性変更" + kStable, nullptr,
                                 InsectFireAttributeChange,
                                 "猟虫の火属性を変更します。");
        *insect += new MenuEntry("猟虫水属性変更" + kStable, nullptr,
                                 InsectWaterAttributeChange,
                                 "猟虫の水属性を変更します。");
        *insect += new MenuEntry("猟虫雷属性変更" + kStable, nullptr,
                                 InsectThunderAttributeChange,
                                 "猟虫の雷属性を変更します。");
        *insect += new MenuEntry("猟虫氷属性変更" + kStable, nullptr,
                                 InsectIceAttributeChange,
                                 "猟虫の氷属性を変更します。");
        *insect += new MenuEntry("猟虫龍属性変更" + kStable, nullptr,
                                 InsectDragonAttributeChange,
                                 "猟虫の龍属性を変更します。");
      }
      *equipment += insect;

      *equipment += new MenuEntry(
          "他プレイヤーの装備コピー" + kStable, nullptr,
          OtherPlayerEquipmentCopy,
          "コピーしたいプレイヤーが猫の場合、コピーしないでください。");
    }
    *item += equipment;

    *item += new MenuEntry("爆弾を無限に置ける" + kStable, InfiniteBombPut,
                           "見た目だけです。");
    *item += new MenuEntry("たんほれアイテムセット" + kStable, TanhoreItemSet,
                           "ポーチの\n"
                           "1枠目を 燃石炭\n"
                           "2枠目を ネコタクチケット\n"
                           "3枠目を モドリ玉\n"
                           "にします。");
    *item += new MenuEntry("所持金最大" + kStable, nullptr, MoneyChange,
                           "所持金を変更できます。");
    *item +=
        new MenuEntry("龍歴院ポイント最大" + kStable, nullptr,
                      WycademyPointChange, "龍歴院ポイントを変更できます。");
    *item +=
        new MenuEntry("アイテム&弾丸無限" + kStable, nullptr, InfiniteItemAmmo,
                      "アイテムと弾丸を無限にします。\n"
                      "しゃがみの弾は無限になりません。");
    *item +=
        new MenuEntry("素材無しで調合可能" + kStable, nullptr,
                      NoMaterialCompound, "素材無しで調合を可能にします。");
    *item += new MenuEntry("運搬物を持たずにポーチに入れる" + kStable, nullptr,
                           CargoPutInPorch, "運搬物がポーチに入ります。");
    *item += new MenuEntry("採取無限" + kStable, nullptr, InfiniteCollect,
                           "採集ポイントで無限に採取ができます。");
    *item += new MenuEntry("装備を素材無しで作れる" + kStable, nullptr,
                           NoMaterialEquipmentCreate,
                           "素材なしで装備生産をすることができます。");
    *item +=
        new MenuEntry("装備欄全て解放" + kStable, nullptr, EquipmentAllRelease,
                      "装備生産リストを全て解放します。");
    *item +=
        new MenuEntry("全てのアイテム販売" + kStable, nullptr, AllItemSold,
                      "全てのアイテムがギルドストアや雑貨屋に売り出されます。");
    *item += new MenuEntry("ボックス1400個に拡張" + kStable, nullptr,
                           ItemBox1400Expansion,
                           "ボックスのページを1400個に拡張します。");
    *item += new MenuEntry("持てるアイテム99個" + kStable, nullptr, HaveItem99,
                           "持てるアイテムの最大数を99個にします。");
    *item += new MenuEntry("アイテムボックスをマイハウス化" + kStable,
                           ItemBoxCanEquipmentChange,
                           "アイテムボックスをマイハウスにあるアイテムボックスと同等の機能をもたせます。");
    *item += new MenuEntry("アイテムボックス編集" + kStable, nullptr,
                           ItemBoxEdit, "アイテムボックスの編集をします。");
    *item +=
        new MenuEntry("アイテムマイセットをポーチにコピー" + kStable, nullptr,
                      MySetToPorchItemCopy,
                      "アイテムマイセットに登録されているアイテムを、アイテムポ"
                      "ーチにコピーします。");
    *item += new MenuEntry(
        "納品アイテムをポーチにコピー" + kStable, nullptr,
        DeliveryItemToPorchCopy,
        "納品アイテムを、アイテムポーチの1番目と2番目にコピーします。\n"
        "空きを作ってください。");
    *item +=
        new MenuEntry("ポーチのアイテム全消去" + kStable, nullptr, PorchAllClear,
                      "ポーチのアイテムを全消去します。\n"
                      "消せないアイテムや、ボックスにしまえないアイテムが"
                      "あるときに実行してください。");
    *item += new MenuEntry("特殊許可チケットの数変更" + kStable, nullptr,
                           SpecialPermitQuestTicketChange,
                           "特殊許可チケットの枚数を変更します。");
  }
  menu += item;

  auto *weapon = new MenuFolder("武器");
  {
    auto *weapon_type = new MenuFolder("武器別チート");
    {
      auto *gunlance = new MenuFolder("ガンランスチート");
      {
        *gunlance +=
            new MenuEntry("ヒートゲージ固定" + kStable, nullptr,
                          GunlanceHeatGageOption, "ヒートゲージを固定します。");
        *gunlance +=
            new MenuEntry("ガンランスの弾無限" + kStable, GunlanceAmmoInfinite,
                          "ガンランスの弾を無限にします。");
        *gunlance += new MenuEntry("オーバーヒート無効" + kStable,
                                   GunlanceInvalidOverHeat,
                                   "オーバーヒートを無効にします。");
      }
      *weapon_type += gunlance;

      auto *insect_glaive = new MenuFolder("操虫棍チート");
      {
        *insect_glaive += new MenuEntry("常時トリプルアップ" + kStable,
                                        InsectGlaiveAlwaysTripleUp,
                                        "常時トリプルアップになります。");
        *insect_glaive += new MenuEntry("虫のスタミナ無限" + kStable,
                                        InsectGlaiveInsectStaminaInfinite,
                                        "虫のスタミナが無限になります。");
      }
      *weapon_type += insect_glaive;

      auto *bowgun = new MenuFolder("ボウガンチート");
      {
        *bowgun +=
            new MenuEntry("ボウガンの弾無限" + kStable, BowgunAmmoInfinite,
                          "ボウガンの弾が無限になります。");
        *bowgun +=
            new MenuEntry("しゃがみの弾無限" + kStable, BowgunCrouchingShot,
                          "しゃがみ撃ちの弾が無限になります。");
      }
      *weapon_type += bowgun;
      *weapon_type +=
          new MenuEntry("溜め段階固定" + kStable, nullptr, ChargeStageOption,
                        "大剣などの溜め段階を固定します。");
      *weapon_type += new MenuEntry("武器ゲージ固定" + kStable, WeaponGageFix,
                                    "太刀や双剣のゲージを固定します。");
      *weapon_type +=
          new MenuEntry("チャージアックスビン固定" + kStable, ChargeAxeBinFix,
                        "チャージアックスのビン数を固定します。");
      *weapon_type += new MenuEntry("狩猟笛の全効果付与" + kStable,
                                    HuntingHornAllEffectGrant,
                                    "反映されない効果があります。");
    }
    *weapon += weapon_type;

    *weapon += new MenuEntry("属性値変更" + kStable, nullptr,
                             AttributePointChange, "属性値を変更できます。");
    *weapon += new MenuEntry("モーション無し" + kStable, nullptr, NoMotion,
                             "モーションを無くします。");
    *weapon += new MenuEntry("会心率100%" + kStable, nullptr, CriticalRate100,
                             "会心率が100%になります。");
    *weapon +=
        new MenuEntry("ボウガン自動装填" + kStable, nullptr, BowgunAutoReload,
                      "ボウガンの弾が自動で装填されます。");
    *weapon += new MenuEntry("斬れ味無限" + kStable, nullptr, InfiniteSharpness,
                             "斬れ味が無限になります。");
    *weapon += new MenuEntry("斬れ味+2" + kStable, nullptr, SharpnessPlus2,
                             "斬れ味レベル+2の効果を付与します。");
    *weapon += new MenuEntry("高速溜め短縮" + kStable, nullptr, ChargeSpeedUp,
                             "大剣等の溜めが短縮されます。");
    *weapon += new MenuEntry("チャージゲージ最大" + kStable, nullptr,
                             ChargeGageMax, "太刀等のゲージが最大になります。");
  }
  menu += weapon;

  auto *monster = new MenuFolder(
      "モンスター", "オンラインだとラグがあったり、使えない場合があります。");
  {
    auto *monster_display = new MenuFolder("モンスター情報画面表示");
    {
      *monster_display +=
          new MenuEntry("1番目のモンスターのHP表示" + kStable, Monster1HpDisplay,
                        "1番目のモンスターのHPを画面上に表示します。");
      *monster_display +=
          new MenuEntry("2番目のモンスターのHP表示" + kStable, Monster2HpDisplay,
                        "2番目のモンスターのHPを画面上に表示します。");
      *monster_display += new MenuEntry(
          "1番目のモンスターのサイズ倍率表示" + kStable,
          Monster1SizeMagnificationDisplay,
          "1番目のモンスターのサイズ倍率を画面上に表示します。\n"
          "1.2付近がキンズサイズ、0.9付近がスモールサイズの目安です。");
      *monster_display += new MenuEntry(
          "2番目のモンスターのサイズ倍率表示" + kStable,
          Monster2SizeMagnificationDisplay,
          "2番目のモンスターのサイズ倍率を画面上に表示します。\n"
          "1.2付近がキングサイズ、0.9付近がスモールサイズの目安です。");
    }
    *monster += monster_display;

    *monster += new MenuEntry("乗り成功" + kStable, RideGageMax,
                              "ハンターの乗りゲージを最大にします。\nモンス"
                              "ターの乗りゲージが増えないようにします。");
    *monster +=
        new MenuEntry("モンスター座標移動" + kStable, MonsterCoordinateModifier,
                      "1番目のモンスターはX+十字キーで操作できます。\n"
                      "2番目のモンスターはX+スライドパッドで操作できます。\n"
                      "操作したいモンスターと同じエリアにいてください。");
    *monster +=
        new MenuEntry("モンスターストーカー" + kStable, MonsterStalker,
                      "1番目のモンスターはX+R+↑で追跡有効にできます。\n"
                      "2番目のモンスターはX+L+↑で追跡有効にできます。\n"
                      "X+R+↓で追跡停止できます。\n"
                      "追跡したいモンスターと同じエリアにいてください。");
    *monster += new MenuEntry(
        "モンスターリピートムーブ" + kStable, nullptr, MonsterActionRepeatOption,
        "リピートムーブの挙動の変更と、操作のオンオフができます。\n"
        "1番目のモンスターはX+R+→で操作できます。\n"
        "2番目のモンスターはX+L+→で操作できます。\n"
        "操作したいモンスターと同じエリアにいてください。");
    *monster += new MenuEntry("1番目と2番目のモンスターの動き停止" + kStable,
                              Monster1And2Stop,
                              "動き停止は、速度変更より優先されます。\n"
                              "当たり判定がなくなります。");
    *monster += new MenuEntry("1番目のモンスターのサイズ変更" + kStable, nullptr,
                              Monster1SizeOption,
                              "1番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry("2番目のモンスターのサイズ変更" + kStable, nullptr,
                              Monster2SizeOption,
                              "2番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry("1番目のモンスターの速度倍率変更" + kStable,
                              nullptr, Monster1SpeedAttributeOption,
                              "1番目のモンスターの速度の変更ができます。");
    *monster += new MenuEntry("2番目のモンスターの速度倍率変更" + kStable,
                              nullptr, Monster2SpeedAttributeOption,
                              "2番目のモンスターの速度の変更ができます。");
    *monster += new MenuEntry(
        "1番目と2番目のモンスター常時毒" + kStable, Monster1And2AlwaysPoison,
        "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster +=
        new MenuEntry("1番目と2番目のモンスター常時麻痺" + kStable,
                      Monster1And2AlwaysParalysis,
                      "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry(
        "1番目と2番目のモンスター常時睡眠" + kStable, Monster1And2AlwaysSleep,
        "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster +=
        new MenuEntry("1番目と2番目のモンスター透明化" + kStable, nullptr,
                      Monster1And2AlwaysInvisible,
                      "1番目と2番目のモンスターのサイズの変更ができます。");
    *monster += new MenuEntry("瞬殺" + kStable, nullptr, OneAttackKill,
                              "モンスターを瞬殺できます。");
  }
  menu += monster;

  auto *palico = new MenuFolder("ねこ");
  {
    auto *palico_edit = new MenuFolder("ねこ編集");
    {
      *palico_edit += new MenuEntry("ねこ選択" + kStable, nullptr, PalicoChoice,
                                    "編集するねこを選択します。");
      *palico_edit += new MenuEntry("装備サポート行動変更" + kStable, nullptr,
                                    PalicoEquipmentSupportActionChanger,
                                    "ねこの装備サポート行動を変更します。");
      *palico_edit += new MenuEntry("装備オトモスキル変更" + kStable, nullptr,
                                    PalicoEquipmentSkillChanger,
                                    "ねこの装備オトモスキルを変更します。\n"
                                    "最大スキル枠を超えるとエラーになります。");
      *palico_edit += new MenuEntry("習得サポート行動変更" + kStable, nullptr,
                                    PalicoLearnSupportActionChanger,
                                    "ねこの習得サポート行動を変更します。");
      *palico_edit += new MenuEntry("習得オトモスキル変更" + kStable, nullptr,
                                    PalicoLearnSkillChanger,
                                    "ねこの習得オトモスキルを変更します。");

      auto *palico_appearance = new MenuFolder("見た目");
      {
        auto *palico_appearance_color = new MenuFolder("見た目の色変更");
        {
          *palico_appearance_color += new MenuEntry("毛色変更" + kStable, nullptr,
                                                    PalicoBodyHairColorChanger,
                                                    "ねこの毛色を変更します。");
          *palico_appearance_color += new MenuEntry(
              "右目の色変更" + kStable, nullptr, PalicoRightEyeColorChanger,
              "ねこの右目の色を変更します。");
          *palico_appearance_color += new MenuEntry(
              "左目の色変更" + kStable, nullptr, PalicoLeftEyeColorChanger,
              "ねこの左目の色を変更します。");
          *palico_appearance_color += new MenuEntry(
              "インナーの色変更" + kStable, nullptr, PalicoInnerColorChanger,
              "ねこのインナーの色を変更します。");
        }
        *palico_appearance += palico_appearance_color;

        *palico_appearance +=
            new MenuEntry("声変更" + kStable, nullptr, PalicoVoiceChange,
                          "ねこの声を変更します。");
        *palico_appearance +=
            new MenuEntry("目変更" + kStable, nullptr, PalicoEyeChange,
                          "ねこの目を変更します。");
        *palico_appearance +=
            new MenuEntry("インナー変更" + kStable, nullptr, PalicoInnerChange,
                          "ねこのインナーを変更します。");
        *palico_appearance +=
            new MenuEntry("毛並み変更" + kStable, nullptr, PalicoFurCoatChange,
                          "ねこの毛並みを変更します。");
        *palico_appearance +=
            new MenuEntry("耳変更" + kStable, nullptr, PalicoEarChange,
                          "ねこの耳を変更します。");
        *palico_appearance +=
            new MenuEntry("尻尾変更" + kStable, nullptr, PalicoTailChange,
                          "ねこの尻尾を変更します。");
      }
      *palico_edit += palico_appearance;

      *palico_edit +=
          new MenuEntry("経験値変更" + kStable, nullptr, PalicoExperienceChange,
                        "ねこの経験値を変更します。");
      *palico_edit +=
          new MenuEntry("レベル変更" + kStable, nullptr, PalicoLevelChange,
                        "ねこのレベルを変更します。");
      *palico_edit += new MenuEntry("サポート傾向変更" + kStable, nullptr,
                                    PalicoSupportTrendChange,
                                    "ねこのサポート傾向を変更します。");
      *palico_edit +=
          new MenuEntry("親密度変更" + kStable, nullptr, PalicoClosenessChange,
                        "ねこの親密度を変更します。");
      *palico_edit +=
          new MenuEntry("ターゲット変更" + kStable, nullptr, PalicoTargetChange,
                        "ねこのターゲットを変更します。");
      *palico_edit +=
          new MenuEntry("オトモコメント編集可能変更" + kStable, nullptr,
                        PalicoCommentEditPossibleChange,
                        "ねこのオトモコメントを編集可能にするか選べます。");
      *palico_edit += new MenuEntry("特別配信表示変更" + kStable, nullptr,
                                    SpecialDeliveryDisplayChange,
                                    "ねこの特別配信の表示を変更します。");
      *palico_edit += new MenuEntry(
          "名前変更" + kStable, nullptr, PalicoNameChange,
          "ねこの名前を変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこの名前にコピーします"
          "。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
      *palico_edit += new MenuEntry(
          "コメント変更" + kStable, nullptr, PalicoCommentChange,
          "ねこのコメントを変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこのコメントにコピーし"
          "ます。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
      *palico_edit += new MenuEntry(
          "名付け親変更" + kStable, nullptr, PalicoGodParentChange,
          "ねこの名付け親を変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこの名付け親にコピーし"
          "ます。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
      *palico_edit += new MenuEntry(
          "先代旦那さん変更" + kStable, nullptr, PalicoPredecessorHusbandChange,
          "ねこの先代旦那さんを変更します。\n"
          "定型文では1ページ目の一番左下にある定型文をねこの先代旦那さんにコピ"
          "ーします。\n"
          "キーボードでは、メニュー内で直接変更することができます。\n"
          "変換候補変換の改行やタブが使えます。");
    }
    *palico += palico_edit;

    *palico += new MenuEntry("ねこの攻撃力倍率変更" + kStable, nullptr,
                             PalicoAttackPowerMagnificationOption,
                             "ねこの攻撃力の倍率を変更します。");
    *palico += new MenuEntry("ねこの防御力倍率変更" + kStable, nullptr,
                             PalicoDefencePowerMagnificationOption,
                             "ねこの防御力変更の倍率を変更します。");
    *palico += new MenuEntry(
        "ねこ吸収" + kStable, PalicoAbsorption,
        "ねこをハンターに吸収させます。\n他プレイヤーからは見えません。");
    *palico +=
        new MenuEntry("サポートゲージ最大" + kStable, ProwlerSupportGageMax,
                      "ニャンターのサポートゲージを最大にします。");
  }
  menu += palico;

  auto *other = new MenuFolder("その他");
  {
    auto *chat = new MenuFolder("チャット");
    {
      *chat += new MenuEntry("チャット無限" + kStable, ChatInfinite,
                             "オンラインで赤文字を出現させなくします。");
      *chat += new MenuEntry("変換候補変換" + kStable, ChatConversionChange,
                             "キーボードを開いて、Rを押しながら文字を打つ"
                             "ことで、変換候補の文字が変わります。");
      *chat += new MenuEntry(
          "変換候補変換対応文字一覧" + kStable, nullptr, ChatConversionList,
          "変換対応文字が書かれています。\n"
          "変換しづらい文字や、改造でしか入力できない文字を入れています。");
      *chat += new MenuEntry("クエスト中にチャット可能" + kStable,
                             ChatInQuest,
                             "クエスト中でもキーボードを開いてチャットができます。");
    }
    *other += chat;

    auto *drunk =
        new MenuFolder("酔っぱらい", "クエスト中は酔っぱらえません。");
    {
      *drunk +=
          new MenuEntry("即酔っぱらい" + kStable, nullptr, InstantDrunkOption,
                        "酔っぱらいになるか変更できます。");
      *drunk += new MenuEntry("1回お酒を飲むと酔っぱらい" + kStable, Drunk1,
                              "1回お酒を飲むと酔っぱらいになります。");
    }
    *other += drunk;

    auto *hunter_rank = new MenuFolder("ハンターランク");
    {
      *hunter_rank +=
          new MenuEntry("ハンターランク変更" + kStable, nullptr,
                        HunterRankChange, "ハンターランクを変更できます。");
      *hunter_rank += new MenuEntry("ハンターランクポイント変更" + kStable,
                                    nullptr, HunterRankPointChange,
                                    "ハンターランクポイントを変更できます。");
    }
    *other += hunter_rank;

    auto *feny_and_pugy = new MenuFolder("プーギー&フェニー");
    {
      *feny_and_pugy += new MenuEntry("フェニー&プーギーの服変更" + kStable,
                                      nullptr, FenyAndPugyClothes,
                                      "フェニー&プーギーの服を変更できます。");
      *feny_and_pugy += new MenuEntry(
          "定型文でフェニー&プーギーの名前変更" + kStable, nullptr,
          FenyAndPugyNameChange,
          "1ページ目の一番左下にある定型文を名前にコピーします。\nフェニ"
          "ー&プーギーの名前を変更できます。");
    }
    *other += feny_and_pugy;

    auto *quest = new MenuFolder("クエスト");
    {
      *quest += new MenuEntry("クエストステータス変更" + kStable, nullptr,
                              QuestClearOption,
                              "クエストクリアか失敗を選択できます。");
      *quest +=
          new MenuEntry("クエストクリア後即リザルト" + kStable, QuestWaitSkip,
                        "クエストクリア後の待ち時間をスキップします。");
      *quest += new MenuEntry("報酬画面スキップ" + kStable, QuestResultSkip,
                              "報酬受取の時間を0にし、スキップします。");
      *quest +=
          new MenuEntry("最大ダウン回数変更" + kStable, nullptr,
                        QuestDownMaxOption, "最大ダウン回数を変更できます。");
      *quest +=
          new MenuEntry("現在のダウン回数変更" + kStable, nullptr,
                        QuestDownNowOption, "現在のダウン回数を変更します。");
      *quest += new MenuEntry(
          "クエスト残り時間表示" + kStable, QuestTimeDisplay,
          "QT = Quest Timeです。\n時:分:秒:フレーム\nと表示します。");
      *quest +=
          new MenuEntry("選択肢を固定" + kStable, nullptr, SaveScreenOption,
                        "Rボタンを押すと固定できます。");
      *quest += new MenuEntry("クエスト時間停止" + kStable, nullptr,
                              QuestTimeStop, "クエスト時間を停止します。");
      *quest += new MenuEntry(
          "全クエストクリア変更" + kStable, nullptr, AllQuestClearChange,
          "ストーリーに不具合が起きる可能性があります。\n予めバックアップ"
          "を取ったり、サブキャラクターで実行してください。");
    }
    *other += quest;

    auto *base =
        new MenuFolder("集会所", "ベルナ村にいる状態で変更してください。");
    {
      auto *base_create = new MenuFolder("集会所を作る");
      {
        *base_create += new MenuEntry("ターゲット変更" + kStable, nullptr,
                                      BaseCreateTargetChange,
                                      "ターゲットを？？？？？にできます。");
        *base_create += new MenuEntry("クエスト形式変更" + kStable, nullptr,
                                      BaseCreateQuestTypeChange,
                                      "クエスト形式を変更できます。");
        *base_create +=
            new MenuEntry("募集HR下限変更" + kStable, nullptr,
                          BaseCreateRecruitmentHunterRankMinimumChange,
                          "募集HRの下限を変更できます。");
        *base_create +=
            new MenuEntry("募集HR上限変更" + kStable, nullptr,
                          BaseCreateRecruitmentHunterRankMaximumChange,
                          "募集HRの上限を変更できます。");
        *base_create += new MenuEntry("入室人数変更" + kStable, nullptr,
                                      BaseCreateEntryPeopleChange,
                                      "入室人数を変更できます。");
        *base_create += new MenuEntry("入室制限変更" + kStable, nullptr,
                                      BaseCreateEntryLimitChange,
                                      "入室制限を変更できます。");
        *base_create += new MenuEntry("パスワード有無変更" + kStable, nullptr,
                                      BaseCreatePasswordExistChange,
                                      "パスワードの有無を変更できます。");
        *base_create += new MenuEntry("募集文①変更" + kStable, nullptr,
                                      BaseCreateRecruitmentMessage1Change,
                                      "募集文①を変更できます。");
        *base_create += new MenuEntry("募集文②変更" + kStable, nullptr,
                                      BaseCreateRecruitmentMessage2Change,
                                      "募集文②を変更できます。");
        *base_create += new MenuEntry("募集文③変更" + kStable, nullptr,
                                      BaseCreateRecruitmentMessage3Change,
                                      "募集文③を変更できます。");
        *base_create += new MenuEntry("募集文④変更" + kStable, nullptr,
                                      BaseCreateRecruitmentMessage4Change,
                                      "募集文④を変更できます。");
      }
      *base += base_create;

      auto *base_search = new MenuFolder("集会所を探す");
      {
        *base_search +=
            new MenuEntry("ターゲット変更" + kStable, nullptr,
                          BaseSearchTargetChange, "ターゲットを変更できます。");
        *base_search += new MenuEntry("クエスト形式変更" + kStable, nullptr,
                                      BaseSearchQuestTypeChange,
                                      "クエスト形式を変更できます。");
        *base_search += new MenuEntry("ホストHR下限変更" + kStable, nullptr,
                                      BaseSearchHostHunterRankMinimumChange,
                                      "ホストHRの下限を変更できます");
        *base_search += new MenuEntry("ホストHR上限変更" + kStable, nullptr,
                                      BaseSearchHostHunterRankMaximumChange,
                                      "ホストHRの上限を変更できます");
        *base_search += new MenuEntry("クエスト中変更" + kStable, nullptr,
                                      BaseSearchInQuestChange,
                                      "クエスト中を変更できます。");
        *base_search += new MenuEntry("パスワード有無変更" + kStable, nullptr,
                                      BaseSearchPasswordExistChange,
                                      "パスワードの有無を変更できます。");
      }
      *base += base_search;
    }
    *other += base;

    *other += new MenuEntry("プレイヤーの現在座標表示" + kStable,
                            DisplayPlayerCoordinate,
                            "プレイヤーの現在座標を表示します。");
    *other += new MenuEntry("クエスト中の視野角変更" + kStable, nullptr,
                            ViewingAngleOption,
                            "クエスト中の視野角を変更します。\n(画面酔い注意)");
    *other += new MenuEntry("視野角変更" + kStable, nullptr,
                            ViewingAngleChangeV2, "視野の倍率を変更できます。");
    *other += new MenuEntry("武器サイズ変更" + kStable, nullptr,
                            WeaponSizeChange, "武器のサイズを変更できます。");
    *other += new MenuEntry("画面の明るさ変更" + kStable, nullptr,
                            ContrastChange, "画面の明るさ変更を変更できます。");
    *other +=
        new MenuEntry("ギルドカード情報変更" + kStable, nullptr, GuildCardChange,
                      "ギルドカードの情報を変更できます。");
    *other += new MenuEntry("リージョン変更" + kStable, nullptr, RegionChange,
                            "日本かヨーロッパに変更できます。");
    *other += new MenuEntry("村の貢献度変更" + kStable, nullptr,
                            VillageContributionPointChange,
                            "村の貢献度を変更します。");
    *other += new MenuEntry("ルームサービス変更" + kStable, nullptr,
                            RoomServiceChange, "ルームサービスを変更します。");
    *other +=
        new MenuEntry("障害物無視" + kStable, nullptr, WallThrough,
                      "クエスト中に障害物を無視するかどうか選択できます。");
    *other += new MenuEntry("最大FPS変更" + kStable, nullptr, MaximumFpsChange,
                            "最大FPSを変更できます。");
  }
  menu += other;

  auto *bonus = new MenuFolder("おまけ");
  {
    auto *conversion = new MenuFolder("変換");
    {
      *conversion += new MenuEntry("32bit版符号あり16進数→10進数" + kStable,
                                   nullptr, HexToDecD32);
      *conversion += new MenuEntry("32bit版符号なし16進数→10進数" + kStable,
                                   nullptr, HexToDecU32);
      *conversion += new MenuEntry("16bit版符号あり16進数→10進数" + kStable,
                                   nullptr, HexToDecD16);
      *conversion += new MenuEntry("16bit版符号なし16進数→10進数" + kStable,
                                   nullptr, HexToDecU16);
      *conversion += new MenuEntry("8bit版符号あり16進数→10進数" + kStable,
                                   nullptr, HexToDecD8);
      *conversion += new MenuEntry("8bit版符号なし16進数→10進数" + kStable,
                                   nullptr, HexToDecU8);
      *conversion += new MenuEntry("10進数→16進数" + kStable, nullptr, DecToHex);
    }
    *bonus += conversion;

    auto *calculator = new MenuFolder("電卓");
    {
      *calculator +=
          new MenuEntry("16進数電卓" + kStable, nullptr, HexadecimalCalculator,
                        "16進数を計算することができます。");
      *calculator +=
          new MenuEntry("10進数電卓" + kStable, nullptr, DecimalCalculator,
                        "10進数を計算することができます。");
      *calculator +=
          new MenuEntry("浮動小数点数電卓" + kStable, nullptr, DoubleCalculator,
                        "浮動小数点数を計算することができます。");
    }
    *bonus += calculator;

    auto *patch_process_editor = new MenuFolder("CTRPFの色を変更");
    {
      auto *patch_process_editor_ui = new MenuFolder("UI");
      {
        *patch_process_editor_ui +=
            new MenuEntry("Main Text Color" + kStable, nullptr,
                          PatchProcessUiMainTextColorEditor);
        *patch_process_editor_ui +=
            new MenuEntry("Window Title Color" + kStable, nullptr,
                          PatchProcessUiWindowTitleColorEditor);
        *patch_process_editor_ui +=
            new MenuEntry("Menu Selected Item Color" + kStable, nullptr,
                          PatchProcessUiMenuSelectedItemColorEditor);
        *patch_process_editor_ui +=
            new MenuEntry("Menu Unselected Item Color" + kStable, nullptr,
                          PatchProcessUiMenuUnselectedItemColorEditor);
        *patch_process_editor_ui +=
            new MenuEntry("Background Main Color" + kStable, nullptr,
                          PatchProcessUiBackgroundMainColorEditor);
        *patch_process_editor_ui +=
            new MenuEntry("Background Secondary Color" + kStable, nullptr,
                          PatchProcessUiBackgroundSecondaryColorEditor);
        *patch_process_editor_ui +=
            new MenuEntry("Background Border Color" + kStable, nullptr,
                          PatchProcessUiBackgroundBorderColorEditor);
      }
      *patch_process_editor += patch_process_editor_ui;

      auto *patch_process_editor_keyboard = new MenuFolder("Keyboard");
      {
        *patch_process_editor_keyboard +=
            new MenuEntry("Background" + kStable, nullptr,
                          PatchProcessKeyboardBackgroundColorEditor);
        *patch_process_editor_keyboard +=
            new MenuEntry("Key Background" + kStable, nullptr,
                          PatchProcessKeyboardKeyBackgroundColorEditor);
        *patch_process_editor_keyboard +=
            new MenuEntry("Key Background Pressed" + kStable, nullptr,
                          PatchProcessKeyboardKeyBackgroundPressedColorEditor);
        *patch_process_editor_keyboard +=
            new MenuEntry("Key Text" + kStable, nullptr,
                          PatchProcessKeyboardKeyTextColorEditor);
        *patch_process_editor_keyboard +=
            new MenuEntry("Key Text Pressed" + kStable, nullptr,
                          PatchProcessKeyboardKeyTextPressedColorEditor);
        *patch_process_editor_keyboard +=
            new MenuEntry("Key Text Disabled" + kStable, nullptr,
                          PatchProcessKeyboardKeyTextDisabledColorEditor);
        *patch_process_editor_keyboard += new MenuEntry(
            "Cursor" + kStable, nullptr, PatchProcessKeyboardCursorColorEditor);
        *patch_process_editor_keyboard += new MenuEntry(
            "Input" + kStable, nullptr, PatchProcessKeyboardInputColorEditor);
      }
      *patch_process_editor += patch_process_editor_keyboard;

      auto *patch_process_editor_custom_keyboard =
          new MenuFolder("Custom Keyboard");
      {
        *patch_process_editor_custom_keyboard +=
            new MenuEntry("Background Main" + kStable, nullptr,
                          PatchProcessCustomKeyboardBackgroundMainColorEditor);
        *patch_process_editor_custom_keyboard += new MenuEntry(
            "Background Secondary" + kStable, nullptr,
            PatchProcessCustomKeyboardBackgroundSecondaryColorEditor);
        *patch_process_editor_custom_keyboard += new MenuEntry(
            "Background Border" + kStable, nullptr,
            PatchProcessCustomKeyboardBackgroundBorderColorEditor);
        *patch_process_editor_custom_keyboard +=
            new MenuEntry("Key Background" + kStable, nullptr,
                          PatchProcessCustomKeyboardKeyBackgroundColorEditor);
        *patch_process_editor_custom_keyboard += new MenuEntry(
            "Key Background Pressed" + kStable, nullptr,
            PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor);
        *patch_process_editor_custom_keyboard +=
            new MenuEntry("Key Text" + kStable, nullptr,
                          PatchProcessCustomKeyboardKeyTextColorEditor);
        *patch_process_editor_custom_keyboard +=
            new MenuEntry("Key Text Pressed" + kStable, nullptr,
                          PatchProcessCustomKeyboardKeyTextPressedColorEditor);
        *patch_process_editor_custom_keyboard += new MenuEntry(
            "Scroll Bar Background" + kStable, nullptr,
            PatchProcessCustomKeyboardScrollBarBackgroundColorEditor);
        *patch_process_editor_custom_keyboard +=
            new MenuEntry("Scroll Bar Thumb" + kStable, nullptr,
                          PatchProcessCustomKeyboardScrollBarThumbColorEditor);
      }
      *patch_process_editor += patch_process_editor_custom_keyboard;

      *patch_process_editor += new MenuEntry("Set Default Theme" + kStable,
                                             nullptr, PatchProcessDefaultTheme);
      *patch_process_editor += new MenuEntry("Create Default File" + kStable,
                                             nullptr, CreateDefaultFile);
    }
    *bonus += patch_process_editor;

    *bonus += new MenuEntry("RGBチェッカー" + kStable, nullptr, RgbOutput,
                            "入力されたRGB値がどういう色かが分かります。");

    *bonus += EntryWithHotkey(
        new MenuEntry("アドレス監視" + kStable, HexEditor,
                      "アドレスと値の監視ができます。\nA+"
                      "↑で上に移動できます。\nA+↓で下に移動できます。"),
        {Hotkey(Key::R | A, "アドレス変更"), Hotkey(Key::R | B, "値を入力")});
    *bonus += new MenuEntry("時刻を確認" + kStable, nullptr, LocalTimeDisplay,
                            "時刻を表示します。");
    *bonus += new MenuEntry("3DSの情報を確認" + kStable, nullptr, Information,
                            "3DSの情報を確認できます。");
    *bonus += new MenuEntry(
        "フレンドコードシード値確認" + kStable, nullptr, [](MenuEntry *entry) {
          MessageBox(Utils::Format("%X", Security::GetFriendCodeSeed))();
        });
  }
  menu += bonus;
}

// Plugin menu
int main() {
  const std::string kTitle = "MHX3gx";
  const std::string kAbout =
      "データのバックアップは取ってください。\n"
      "プラグインを楽しんでください！\n"
      "Twitter @ponpoko094\n"
      "github.com/ponpoko094/MHX3gx";

  // タイトルやAbout等作成
  auto *menu = new PluginMenu(kTitle, 3, 0, 8, kAbout, 0);

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
