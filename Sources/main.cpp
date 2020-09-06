#include "common.hpp"

namespace CTRPluginFramework
{
    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern = {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003};

        Result res;
        Handle processHandle;
        s64 textTotalSize = 0;
        s64 startAddress = 0;
        u32 *found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if (R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
    exit:
        svcCloseHandle(processHandle);
    }

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const Hotkey &hotkey)
    {
        if (entry != nullptr)
        {
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

    static MenuEntry *EntryWithHotkey(MenuEntry *entry, const std::vector<Hotkey> &hotkeys)
    {
        if (entry != nullptr)
        {
            for (const Hotkey &hotkey : hotkeys)
                entry->Hotkeys += hotkey;
        }

        return (entry);
    }

    static MenuEntry *EnableEntry(MenuEntry *entry)
    {
        if (entry != nullptr)
        {
            entry->SetArg(new std::string(entry->Name()));
            entry->Enable();
        }
        return (entry);
    }

    // This function is called before main and before the game starts
    // Useful to do code edits safely
    void PatchProcess(FwkSettings &settings)
    {
        //	FwkSettings& settings = FwkSettings::Get();
        ToggleTouchscreenForceOn();
        //プラグインの設定
        settings.AllowActionReplay = false;   //アクションリプレイ
        settings.AllowSearchEngine = false;   //サーチ
        settings.WaitTimeToBoot = Seconds(3); //起動時間
        //UIの色
        settings.MainTextColor = Color(234, 145, 152);           //テキストの色
        settings.WindowTitleColor = Color(234, 145, 152);        //タイトルの色
        settings.MenuSelectedItemColor = Color(234, 145, 152);   //普通のメニューの色
        settings.MenuUnselectedItemColor = Color(234, 145, 152); //ActionReplayとかの色
        settings.BackgroundMainColor = Color::Black;             //背景の色
        settings.BackgroundSecondaryColor = Color::Black;        //背景の細線の色
        settings.BackgroundBorderColor = Color(234, 145, 152);   //背景の枠線の色
        //キーボードの色
        settings.Keyboard.KeyBackgroundPressed = Color::Black; //押された時の背景の色
        settings.Keyboard.KeyText = Color(234, 145, 152);      //数字の色
        settings.Keyboard.KeyTextPressed = Color::White;       //押された時の数字の色
        settings.Keyboard.Input = Color(234, 145, 152);        //上に表示されてる数字の色
        //カスタムキーボードの色
        settings.CustomKeyboard.BackgroundSecondary = Color::Black;      //歯車の背景細線の色
        settings.CustomKeyboard.BackgroundBorder = Color(234, 145, 152); //歯車の枠線の色
        settings.CustomKeyboard.KeyBackground = Color::Black;            //歯車のメニューの色
        settings.CustomKeyboard.KeyBackgroundPressed = Color::Black;     //歯車のメニューが押された時の色
        settings.CustomKeyboard.KeyText = Color(234, 145, 152);          //歯車のキーの色
        settings.CustomKeyboard.KeyTextPressed = Color::White;           //歯車のキーが押された時の色
        settings.CustomKeyboard.ScrollBarBackground = Color::Black;      //スクロールバーの背景の色
        settings.CustomKeyboard.ScrollBarThumb = Color(234, 145, 152);   //スクロールバーの動く色
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    // チートメニュー作成
    void InitMenu(PluginMenu &menu)
    {
        // Create your entries here, or elsewhere
        // You can create your entries whenever/wherever you feel like it

        MenuFolder *player = new MenuFolder(Color::Red << "プレイヤー");
        {

            MenuFolder *statusV2 = new MenuFolder(Color::Yellow << "ステータス変更");
            {
                *statusV2 += new MenuEntry(Color::Yellow << "攻撃力変更", AttackPowerChange, AttackPowerOption, Color::Yellow << "攻撃力を変更できます。");
                *statusV2 += new MenuEntry(Color::Yellow << "防御力変更", DefencePowerChange, DefencePowerOption, Color::Yellow << "防御力を変更できます。");
                *statusV2 += new MenuEntry(Color::Yellow << "属性値変更", AttributeChange, AttributeOption, Color::Yellow << "属性値を変更できます。");
                *statusV2 += new MenuEntry(Color::Yellow << "耐性値変更", ResistanceChange, ResistanceOption, Color::Yellow << "耐性値を変更できます。");
            }
            *player += statusV2;

            MenuFolder *playerChange = new MenuFolder(Color::Orange << "プレイヤー情報変更");
            {
                MenuFolder *hunterArt = new MenuFolder(Color::Yellow << "狩技変更");
                {
                    *hunterArt += new MenuEntry(Color::Yellow << "狩技1番目変更", nullptr, HunterArt1Change, Color::Yellow << "狩技の1番目を変更します。");
                    *hunterArt += new MenuEntry(Color::Yellow << "狩技2番目変更", nullptr, HunterArt2Change, Color::Yellow << "狩技の2番目を変更します。");
                    *hunterArt += new MenuEntry(Color::Yellow << "狩技3番目変更", nullptr, HunterArt3Change, Color::Yellow << "狩技の3番目を変更します。");
                }
                *playerChange += hunterArt;

                MenuFolder *skin = new MenuFolder(Color::SkyBlue << "肌の色変更", Color::Yellow << "RGBの値は、\nbit.ly/GetRGB\nを見て、入力してください。");
                {
                    *skin += new MenuEntry(Color::SkyBlue << "肌の色R値変更", nullptr, SkinRedChange, Color::Yellow << "肌の色の赤色を変更します。");
                    *skin += new MenuEntry(Color::SkyBlue << "肌の色G値変更", nullptr, SkinGreenChange, Color::Yellow << "肌の色の緑色を変更します。");
                    *skin += new MenuEntry(Color::SkyBlue << "肌の色B値変更", nullptr, SkinBlueChange, Color::Yellow << "肌の色の青色を変更します。");
                    *skin += new MenuEntry(Color::SkyBlue << "肌の色変更", nullptr, SkinColorChange, Color::Yellow << "肌の色を変更します。");
                }
                *playerChange += skin;

                MenuFolder *meal = new MenuFolder(Color::Magenta << "食事");
                {
                    MenuFolder *mealFlag = new MenuFolder(Color::ForestGreen << "フラグ");
                    {
                        *mealFlag += new MenuEntry(Color::ForestGreen << "食事無限", MealInfinite, Color::Yellow << "食事が無限にできます。");
                        *mealFlag += new MenuEntry(Color::ForestGreen << "高級お食事券効果付与", LuxuryCouponGrant, Color::Yellow << "高級お食事券の効果が付与されます。");
                        *mealFlag += new MenuEntry(Color::ForestGreen << "よろず焼きの依頼無限", MeetRequestInfinite, Color::Yellow << "よろず焼きの依頼が無限にできます。");
                    }
                    *meal += mealFlag;

                    MenuFolder *mealStatus = new MenuFolder(Color::Green << "ステータス");
                    {
                        MenuFolder *mealStatusResistance = new MenuFolder(Color::Lime << "耐性");
                        {
                            *mealStatusResistance += new MenuEntry(Color::Lime << "火耐性UP", MealFireResistanceUp, Color::Yellow << "火耐性が上昇します。");
                            *mealStatusResistance += new MenuEntry(Color::Lime << "水耐性UP", MealWaterResistanceUp, Color::Yellow << "水耐性が上昇します。");
                            *mealStatusResistance += new MenuEntry(Color::Lime << "雷耐性UP", MealThunderResistanceUp, Color::Yellow << "雷耐性が上昇します。");
                            *mealStatusResistance += new MenuEntry(Color::Lime << "氷耐性UP", MealIceResistanceUp, Color::Yellow << "氷耐性が上昇します。");
                            *mealStatusResistance += new MenuEntry(Color::Lime << "龍耐性UP", MealDragonResistanceUp, Color::Yellow << "龍耐性が上昇します。");
                        }
                        *mealStatus += mealStatusResistance;

                        *mealStatus += new MenuEntry(Color::Green << "体力UP", MealHpUp, Color::Yellow << "体力が上昇します。");
                        *mealStatus += new MenuEntry(Color::Green << "スタミナUP", MealStaminaUp, Color::Yellow << "スタミナが上昇します。");
                        *mealStatus += new MenuEntry(Color::Green << "攻撃力UP", MealAttackPowerUp, Color::Yellow << "攻撃力が上昇します。");
                        *mealStatus += new MenuEntry(Color::Green << "防御力UP", MealDefencePowerUp, Color::Yellow << "防御力が上昇します。");
                    }
                    *meal += mealStatus;

                    MenuFolder *mealSkill = new MenuFolder(Color::LimeGreen << "スキル");
                    {
                        *mealSkill += new MenuEntry(Color::LimeGreen << "スキル1", nullptr, MealSkill1Change, Color::Yellow << "食事スキルの1番目を変更します。");
                        *mealSkill += new MenuEntry(Color::LimeGreen << "スキル2", nullptr, MealSkill2Change, Color::Yellow << "食事スキルの2番目を変更します。");
                        *mealSkill += new MenuEntry(Color::LimeGreen << "スキル3", nullptr, MealSkill3Change, Color::Yellow << "食事スキルの3番目を変更します。");
                    }
                    *meal += mealSkill;
                }
                *playerChange += meal;

                *playerChange += new MenuEntry(Color::Orange << "声変更", nullptr, PlayerVoiceChange, Color::Yellow << "声を変更します。");
                *playerChange += new MenuEntry(Color::Orange << "目の色変更", nullptr, PlayerEyeColorChange, Color::Yellow << "目の色を変更します。");
                *playerChange += new MenuEntry(Color::Orange << "インナー変更", nullptr, PlayerInnerChange, Color::Yellow << "インナーを変更します。");
                *playerChange += new MenuEntry(Color::Orange << "性別変更", nullptr, PlayerGenderChange, Color::Yellow << "性別を変更します。");
                *playerChange += new MenuEntry(Color::Orange << "狩猟スタイル変更", nullptr, PlayerHuntingStyleChange, Color::Yellow << "狩猟スタイルを変更します。");
                *playerChange += new MenuEntry(Color::Orange << "髪型変更", nullptr, PlayerHearStyleChange, Color::Yellow << "髪型を変更します。");
                *playerChange += new MenuEntry(Color::Orange << "顔変更", nullptr, PlayerFaceChange, Color::Yellow << "顔を変更します。");
                *playerChange += new MenuEntry(Color::Orange << "メイク変更", nullptr, PlayerMakeChange, Color::Yellow << "メイクを変更します。");
            }
            *player += playerChange;

            *player += new MenuEntry(Color::Red << "攻撃力倍率変更", PlayerAttackPowerMagnificationChange, PlayerAttackPowerMagnificationOption, Color::Yellow << "Y+UPでON、Y+DOWNでOFF\n攻撃力の倍率を変更します。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "防御力倍率変更", playerDefencePowerMagnificationChange, PlayerDefencePowerMagnificationOption, Color::Yellow << "X+UPでON、X+DOWNでOFF\n防御力の倍率を変更します。\nCode by ymyn");
            *player += new MenuEntry(Color::Cyan << "速度変更", PlayerSpeedChange, PlayerSpeedOption, Color::Yellow << "SELECT+LでON、SELECT+RでOFF\n速度を変更します。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "プレイヤー座標移動", PlayerCoordinateModifier, Color::Yellow << "A+十字キーで移動できます。");
            *player += new MenuEntry(Color::Red << "ムーンジャンプ", PlayerMoonJump, Color::Yellow << "R+Bでジャンプできます。\n上がり続けるにはリピートムーブもオンにして、R+B+Yを押してください。");
            *player += new MenuEntry(Color::Red << "保存式テレポート", Teleport, Color::Yellow << "R + → 現在位置を読み込む。\nR + ← 現在位置に書き込む");
            *player += new MenuEntry(Color::Red << "他プレイヤーストーカー", stalker, Color::Yellow << "R+十字キーで追跡設定ができます。\nR↑ P1を追跡有効\nR+→ P2を追跡有効\nR+↓ P3を追跡有効\nR+←で追跡無効にできます。");
            *player += new MenuEntry(Color::Red << "リピートムーブ", Repeatmove, Color::Yellow << "B+Yで動きを繰り返します。");
            *player += new MenuEntry(Color::Red << "狩技解放", HunterArtRelease, Color::Yellow << "狩技を全て解放します。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "腹減り無効", HungryInvalid, Color::Yellow << "時間経過でスタミナが減らなくなります。");
            *player += new MenuEntry(Color::Red << "プレイヤーサイズ変更", HunterSizeChange, HunterSizeOption, Color::Yellow << "ハンターのサイズを変更できます。");
            *player += new MenuEntry(Color::Red << "HP無限", nullptr, InfiniteHP, Color::Yellow << "HPを無限にします。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "無敵", nullptr, Invincible, Color::Yellow << "無敵になります。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "スーパーアーマー", nullptr, SuperArmor, Color::Yellow << "スーパーアーマーになります。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "スタミナ無限", nullptr, InfiniteStamina, Color::Yellow << "スタミナを無限にします。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "狩技ゲージ無限", nullptr, InfiniteHunterArt, Color::Yellow << "狩技ゲージが無限になります。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "全スタイルで狩技3つ装着可能", nullptr, Always3HunterArtEquip, Color::Yellow << "全スタイルで狩技を3つ装着可能になります。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "常時地図表示", nullptr, AlwaysDisplayMap, Color::Yellow << "常に地図を表示します。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "常にモンスターペイント", nullptr, AlwaysPaint, Color::Yellow << "常にマップにモンスターが表示されます。\nCode by ymyn");
            *player += new MenuEntry(Color::Red << "スピードハック", nullptr, SpeedHack, Color::Yellow << "速度の変更ができます。");
            *player += new MenuEntry(Color::Red << "クエスト中スピードハック", nullptr, InQuestSpeedHack, Color::Yellow << "クエスト中での速度を変更できます。");
            *player += new MenuEntry(Color::Red << "走った時にムーンウォーク", nullptr, IfRunMoonWalk, Color::Yellow << "走った時にムーンウォークをします。");
            *player += new MenuEntry(Color::Red << "プレイヤー名前変更", nullptr, HunterNameChange, Color::Yellow << "定型文では1ページ目の一番左下にある定型文を名前にコピーします。\nキーボードでは、メニュー内で直接変更することができます。\n変換候補変換の改行やタブが使えます。");
        }
        menu += player;

        MenuFolder *item = new MenuFolder(Color::Orange << "アイテム");
        {
            MenuFolder *equipment = new MenuFolder(Color::Magenta << "装備");
            {
                MenuFolder *amulet = new MenuFolder(Color::Red << "護石編集", Color::Yellow << "編集したい護石を、装備BOX14ページ目の一番右下に移動させてください。\n14ページ目がない場合は、アイテムフォルダにある「ボックス1400個に拡張」をオンにしてください。");
                {
                    *amulet += new MenuEntry(Color::Red << "新護石作成", nullptr, AmuletCreate, Color::Yellow << "新たに護石を作成できます。");
                    *amulet += new MenuEntry(Color::Red << "護石種類変更", nullptr, AmuletTypeChange, Color::Yellow << "護石の種類を変更します。");
                    *amulet += new MenuEntry(Color::Red << "第一スキル変更", nullptr, AmuletSkill1Change, Color::Yellow << "第一スキルを変更します。");
                    *amulet += new MenuEntry(Color::Red << "第二スキル変更", nullptr, AmuletSkill2Change, Color::Yellow << "第二スキルを変更します。");
                    *amulet += new MenuEntry(Color::Red << "第一スキルポイント変更", nullptr, AmuletSkill1PointChange, Color::Yellow << "第一スキルポイントを変更します。");
                    *amulet += new MenuEntry(Color::Red << "第二スキルポイント変更", nullptr, AmuletSkill2PointChange, Color::Yellow << "第二スキルポイントを変更します。");
                    *amulet += new MenuEntry(Color::Red << "スロット数変更", nullptr, AmuletSlotChange, Color::Yellow << "スロット数を変更します。");
                }
                *equipment += amulet;

                MenuFolder *insect = new MenuFolder(Color::Cyan << "猟虫編集", Color::Yellow << "編集したい猟虫がついている操虫棍を、装備BOX14ページ目の一番下の右から4番目に移動させてください。\n14ページ目がない場合は、アイテムフォルダにある「ボックス1400個に拡張」をオンにしてください。");
                {
                    *insect += new MenuEntry(Color::Cyan << "猟虫種類変更", nullptr, InsectTypeChange, Color::Yellow << "猟虫の種類を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫レベル変更", nullptr, InsectLevelChange, Color::Yellow << "猟虫のレベルを変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫パワー補正変更", nullptr, InsectPowerChange, Color::Yellow << "猟虫のパワー補正を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫ウェイト補正変更", nullptr, InsectWeightChange, Color::Yellow << "猟虫のウェイト補正を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫スタミナ補正変更", nullptr, InsectStaminaChange, Color::Yellow << "猟虫のスタミナ補正を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫火属性変更", nullptr, InsectFireAttributeChange, Color::Yellow << "猟虫の火属性を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫水属性変更", nullptr, InsectWaterAttributeChange, Color::Yellow << "猟虫の水属性を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫雷属性変更", nullptr, InsectThunderAttributeChange, Color::Yellow << "猟虫の雷属性を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫氷属性変更", nullptr, InsectIceAttributeChange, Color::Yellow << "猟虫の氷属性を変更します。");
                    *insect += new MenuEntry(Color::Cyan << "猟虫龍属性変更", nullptr, InsectDragonAttributeChange, Color::Yellow << "猟虫の龍属性を変更します。");
                }
                *equipment += insect;

                *equipment += new MenuEntry(Color::Magenta << "他プレイヤーの装備コピー", nullptr, OtherPlayerEquipmentCopy, Color::Yellow << "コピーしたいプレイヤーが猫の場合、コピーしないでください。");
            }
            *item += equipment;

            *item += new MenuEntry(Color::Orange << "爆弾を無限に置ける", InfiniteBombPut, Color::Yellow << "見た目だけです。");
            *item += new MenuEntry(Color::Orange << "たんほれアイテムセット", TanhoreItemSet, Color::Yellow << "ポーチの\n1枠目を 燃石炭\n2枠目を ネコタクチケット\n3枠目を モドリ玉\nにします。");
            *item += new MenuEntry(Color::Orange << "所持金最大", nullptr, MoneyChange, Color::Yellow << "所持金を変更できます。");
            *item += new MenuEntry(Color::Orange << "龍歴院ポイント最大", nullptr, WycademyPointChange, Color::Yellow << "龍歴院ポイントを変更できます。");
            *item += new MenuEntry(Color::Orange << "アイテム&弾丸無限", nullptr, infitemammo, Color::Yellow << "アイテムと弾丸を無限にします。\nしゃがみの弾は無限になりません。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "素材無しで調合可能", nullptr, NoMaterialCompound, Color::Yellow << "素材無しで調合を可能にします。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "運搬物を持たずにポーチに入れる", nullptr, CargoPutInPorch, Color::Yellow << "運搬物がポーチに入ります。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "採取無限", nullptr, InfiniteCollect, Color::Yellow << "採集ポイントで無限に採取ができます。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "装備を素材無しで作れる", nullptr, NoMaterialEquipmentCreate, Color::Yellow << "素材なしで装備生産をすることができます。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "装備欄全て解放", nullptr, EquipmentAllRelease, Color::Yellow << "装備生産リストを全て解放します。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "全てのアイテム販売", nullptr, AllItemSold, Color::Yellow << "全てのアイテムがギルドストアや雑貨屋に売り出されます。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "ボックス1400個に拡張", nullptr, ItemBox1400Expansion, Color::Yellow << "ボックスのページを1400個に拡張します。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "持てるアイテム99個", nullptr, HaveItem99, Color::Yellow << "持てるアイテムの最大数を99個にします。\nCode by ymyn");
            *item += new MenuEntry(Color::Orange << "アイテムボックス編集", nullptr, ItemBoxEdit, Color::Yellow << "アイテムボックスの編集をします。");
            *item += new MenuEntry(Color::Orange << "アイテムマイセットをポーチにコピー", nullptr, MySetToPorchItemCopy, Color::Yellow << "アイテムマイセットに登録されているアイテムを、アイテムポーチにコピーします。");
            *item += new MenuEntry(Color::Orange << "納品アイテムをポーチにコピー", nullptr, DeliveryItemToPorchCopy, Color::Yellow << "納品アイテムを、アイテムポーチの1番目と2番目にコピーします。\n空きを作ってください。");
            *item += new MenuEntry(Color::Orange << "ポーチを納品アイテムにコピー", nullptr, PorchToDeliveryItemCopy, Color::Yellow << "アイテムポーチの1番目をメインの納品に、2番目をサブの納品にコピーします。\n空きを作ってください。");
            *item += new MenuEntry(Color::Orange << "ポーチのアイテム全消去", nullptr, PorchAllClear, Color::Yellow << "ポーチのアイテムを全消去します。\n消せないアイテムや、ボックスにしまえないアイテムがあるときに実行してください。");
            *item += new MenuEntry(Color::Orange << "特殊許可チケットの数変更", nullptr, SpecialPermitQuestTicketChange, Color::Yellow << "特殊許可チケットの枚数を変更します。");
        }
        menu += item;

        MenuFolder *weapon = new MenuFolder(Color::Yellow << "武器");
        {
            MenuFolder *weaponType = new MenuFolder(Color::Red << "武器別チート");
            {
                MenuFolder *gunlance = new MenuFolder(Color::Orange << "ガンランスチート");
                {
                    *gunlance += new MenuEntry(Color::Orange << "ヒートゲージ固定", GunlanceHeatGageFix, GunlanceHeatGageOption, Color::Yellow << "ヒートゲージを固定します。");
                    *gunlance += new MenuEntry(Color::Orange << "ガンランスの弾無限", GunlanceAmmoInfinite, Color::Yellow << "ガンランスの弾を無限にします。");
                    *gunlance += new MenuEntry(Color::Orange << "オーバーヒート無効", GunlanceInvalidOverHeat, Color::Yellow << "オーバーヒートを無効にします。");
                }
                *weaponType += gunlance;

                MenuFolder *insectGlaive = new MenuFolder(Color::Green << "操虫棍チート");
                {
                    *insectGlaive += new MenuEntry(Color::Green << "常時トリプルアップ", InsectGlaiveAlwaysTripleUp, Color::Yellow << "常時トリプルアップになります。");
                    *insectGlaive += new MenuEntry(Color::Green << "虫のスタミナ無限", InsectGlaiveInsectStaminaInfinite, Color::Yellow << "虫のスタミナが無限になります。");
                }
                *weaponType += insectGlaive;

                MenuFolder *bowgun = new MenuFolder(Color::Magenta << "ボウガンチート");
                {
                    *bowgun += new MenuEntry(Color::Magenta << "ボウガンの弾無限", BowgunAmmoInfinite, Color::Yellow << "ボウガンの弾が無限になります。");
                    *bowgun += new MenuEntry(Color::Magenta << "しゃがみの弾無限", BowgunCrouchingShot, Color::Yellow << "しゃがみ撃ちの弾が無限になります。");
                }
                *weaponType += bowgun;

                *weaponType += new MenuEntry(Color::Red << "溜め段階固定", ChargeStageFix, ChageStageOption, Color::Yellow << "大剣などの溜め段階を固定します。");
                *weaponType += new MenuEntry(Color::Red << "武器ゲージ固定", WeaponGageFix, Color::Yellow << "太刀や双剣のゲージを固定します。");
                *weaponType += new MenuEntry(Color::Red << "チャージアックスビン固定", ChargeAxeBinFix, Color::Yellow << "チャージアックスのビン数を固定します。");
                *weaponType += new MenuEntry(Color::Red << "狩猟笛の全効果付与", HuntingHornAllEffectGrant, Color::Yellow << "反映されない効果があります。");
            }
            *weapon += weaponType;

            *weapon += new MenuEntry(Color::Yellow << "属性値変更", nullptr, AttributePointChange, Color::Yellow << "属性値を変更できます。");
            *weapon += new MenuEntry(Color::Yellow << "モーション無し", nullptr, NoMotion, Color::Yellow << "モーションを無くします。\nCode by 舞姫");
            *weapon += new MenuEntry(Color::Yellow << "会心率100%", nullptr, CriticalRate100, Color::Yellow << "会心率が100%になります。\nCode by Fort42");
            *weapon += new MenuEntry(Color::Yellow << "ボウガン自動装填", nullptr, BowgunAutoReload, Color::Yellow << "ボウガンの弾が自動で装填されます。\nCode by ymyn");
            *weapon += new MenuEntry(Color::Yellow << "斬れ味無限", nullptr, InfiniteSharpness, Color::Yellow << "斬れ味が無限になります。\nCode by ymyn");
            *weapon += new MenuEntry(Color::Yellow << "斬れ味+2", nullptr, SharpnessPlus2, Color::Yellow << "斬れ味レベル+2の効果を付与します。\nCode by Fort42");
            *weapon += new MenuEntry(Color::Yellow << "高速溜め短縮", nullptr, ChargeSpeedUp, Color::Yellow << "大剣等の溜めが短縮されます。\nCode by Fort42");
            *weapon += new MenuEntry(Color::Yellow << "チャージゲージ最大", nullptr, ChargeGageMax, Color::Yellow << "チャージゲージが最大になります。\nCode by Fort42");
        }
        menu += weapon;

        MenuFolder *monster = new MenuFolder(Color::Green << "モンスター", Color::Yellow << "オンラインだとラグがあったり、使えない場合があります。");
        {
            MenuFolder *monsterDisplay = new MenuFolder(Color::LimeGreen << "モンスター情報画面表示");
            {
                *monsterDisplay += new MenuEntry(Color::LimeGreen << "1番目のモンスターのHP表示", Monster1HpDisplay, Color::Yellow << "1番目のモンスターのHPを画面上に表示します。");
                *monsterDisplay += new MenuEntry(Color::LimeGreen << "2番目のモンスターのHP表示", Monster2HpDisplay, Color::Yellow << "2番目のモンスターのHPを画面上に表示します。");
                *monsterDisplay += new MenuEntry(Color::LimeGreen << "1番目のモンスターのサイズ倍率表示", Monster1SizeMagnificationDisplay, Color::Yellow << "1番目のモンスターのサイズ倍率を画面上に表示します。\n1.2付近がキンズサイズ、0.9付近がスモールサイズの目安です。");
                *monsterDisplay += new MenuEntry(Color::LimeGreen << "2番目のモンスターのサイズ倍率表示", Monster2SizeMagnificationDisplay, Color::Yellow << "2番目のモンスターのサイズ倍率を画面上に表示します。\n1.2付近がキングサイズ、0.9付近がスモールサイズの目安です。");
            }
            *monster += monsterDisplay;

            *monster += new MenuEntry(Color::Green << "乗り成功", RideGageMax, Color::Yellow << "ハンターの乗りゲージを最大にします。\nモンスターの乗りゲージが増えないようにします。");
            *monster += new MenuEntry(Color::Green << "モンスター座標移動", MonsterCoordinateModifier, Color::Yellow << "1番目のモンスターはX+十字キーで操作できます。\n2番目のモンスターはX+スライドパッドで操作できます。\n操作したいモンスターと同じエリアにいてください。");
            *monster += new MenuEntry(Color::Green << "モンスターストーカー", MonsterStalker, Color::Yellow << "1番目のモンスターはX+R+↑で追跡有効にできます。\n2番目のモンスターはX+L+↑で追跡有効にできます。\nX+R+↓で追跡停止できます。\n追跡したいモンスターと同じエリアにいてください。");
            *monster += new MenuEntry(Color::Green << "モンスターリピートムーブ", MonsterActionRepeat, MonsterActionRepeatOption, Color::Yellow << "リピートムーブの挙動の変更と、操作のオンオフができます。\n1番目のモンスターはX+R+→で操作できます。\n2番目のモンスターはX+L+→で操作できます。\n操作したいモンスターと同じエリアにいてください。");
            *monster += new MenuEntry(Color::Green << "1番目と2番目のモンスターの動き停止", Monster1And2Stop, Color::Yellow << "動き停止は、速度変更より優先されます。");
            *monster += new MenuEntry(Color::Green << "1番目のモンスターのサイズ変更", Monster1SizeChange, Monster1SizeOption, Color::Yellow << "1番目のモンスターのサイズの変更ができます。");
            *monster += new MenuEntry(Color::Green << "2番目のモンスターのサイズ変更", Monster2SizeChange, Monster2SizeOption, Color::Yellow << "2番目のモンスターのサイズの変更ができます。");
            *monster += new MenuEntry(Color::Green << "1番目のモンスターの速度倍率変更", Monster1SpeedAttributeChange, Monster1SpeedAttributeOption, Color::Yellow << "1番目のモンスターの速度の変更ができます。");
            *monster += new MenuEntry(Color::Green << "2番目のモンスターの速度倍率変更", Monster2SpeedAttributeChange, Monster2SpeedAttributeOption, Color::Yellow << "2番目のモンスターの速度の変更ができます。");
            *monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター常時毒", Monster1And2AlwaysPoison, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
            *monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター常時麻痺", Monster1And2AlwaysParalysis, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
            *monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター常時睡眠", Monster1And2AlwaysSleep, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
            *monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター透明化", nullptr, Monster1And2AlwaysInvisible, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
            *monster += new MenuEntry(Color::Green << "瞬殺", nullptr, OneAttackKill, Color::Yellow << "モンスターを瞬殺できます。\nCode by 舞姫");
        }
        menu += monster;

        MenuFolder *palico = new MenuFolder(Color::Blue << "ねこ");
        {
            *palico += new MenuEntry(Color::Magenta << "ねこの攻撃力倍率変更", PalicoAttackPowerMagnificationChange, PalicoAttackPowerMagnificationOption, Color::Yellow << "Y+UPでON、Y+DOWNでOFF\nねこの攻撃力の倍率を変更します。\nCode by Fort42");
            *palico += new MenuEntry(Color::Cyan << "ねこの防御力倍率変更", PalicoDefencePowerMagnificationChange, PalicoDefencePowerMagnificationOption, Color::Yellow << "X+UPでON、X+DOWNでOFF\nねこの防御力変更の倍率を変更します。\nCode by Fort42");

            MenuFolder *palicoEdit = new MenuFolder(Color::LimeGreen << "ねこ編集");
            {
                *palicoEdit += new MenuEntry(Color::LimeGreen << "ねこ選択", nullptr, PalicoChoice, Color::Yellow << "編集するねこを選択します。");

                MenuFolder *palicoEquipmentSupportAction = new MenuFolder(Color::Magenta << "装備サポート行動");
                {
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動1番目変更", nullptr, PalicoEquipmentSupportAction1Change, Color::Yellow << "ねこの装備サポート行動の1番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動2番目変更", nullptr, PalicoEquipmentSupportAction2Change, Color::Yellow << "ねこの装備サポート行動の2番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動3番目変更", nullptr, PalicoEquipmentSupportAction3Change, Color::Yellow << "ねこの装備サポート行動の3番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動4番目変更", nullptr, PalicoEquipmentSupportAction4Change, Color::Yellow << "ねこの装備サポート行動の4番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動5番目変更", nullptr, PalicoEquipmentSupportAction5Change, Color::Yellow << "ねこの装備サポート行動の5番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動6番目変更", nullptr, PalicoEquipmentSupportAction6Change, Color::Yellow << "ねこの装備サポート行動の6番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動7番目変更", nullptr, PalicoEquipmentSupportAction7Change, Color::Yellow << "ねこの装備サポート行動の7番目を変更します。");
                    *palicoEquipmentSupportAction += new MenuEntry(Color::Magenta << "装備サポート行動8番目変更", nullptr, PalicoEquipmentSupportAction8Change, Color::Yellow << "ねこの装備サポート行動の8番目を変更します。");
                }
                *palicoEdit += palicoEquipmentSupportAction;

                MenuFolder *palicoEquipmentSkill = new MenuFolder(Color::Cyan << "装備オトモスキル");
                {
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル1番目変更", nullptr, PalicoEquipmentSkill1Change, Color::Yellow << "ねこの装備オトモスキルの1番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル2番目変更", nullptr, PalicoEquipmentSkill2Change, Color::Yellow << "ねこの装備オトモスキルの2番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル3番目変更", nullptr, PalicoEquipmentSkill3Change, Color::Yellow << "ねこの装備オトモスキルの3番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル4番目変更", nullptr, PalicoEquipmentSkill4Change, Color::Yellow << "ねこの装備オトモスキルの4番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル5番目変更", nullptr, PalicoEquipmentSkill5Change, Color::Yellow << "ねこの装備オトモスキルの5番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル6番目変更", nullptr, PalicoEquipmentSkill6Change, Color::Yellow << "ねこの装備オトモスキルの6番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル7番目変更", nullptr, PalicoEquipmentSkill7Change, Color::Yellow << "ねこの装備オトモスキルの7番目を変更します。");
                    *palicoEquipmentSkill += new MenuEntry(Color::Cyan << "装備オトモスキル8番目変更", nullptr, PalicoEquipmentSkill8Change, Color::Yellow << "ねこの装備オトモスキルの8番目を変更します。");
                }
                *palicoEdit += palicoEquipmentSkill;

                MenuFolder *palicoLearnSupportAction = new MenuFolder(Color::Orange << "習得サポート行動");
                {
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動1番目変更", nullptr, PalicoLearnSupportAction1Change, Color::Yellow << "ねこの習得サポート行動の1番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動2番目変更", nullptr, PalicoLearnSupportAction2Change, Color::Yellow << "ねこの習得サポート行動の2番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動3番目変更", nullptr, PalicoLearnSupportAction3Change, Color::Yellow << "ねこの習得サポート行動の3番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動4番目変更", nullptr, PalicoLearnSupportAction4Change, Color::Yellow << "ねこの習得サポート行動の4番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動5番目変更", nullptr, PalicoLearnSupportAction5Change, Color::Yellow << "ねこの習得サポート行動の5番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動6番目変更", nullptr, PalicoLearnSupportAction6Change, Color::Yellow << "ねこの習得サポート行動の6番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動7番目変更", nullptr, PalicoLearnSupportAction7Change, Color::Yellow << "ねこの習得サポート行動の7番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動8番目変更", nullptr, PalicoLearnSupportAction8Change, Color::Yellow << "ねこの習得サポート行動の8番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動9番目変更", nullptr, PalicoLearnSupportAction9Change, Color::Yellow << "ねこの習得サポート行動の9番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動10番目変更", nullptr, PalicoLearnSupportAction10Change, Color::Yellow << "ねこの習得サポート行動の10番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動11番目変更", nullptr, PalicoLearnSupportAction11Change, Color::Yellow << "ねこの習得サポート行動の11番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動12番目変更", nullptr, PalicoLearnSupportAction12Change, Color::Yellow << "ねこの習得サポート行動の12番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動13番目変更", nullptr, PalicoLearnSupportAction13Change, Color::Yellow << "ねこの習得サポート行動の13番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動14番目変更", nullptr, PalicoLearnSupportAction14Change, Color::Yellow << "ねこの習得サポート行動の14番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動15番目変更", nullptr, PalicoLearnSupportAction15Change, Color::Yellow << "ねこの習得サポート行動の15番目を変更します。");
                    *palicoLearnSupportAction += new MenuEntry(Color::Orange << "習得サポート行動16番目変更", nullptr, PalicoLearnSupportAction16Change, Color::Yellow << "ねこの習得サポート行動の16番目を変更します。");
                }
                *palicoEdit += palicoLearnSupportAction;

                MenuFolder *palicoLearnSkill = new MenuFolder(Color::Green << "習得オトモスキル");
                {
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル1番目変更", nullptr, PalicoLearnSupportSkill1Change, Color::Yellow << "ねこの習得オトモスキルの1番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル2番目変更", nullptr, PalicoLearnSupportSkill2Change, Color::Yellow << "ねこの習得オトモスキルの2番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル3番目変更", nullptr, PalicoLearnSupportSkill3Change, Color::Yellow << "ねこの習得オトモスキルの3番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル4番目変更", nullptr, PalicoLearnSupportSkill4Change, Color::Yellow << "ねこの習得オトモスキルの4番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル5番目変更", nullptr, PalicoLearnSupportSkill5Change, Color::Yellow << "ねこの習得オトモスキルの5番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル6番目変更", nullptr, PalicoLearnSupportSkill6Change, Color::Yellow << "ねこの習得オトモスキルの6番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル7番目変更", nullptr, PalicoLearnSupportSkill7Change, Color::Yellow << "ねこの習得オトモスキルの7番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル8番目変更", nullptr, PalicoLearnSupportSkill8Change, Color::Yellow << "ねこの習得オトモスキルの8番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル9番目変更", nullptr, PalicoLearnSupportSkill9Change, Color::Yellow << "ねこの習得オトモスキルの9番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル10番目変更", nullptr, PalicoLearnSupportSkill10Change, Color::Yellow << "ねこの習得オトモスキルの10番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル11番目変更", nullptr, PalicoLearnSupportSkill11Change, Color::Yellow << "ねこの習得オトモスキルの11番目を変更します。");
                    *palicoLearnSkill += new MenuEntry(Color::Green << "習得オトモスキル12番目変更", nullptr, PalicoLearnSupportSkill12Change, Color::Yellow << "ねこの習得オトモスキルの12番目を変更します。");
                }
                *palicoEdit += palicoLearnSkill;

                MenuFolder *palicoAppearance = new MenuFolder(Color::ForestGreen << "見た目");
                {
                    MenuFolder *palicoAppearanceColor = new MenuFolder(Color::Green << "見た目の色変更");
                    {
                        MenuFolder *palicoBodyHairColor = new MenuFolder(Color::Magenta << "毛色");
                        {
                            *palicoBodyHairColor += new MenuEntry(Color::Magenta << "R値変更", nullptr, PalicoBodyHairColorRedChange, Color::Yellow << "ねこの毛色の赤色を変更します。");
                            *palicoBodyHairColor += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, PalicoBodyHairColorGreenChange, Color::Yellow << "ねこの毛色の緑色を変更します。");
                            *palicoBodyHairColor += new MenuEntry(Color::Cyan << "B値変更", nullptr, PalicoBodyHairColorBlueChange, Color::Yellow << "ねこの毛色の青色を変更します。");
                        }
                        *palicoAppearanceColor += palicoBodyHairColor;

                        MenuFolder *palicoRightEyeColor = new MenuFolder(Color::Cyan << "右目の色");
                        {
                            *palicoRightEyeColor += new MenuEntry(Color::Magenta << "R値変更", nullptr, PalicoRightEyeColorRedChange, Color::Yellow << "ねこの右目の赤色を変更します。");
                            *palicoRightEyeColor += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, PalicoRightEyeColorGreenChange, Color::Yellow << "ねこの右目の緑色を変更します。");
                            *palicoRightEyeColor += new MenuEntry(Color::Cyan << "B値変更", nullptr, PalicoRightEyeColorBlueChange, Color::Yellow << "ねこの右目の青色を変更します。");
                        }
                        *palicoAppearanceColor += palicoRightEyeColor;

                        MenuFolder *palicoLeftEyeColor = new MenuFolder(Color::LimeGreen << "左目の色");
                        {
                            *palicoLeftEyeColor += new MenuEntry(Color::Magenta << "R値変更", nullptr, PalicoLeftEyeColorRedChange, Color::Yellow << "ねこの左目の赤色を変更します。");
                            *palicoLeftEyeColor += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, PalicoLeftEyeColorGreenChange, Color::Yellow << "ねこの左目の緑色を変更します。");
                            *palicoLeftEyeColor += new MenuEntry(Color::Cyan << "B値変更", nullptr, PalicoLeftEyeColorBlueChange, Color::Yellow << "ねこの左目の青色を変更します。");
                        }
                        *palicoAppearanceColor += palicoLeftEyeColor;

                        MenuFolder *palicoInnerColor = new MenuFolder(Color::Yellow << "インナーの色");
                        {
                            *palicoInnerColor += new MenuEntry(Color::Magenta << "R値変更", nullptr, PalicoInnerColorRedChange, Color::Yellow << "ねこのインナーの色の赤色を変更します。");
                            *palicoInnerColor += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, PalicoInnerColorGreenChange, Color::Yellow << "ねこのインナーの色の緑色を変更します。");
                            *palicoInnerColor += new MenuEntry(Color::Cyan << "B値変更", nullptr, PalicoInnerColorBlueChange, Color::Yellow << "ねこのインナーの色の青色を変更します。");
                        }
                        *palicoAppearanceColor += palicoInnerColor;
                    }
                    *palicoAppearance += palicoAppearanceColor;

                    *palicoAppearance += new MenuEntry(Color::ForestGreen << "声変更", nullptr, PalicoVoiceChange, Color::Yellow << "ねこの声を変更します。");
                    *palicoAppearance += new MenuEntry(Color::ForestGreen << "目変更", nullptr, PalicoEyeChange, Color::Yellow << "ねこの目を変更します。");
                    *palicoAppearance += new MenuEntry(Color::ForestGreen << "インナー変更", nullptr, PalicoInnerChange, Color::Yellow << "ねこのインナーを変更します。");
                    *palicoAppearance += new MenuEntry(Color::ForestGreen << "毛並み変更", nullptr, PalicoFurCoatChange, Color::Yellow << "ねこの毛並みを変更します。");
                    *palicoAppearance += new MenuEntry(Color::ForestGreen << "耳変更", nullptr, PalicoEarChange, Color::Yellow << "ねこの耳を変更します。");
                    *palicoAppearance += new MenuEntry(Color::ForestGreen << "尻尾変更", nullptr, PalicoTailChange, Color::Yellow << "ねこの尻尾を変更します。");
                }
                *palicoEdit += palicoAppearance;

                *palicoEdit += new MenuEntry(Color::LimeGreen << "経験値変更", nullptr, PalicoExperienceChange, Color::Yellow << "ねこの経験値を変更します。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "レベル変更", nullptr, ParicoLevelChange, Color::Yellow << "ねこのレベルを変更します。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "サポート傾向変更", nullptr, ParicoSupportTrendChange, Color::Yellow << "ねこのサポート傾向を変更します。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "親密度変更", nullptr, PalicoClosenessChange, Color::Yellow << "ねこの親密度を変更します。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "ターゲット変更", nullptr, PalicoTargetChange, Color::Yellow << "ねこのターゲットを変更します。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "オトモコメント編集可能変更", nullptr, PalicoCommentEditPossibleChange, Color::Yellow << "ねこのオトモコメントを編集可能にするか選べます。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "特別配信表示変更", nullptr, SpecialDeliveryDisplayChange, Color::Yellow << "ねこの特別配信の表示を変更します。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "名前変更", nullptr, PalicoNameChange, Color::Yellow << "ねこの名前を変更します。\n定型文では1ページ目の一番左下にある定型文をねこの名前にコピーします。\nキーボードでは、メニュー内で直接変更することができます。\n変換候補変換の改行やタブが使えます。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "コメント変更", nullptr, PalicoCommentChange, Color::Yellow << "ねこのコメントを変更します。\n定型文では1ページ目の一番左下にある定型文をねこのコメントにコピーします。\nキーボードでは、メニュー内で直接変更することができます。\n変換候補変換の改行やタブが使えます。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "名付け親変更", nullptr, PalicoGodParentChange, Color::Yellow << "ねこの名付け親を変更します。\n定型文では1ページ目の一番左下にある定型文をねこの名付け親にコピーします。\nキーボードでは、メニュー内で直接変更することができます。\n変換候補変換の改行やタブが使えます。");
                *palicoEdit += new MenuEntry(Color::LimeGreen << "先代旦那さん変更", nullptr, PalicoPredecessorHusbandChange, Color::Yellow << "ねこの先代旦那さんを変更します。\n定型文では1ページ目の一番左下にある定型文をねこの先代旦那さんにコピーします。\nキーボードでは、メニュー内で直接変更することができます。\n変換候補変換の改行やタブが使えます。");
            }
            *palico += palicoEdit;

            *palico += new MenuEntry(Color::Blue << "ねこ吸収", PalicoAbsorption, Color::Yellow << "ねこをハンターに吸収させます。\n他プレイヤーからは見えません。");
            *palico += new MenuEntry(Color::Blue << "サポートゲージ最大", ProwlerSupportGageMax, Color::Yellow << "ニャンターのサポートゲージを最大にします。");
        }
        menu += palico;

        MenuFolder *other = new MenuFolder(Color::Purple << "その他");
        {
            MenuFolder *chat = new MenuFolder(Color::Magenta << "チャット");
            {
                *chat += new MenuEntry(Color::Magenta << "チャット無限", ChatInfinite, Color::Yellow << "オンラインで赤文字を出現させなくします。");
                *chat += new MenuEntry(Color::Magenta << "変換候補変換", ChatConversionChange, Color::Yellow << "キーボードを開いて、Rを押しながら文字を打つことで、変換候補の文字が変わります。");
                *chat += new MenuEntry(Color::Magenta << "変換候補変換対応文字一覧", nullptr, ChatConversionList, Color::Yellow << "変換対応文字が書かれています。\n変換しづらい文字や、改造でしか入力できない文字を入れています。");
            }
            *other += chat;

            MenuFolder *drunk = new MenuFolder(Color::Cyan << "酔っぱらい", Color::Yellow << "クエスト中は酔っぱらえません。");
            {
                *drunk += new MenuEntry(Color::Cyan << "即酔っぱらい", InstantDrunk, InstantDrunkOption, Color::Yellow << "酔っぱらいになるか変更できます。");
                *drunk += new MenuEntry(Color::Cyan << "1回お酒を飲むと酔っぱらい", Drunk1, Color::Yellow << "1回お酒を飲むと酔っぱらいになります。");
            }
            *other += drunk;

            MenuFolder *hunterRank = new MenuFolder(Color::LimeGreen << "ハンターランク");
            {
                *hunterRank += new MenuEntry(Color::LimeGreen << "ハンターランク変更", nullptr, HunterRankChange, Color::Yellow << "ハンターランクを変更できます。");
                *hunterRank += new MenuEntry(Color::LimeGreen << "ハンターランクポイント変更", nullptr, HunterRankPointChange, Color::Yellow << "ハンターランクポイントを変更できます。");
            }
            *other += hunterRank;

            MenuFolder *fenyAndPugy = new MenuFolder(Color::Orange << "プーギー&フェニー");
            {
                *fenyAndPugy += new MenuEntry(Color::Orange << "フェニー&プーギーの服変更", nullptr, FenyAndPugyClothes, Color::Yellow << "フェニー&プーギーの服を変更できます。");
                *fenyAndPugy += new MenuEntry(Color::Orange << "定型文でフェニー&プーギーの名前変更", nullptr, FenyAndPugyNameChange, Color::Yellow << "1ページ目の一番左下にある定型文を名前にコピーします。\nフェニー&プーギーの名前を変更できます。");
            }
            *other += fenyAndPugy;

            MenuFolder *quest = new MenuFolder(Color::Yellow << "クエスト");
            {
                *quest += new MenuEntry(Color::Yellow << "クエストステータス変更", QuestClear, QuestClearOption, Color::Yellow << "クエストクリアか失敗を選択できます。");
                *quest += new MenuEntry(Color::Yellow << "クエストクリア後即リザルト", QuestWaitSkip, Color::Yellow << "クエストクリア後の待ち時間をスキップします。");
                *quest += new MenuEntry(Color::Yellow << "報酬画面スキップ", QuestResultSkip, Color::Yellow << "報酬受取の時間を0にし、スキップします。");
                *quest += new MenuEntry(Color::Yellow << "最大ダウン回数変更", QuestDownMaxChange, QuestDownMaxOption, Color::Yellow << "最大ダウン回数を変更できます。");
                *quest += new MenuEntry(Color::Yellow << "現在のダウン回数変更", QuestDownNowChange, QuestDownNowOption, Color::Yellow << "現在のダウン回数を変更します。");
                *quest += new MenuEntry(Color::Yellow << "クエスト残り時間表示", QuestTimeDisplay, Color::Yellow << "QT = Quest Timeです。\n時:分:秒:フレーム\nと表示します。");
                *quest += new MenuEntry(Color::Yellow << "選択肢を固定", SaveScreenFix, SaveScreenOption, Color::Yellow << "Rボタンを押すと固定できます。");
                *quest += new MenuEntry(Color::Yellow << "クエスト時間停止", nullptr, QuestTimeStop, Color::Yellow << "クエスト時間を停止します。\nCode by 舞姫");
                *quest += new MenuEntry(Color::Yellow << "全クエストクリア変更", nullptr, AllQuestClearChange, Color::Yellow << "ストーリーに不具合が起きる可能性があります。\n予めバックアップを取ったり、サブキャラクターで実行してください。");
            }
            *other += quest;

            MenuFolder *base = new MenuFolder(Color::Lime << "集会所");
            {
                MenuFolder *baseCreate = new MenuFolder(Color::Magenta << "集会所を作る");
                {
                    *baseCreate += new MenuEntry(Color::Magenta << "ターゲット変更", nullptr, BaseCreateTargetChange, Color::Yellow << "ターゲットを？？？？？にできます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "クエスト形式変更", nullptr, BaseCreateQuestTypeChange, Color::Yellow << "クエスト形式を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "募集HR下限変更", nullptr, BaseCreateRecruitmentHunterRankMinimumChange, Color::Yellow << "募集HRの下限を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "募集HR上限変更", nullptr, BaseCreateRecruitmentHunterRankMaximumChange, Color::Yellow << "募集HRの上限を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "入室人数変更", nullptr, BaseCreateEntryPeopleChange, Color::Yellow << "入室人数を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "入室制限変更", nullptr, BaseCreateEntryLimitChange, Color::Yellow << "入室制限を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "パスワード有無変更", nullptr, BaseCreatePasswordExistChange, Color::Yellow << "パスワードの有無を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "募集文①変更", nullptr, BaseCreateRecruitmentMessage1Change, Color::Yellow << "募集文①を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "募集文②変更", nullptr, BaseCreateRecruitmentMessage2Change, Color::Yellow << "募集文②を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "募集文③変更", nullptr, BaseCreateRecruitmentMessage3Change, Color::Yellow << "募集文③を変更できます。");
                    *baseCreate += new MenuEntry(Color::Magenta << "募集文④変更", nullptr, BaseCreateRecruitmentMessage4Change, Color::Yellow << "募集文④を変更できます。");
                }
                *base += baseCreate;

                MenuFolder *baseSearch = new MenuFolder(Color::Cyan << "集会所を探す");
                {
                    *baseSearch += new MenuEntry(Color::Cyan << "ターゲット変更", nullptr, BaseSearchTargetChange, Color::Yellow << "ターゲットを？？？？？にできます。");
                    *baseSearch += new MenuEntry(Color::Cyan << "クエスト形式変更", nullptr, BaseSearchQuestTypeChange, Color::Yellow << "クエスト形式を変更できます。");
                    *baseSearch += new MenuEntry(Color::Cyan << "ホストHR下限変更", nullptr, BaseSearchHostHunterRankMinimumChange, Color::Yellow << "ホストHRの下限を変更できます");
                    *baseSearch += new MenuEntry(Color::Cyan << "ホストHR上限変更", nullptr, BaseSearchHostHunterRankMaximumChange, Color::Yellow << "ホストHRの上限を変更できます");
                    *baseSearch += new MenuEntry(Color::Cyan << "クエスト中変更", nullptr, BaseSearchInQuestChange, Color::Yellow << "クエスト中を変更できます。");
                    *baseSearch += new MenuEntry(Color::Cyan << "パスワード有無変更", nullptr, BaseSearchPasswordExistChange, Color::Yellow << "パスワードの有無を変更できます。");
                }
                *base += baseSearch;
            }
            *other += base;

            *other += new MenuEntry(Color::Purple << "画面に集会所のパス表示", DisplayBasePassword, Color::Yellow << "現在の部屋のパスワードを表示します。");
            *other += new MenuEntry(Color::Purple << "パスワード無効", Color::Yellow << "荒らしが可能となるので入れていません。");
            *other += new MenuEntry(Color::Purple << "主権限を自プレイヤーに変更", Color::Yellow << "荒らしが可能となるので入れていません。");
            *other += new MenuEntry(Color::Purple << "プレイヤーの現在座標表示", DisplayPlayerCoordinate, Color::Yellow << "プレイヤーの現在座標を表示します。");
            *other += new MenuEntry(Color::Purple << "宙に浮くバグ", FloatBug, Color::Yellow << "L+Selectでオン、R+Selectでオフにできます。\n高確率でエラーになります。注意してオンにしてください。\nCode by 舞姫");
            *other += new MenuEntry(Color::Purple << "視野角変更", ViewingAngleChange, ViewingAngleOption, Color::Yellow << "視野角を変更します。\n(画面酔い注意)");
            *other += new MenuEntry(Color::Purple << "視野角変更改良版", nullptr, ViewingAngleChangeV2, Color::Yellow << "視野の倍率を変更できます。");
            *other += new MenuEntry(Color::Purple << "武器サイズ変更", nullptr, WeaponSizeChange, Color::Yellow << "武器のサイズを変更できます。");
            *other += new MenuEntry(Color::Purple << "画面の明るさ変更", nullptr, ContrastChange, Color::Yellow << "画面の明るさ変更を変更できます。");
            *other += new MenuEntry(Color::Purple << "ギルドカード情報変更", nullptr, GuildCardChange, Color::Yellow << "ギルドカードの情報を変更できます。\n頑張って作りました。()");
            *other += new MenuEntry(Color::Purple << "リージョン変更", nullptr, RegionChange, Color::Yellow << "日本かヨーロッパに変更できます。");
            *other += new MenuEntry(Color::Purple << "村の貢献度変更", nullptr, VillageContributionPointChange, Color::Yellow << "村の貢献度を変更します。");
            *other += new MenuEntry(Color::Purple << "ルームサービス変更", nullptr, RoomServiceChange, Color::Yellow << "ルームサービスを変更します。");
            *other += new MenuEntry(Color::Purple << "障害物無視", nullptr, WallThrough, Color::Yellow << "障害物を無視するかどうか選択できます。\nCode by 舞姫");
            *other += new MenuEntry(Color::Purple << "最大FPS変更", nullptr, MaximumFpsChange, Color::Yellow << "最大FPSを変更できます。");
        }
        menu += other;

        MenuFolder *bonus = new MenuFolder(Color::Magenta << "おまけ");
        {
            MenuFolder *conversion = new MenuFolder(Color::Cyan << "変換");
            {
                *conversion += new MenuEntry(Color::Cyan << "32bit版符号あり16進数を10進数に変換", nullptr, HexToDecd32);
                *conversion += new MenuEntry(Color::Cyan << "32bit版符号なし16進数を10進数に変換", nullptr, HexToDecu32);
                *conversion += new MenuEntry(Color::Cyan << "16bit版符号あり16進数を10進数に変換", nullptr, HexToDecd16);
                *conversion += new MenuEntry(Color::Cyan << "16bit版符号なし16進数を10進数に変換", nullptr, HexToDecu16);
                *conversion += new MenuEntry(Color::Cyan << "8bit版符号あり16進数を10進数に変換", nullptr, HexToDecd8);
                *conversion += new MenuEntry(Color::Cyan << "8bit版符号なし16進数を10進数に変換", nullptr, HexToDecu8);
                *conversion += new MenuEntry(Color::Cyan << "10進数を16進数に変換", nullptr, DecToHex);
            }
            *bonus += conversion;

            MenuFolder *calculator = new MenuFolder(Color::LimeGreen << "電卓");
            {
                *calculator += new MenuEntry(Color::LimeGreen << "16進数電卓", nullptr, HexadecimalCalculator, Color::Yellow << "16進数を計算することができます。");
                *calculator += new MenuEntry(Color::LimeGreen << "10進数電卓", nullptr, DecimalCalculator, Color::Yellow << "10進数を計算することができます。");
                *calculator += new MenuEntry(Color::LimeGreen << "浮動小数点数電卓", nullptr, FloatCalculator, Color::Yellow << "浮動小数点数を計算することができます。");
            }
            *bonus += calculator;

            MenuFolder *RGBChecker = new MenuFolder(Color::Orange << "RGBチェッカー");
            {
                *RGBChecker += new MenuEntry(Color::Red << "R値入力", nullptr, RedInput);
                *RGBChecker += new MenuEntry(Color::Green << "G値入力", nullptr, GreenInput);
                *RGBChecker += new MenuEntry(Color::Blue << "B値入力", nullptr, BlueInput);
                *RGBChecker += new MenuEntry(Color::Yellow << "色確認", nullptr, RGBOutput);
            }
            *bonus += RGBChecker;

            //	*bonus += EntryWithHotkey(new MenuEntry("アドレス監視", HexEditor,
            //		Color::Yellow << "アドレスと値の監視ができます。\nA+↑で上に移動できます。\nA+↓で下に移動できます。"),{
            //			Hotkey(Key::R | A, "アドレス変更"),
            //			Hotkey(Key::R | B, "値を入力")});

            *bonus += EntryWithHotkey(new MenuEntry(Color::Cyan << "アドレス監視", HexEditor2, Color::Yellow << "アドレスと値の監視ができます。\nA+↑で上に移動できます。\nA+↓で下に移動できます。"), {Hotkey(Key::R | A, "アドレス変更"), Hotkey(Key::R | B, "値を入力")});
            *bonus += new MenuEntry(Color::Magenta << "3DSの情報を確認", nullptr, Information, Color::Yellow << "3DSの情報を確認できます。");
        }
        menu += bonus;
    }

    void TeamAndConditions()
    {
        //オープニングメッセージ
        static bool file = false;
        std::string tid;
        std::string openingMessage = "オープニングメッセージ";
        Process::GetTitleID(tid);
        if (tid == "0004000000155400")
        {
            if (!file)
            {
                if (!File::Exists("opskip.bin"))
                {
                    MessageBox("オープニングメッセージ", "ぽんぽこ @ponpoko094\nの3gxを使用していただき\nありがとうございます。\n次に利用規約が表示されます\n同意をお願いします。")();
                    if (MessageBox("オープニングメッセージ", "利用規約\n①この3gxは無料で提供されます。\n②二次配布を禁止します。\n③この3gxを使用しデータが破損する等の\n損害に対して、ぽんぽこは一切の責任を負いません。\n④この3gxは日本版MHX\n  (タイトルID:0004000000155400)\n  でのみ使用できるものとします。\n利用規約に同意しますか？", DialogType::DialogYesNo)())
                    {
                        if (MessageBox("オープニングメッセージ", "利用規約に同意していただき\nありがとうございます。\n次回からオープニングメッセージを\nスキップしますか？", DialogType::DialogYesNo)())
                        {
                            File::Create("opskip.bin");
                            MessageBox("オープニングメッセージ", "opskip.binを作成しました。\n設定を変更するために\n再起動をお願いします。")();
                            abort();
                        }
                        else
                        {
                            MessageBox("オープニングメッセージ", "プラグインを楽しんでください。")();
                        }
                    }
                    else
                    {
                        MessageBox("オープニングメッセージ", "利用規約に同意する必要があります。")();
                        abort();
                    }
                }
                file = true;
            }
        }
        else
        {
            MessageBox("オープニングメッセージ", "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。")();
            abort();
        }
    }

    // タイトルやAbout等作成
    PluginMenu *menu = new PluginMenu(Color::Red << "MHX" << Color::Green << "3gx" << Color::Blue << "dev6", 0, 9, 4,
                                      Color::Red << "ソース記述の人\n"
                                                 << Color::Magenta << " ぽんぽこ\n"
                                                 << Color::Blue << "サーチした人\n"
                                                 << Color::Magenta << " ぽんぽこ\n"
                                                 << Color::Yellow << " 舞姫氏\n"
                                                 << Color::Yellow << " ymyn氏\n"
                                                 << Color::Yellow << " Fort42氏\n"
                                                 << Color::Green << "プラグイン作成において、ヒントを頂いた人\n"
                                                 << Color::Yellow << " Naoki氏\n"
                                                 << Color::Yellow << " クレラビ氏\n"
                                                 << Color::Yellow << " だいち村長氏\n"
                                                 << Color::Yellow << " けんじい氏\n"
                                                 << Color::Red << "参考にしたサイト\n"
                                                 << Color::Yellow << " mhgen.kiranico.com\n"
                                                 << Color::Yellow << " www.sejuku.net/blog/24934\n"
                                                 << Color::Red << "整合性チェックは行っていません。\n"
                                                 << Color::Red << "データのバックアップは取ってください。\n"
                                                 << Color::Red << "プラグインを楽しんでください。");

    //Plugin menu
    int main(void)
    {
        // Synchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        //HexEditorを無効化
        menu->SetHexEditorState(false);

        //Plugin Ready!を無効化
        menu->ShowWelcomeMessage(false);

        //Plugin Ready!の代わり
        OSD::Notify(Color(234, 145, 152) << "ponpoko094's 3gx!");

        // Init our menu entries & folders
        InitMenu(*menu);

        // Launch menu and mainloop
        menu->Run();
        delete menu;
        return (0);
    }
} // namespace CTRPluginFramework