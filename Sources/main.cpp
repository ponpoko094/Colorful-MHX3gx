#include "3ds.h"
#include "csvc.h"
#include "CTRPluginFramework.hpp"
#include "cheats.cpp"
#include "Helpers.hpp"
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

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
		settings.MainTextColor = Color(234, 145, 152);			 //テキストの色
		settings.WindowTitleColor = Color(234, 145, 152);		 //タイトルの色
		settings.MenuSelectedItemColor = Color(234, 145, 152);   //普通のメニューの色
		settings.MenuUnselectedItemColor = Color(234, 145, 152); //ActionReplayとかの色
		settings.BackgroundMainColor = Color::Black;			 //背景の色
		settings.BackgroundSecondaryColor = Color::Black;		 //背景の細線の色
		settings.BackgroundBorderColor = Color(234, 145, 152);   //背景の枠線の色
		//キーボードの色
		settings.Keyboard.KeyBackgroundPressed = Color::Black; //押された時の背景の色
		settings.Keyboard.KeyText = Color(234, 145, 152);	  //数字の色
		settings.Keyboard.KeyTextPressed = Color::White;	   //押された時の数字の色
		settings.Keyboard.Input = Color(234, 145, 152);		   //上に表示されてる数字の色
		//カスタムキーボードの色
		settings.CustomKeyboard.BackgroundSecondary = Color::Black;		 //歯車の背景細線の色
		settings.CustomKeyboard.BackgroundBorder = Color(234, 145, 152); //歯車の枠線の色
		settings.CustomKeyboard.KeyBackground = Color::Black;			 //歯車のメニューの色
		settings.CustomKeyboard.KeyBackgroundPressed = Color::Black;	 //歯車のメニューが押された時の色
		settings.CustomKeyboard.KeyText = Color(234, 145, 152);			 //歯車のキーの色
		settings.CustomKeyboard.KeyTextPressed = Color::White;			 //歯車のキーが押された時の色
		settings.CustomKeyboard.ScrollBarBackground = Color::Black;		 //スクロールバーの背景の色
		settings.CustomKeyboard.ScrollBarThumb = Color(234, 145, 152);   //スクロールバーの動く色
	}

	// This function is called when the process exits
	// Useful to save settings, undo patchs or clean up things
	void OnProcessExit(void)
	{
		ToggleTouchscreenForceOn();
	}

	//チート
	void InitMenu(PluginMenu &menu)
	{
		// Create your entries here, or elsewhere
		// You can create your entries whenever/wherever you feel like it

		//	menu += EntryWithHotkey(new MenuEntry(""<< Color::Red <<"クイック" ""<<Color::Magenta<<"メニュー", Quickmenu, "ホットキーを設定してね"),{Hotkey(Key::L, Color::Yellow<<"クイックメニュー")});
		//	menu += new MenuEntry(Color::Magenta << "ツンデレG氏へ Select式plg作成頑張ってください。", Color::Yellow << "訳:なんで3gx作らないの?\n作れないなら教えてあげようか?(*^ω^*)");
		MenuFolder *player = new MenuFolder(Color::Red << "プレイヤー");
		{

			MenuFolder *statusv2 = new MenuFolder(Color::Yellow << "ステータス変更改良版");
			{
				*statusv2 += new MenuEntry(Color::Yellow << "攻撃力変更改良版", attackv2, attackv2op, Color::Yellow << "攻撃力を変更できます。");
				*statusv2 += new MenuEntry(Color::Yellow << "防御力変更改良版", defencev2, defencev2op, Color::Yellow << "防御力を変更できます。");
				*statusv2 += new MenuEntry(Color::Yellow << "属性値変更改良版", zokuseiv2, zokuseiv2op, Color::Yellow << "属性値を変更できます。");
				*statusv2 += new MenuEntry(Color::Yellow << "耐性値変更改良版", taiseiv2, taiseiv2op, Color::Yellow << "耐性値を変更できます。");
			}
			*player += statusv2;

			MenuFolder *playerchange = new MenuFolder(Color::Orange << "プレイヤー情報変更");
			{
				MenuFolder *kariwazaf = new MenuFolder(Color::Yellow << "狩技変更");
				{
					*kariwazaf += new MenuEntry(Color::Yellow << "狩技1番目変更", nullptr, kariwaza1, Color::Yellow << "狩技の1番目を変更します。");
					*kariwazaf += new MenuEntry(Color::Yellow << "狩技2番目変更", nullptr, kariwaza2, Color::Yellow << "狩技の2番目を変更します。");
					*kariwazaf += new MenuEntry(Color::Yellow << "狩技3番目変更", nullptr, kariwaza3, Color::Yellow << "狩技の3番目を変更します。");
				}
				*playerchange += kariwazaf;

				MenuFolder *skin = new MenuFolder(Color::SkyBlue << "肌の色変更", Color::Yellow << "RGBの値は、\n"
																								"bit.ly/GetRGB\n"
																								"を見て、入力してください。");
				{
					*skin += new MenuEntry(Color::SkyBlue << "肌の色R値変更", nullptr, skinrchange, Color::Yellow << "肌の色の赤色を変更します。");
					*skin += new MenuEntry(Color::SkyBlue << "肌の色G値変更", nullptr, skingchange, Color::Yellow << "肌の色の緑色を変更します。");
					*skin += new MenuEntry(Color::SkyBlue << "肌の色B値変更", nullptr, skinbchange, Color::Yellow << "肌の色の青色を変更します。");
					*skin += new MenuEntry(Color::SkyBlue << "肌の色変更", nullptr, skinrgbchange, Color::Yellow << "肌の色を変更します。");
				}
				*playerchange += skin;

				MenuFolder *syokuji = new MenuFolder(Color::Magenta << "食事");
				{
					MenuFolder *syokujiflag = new MenuFolder(Color::ForestGreen << "フラグ");
					{
						*syokujiflag += new MenuEntry(Color::ForestGreen << "食事無限", Syokuji_Flag_Mugen, Color::Yellow << "食事が無限にできます。");
						*syokujiflag += new MenuEntry(Color::ForestGreen << "高級お食事券効果付与", Syokuji_Flag_Osyokujiken, Color::Yellow << "高級お食事券の効果が付与されます。");
						*syokujiflag += new MenuEntry(Color::ForestGreen << "よろず焼きの依頼無限", Syokuji_Flag_Nikuirai, Color::Yellow << "よろず焼きの依頼が無限にできます。");
					}
					*syokuji += syokujiflag;

					MenuFolder *syokujistatus = new MenuFolder(Color::Green << "ステータス");
					{
						MenuFolder *syokujistatustaisei = new MenuFolder(Color::Lime << "耐性");
						{
							*syokujistatustaisei += new MenuEntry(Color::Lime << "火耐性UP", Syokuji_Status_Taisei_Hi, Color::Yellow << "火耐性が上昇します。");
							*syokujistatustaisei += new MenuEntry(Color::Lime << "水耐性UP", Syokuji_Status_Taisei_Mizu, Color::Yellow << "水耐性が上昇します。");
							*syokujistatustaisei += new MenuEntry(Color::Lime << "雷耐性UP", Syokuji_Status_Taisei_Kaminari, Color::Yellow << "雷耐性が上昇します。");
							*syokujistatustaisei += new MenuEntry(Color::Lime << "氷耐性UP", Syokuji_Status_Taisei_Koori, Color::Yellow << "氷耐性が上昇します。");
							*syokujistatustaisei += new MenuEntry(Color::Lime << "龍耐性UP", Syokuji_Status_Taisei_Ryu, Color::Yellow << "龍耐性が上昇します。");
						}
						*syokujistatus += syokujistatustaisei;

						*syokujistatus += new MenuEntry(Color::Green << "体力UP", Syokuji_Status_Hp, Color::Yellow << "体力が上昇します。");
						*syokujistatus += new MenuEntry(Color::Green << "スタミナUP", Syokuji_Status_Stamina, Color::Yellow << "スタミナが上昇します。");
						*syokujistatus += new MenuEntry(Color::Green << "攻撃力UP", Syokuji_Status_Attack, Color::Yellow << "攻撃力が上昇します。");
						*syokujistatus += new MenuEntry(Color::Green << "防御力UP", Syokuji_Status_Defence, Color::Yellow << "防御力が上昇します。");
					}
					*syokuji += syokujistatus;

					MenuFolder *syokujiskill = new MenuFolder(Color::LimeGreen << "スキル");
					{
						*syokujiskill += new MenuEntry(Color::LimeGreen << "スキル1", nullptr, Syokuji_Skill_1, Color::Yellow << "食事スキルの1番目を変更します。");
						*syokujiskill += new MenuEntry(Color::LimeGreen << "スキル2", nullptr, Syokuji_Skill_2, Color::Yellow << "食事スキルの2番目を変更します。");
						*syokujiskill += new MenuEntry(Color::LimeGreen << "スキル3", nullptr, Syokuji_Skill_3, Color::Yellow << "食事スキルの3番目を変更します。");
					}
					*syokuji += syokujiskill;
				}
				*playerchange += syokuji;

				*playerchange += new MenuEntry(Color::Orange << "声変更", nullptr, voicechange, Color::Yellow << "声を変更します。");
				*playerchange += new MenuEntry(Color::Orange << "目の色変更", nullptr, eyecolorchange, Color::Yellow << "目の色を変更します。");
				*playerchange += new MenuEntry(Color::Orange << "インナー変更", nullptr, innerchange, Color::Yellow << "インナーを変更します。");
				*playerchange += new MenuEntry(Color::Orange << "性別変更", nullptr, seibetuchange, Color::Yellow << "性別を変更します。");
				*playerchange += new MenuEntry(Color::Orange << "狩猟スタイル変更", nullptr, stylechange, Color::Yellow << "狩猟スタイルを変更します。");
				*playerchange += new MenuEntry(Color::Orange << "髪型変更", nullptr, hearchange, Color::Yellow << "髪型を変更します。");
				*playerchange += new MenuEntry(Color::Orange << "顔変更", nullptr, kaochange, Color::Yellow << "顔を変更します。");
				*playerchange += new MenuEntry(Color::Orange << "メイク変更", nullptr, makechange, Color::Yellow << "メイクを変更します。");
			}
			*player += playerchange;

			*player += new MenuEntry(Color::Red << "攻撃力倍率変更", attackchange, attackop, Color::Yellow << "Y+UPでON、Y+DOWNでOFF\n攻撃力の倍率を変更します。\nCode by ymyn");
			*player += new MenuEntry(Color::Red << "防御力倍率変更", defencechange, defenceop, Color::Yellow << "X+UPでON、X+DOWNでOFF\n防御力の倍率を変更します。\nCode by ymyn");
			*player += new MenuEntry(Color::Cyan << "速度変更", speedchange, speedop, Color::Yellow << "SELECT+LでON、SELECT+RでOFF\n速度を変更します。\nCode by ymyn");
			*player += new MenuEntry(Color::Red << "プレイヤー座標移動", zahyo, Color::Yellow << "A+十字キーで移動できます。");
			*player += new MenuEntry(Color::Red << "ムーンジャンプ", moonjump, Color::Yellow << "R+Bでジャンプできます。\n"
																								"上がり続けるにはリピートムーブもオンにして、R+B+Yを押してください。");
			*player += new MenuEntry(Color::Red << "保存式テレポート", Teleport, Color::Yellow << "R + → 現在位置を読み込む。\n"
																								"R + ← 現在位置に書き込む");
			*player += new MenuEntry(Color::Red << "他プレイヤーストーカー", Color::Yellow << "舞姫氏の要望で入れていません。");
			*player += new MenuEntry(Color::Red << "他プレイヤーストーカー", stalker, Color::Yellow << "R+十字キーで追跡設定ができます。\n"
																									"R+↑ P1を追跡有効\n"
																									"R+→ P2を追跡有効\n"
																									"R+↓ P3を追跡有効\n"
																									"R+←で追跡無効にできます。");
			*player += new MenuEntry(Color::Red << "リピートムーブ", Repeatmove, Color::Yellow << "B+Yで動きを繰り返します。");
			*player += new MenuEntry(Color::Red << "狩技開放", kariwazakaihou, Color::Yellow << "狩技を全て開放します。\n"
																								"Code by ymyn");
			*player += new MenuEntry(Color::Red << "腹減り無効", haraherimukou, Color::Yellow << "時間経過でスタミナが減らなくなります。");
			*player += new MenuEntry(Color::Red << "プレイヤーサイズ変更", huntersize, huntersizeop, Color::Yellow << "ハンターのサイズを変更できます。");
			*player += new MenuEntry(Color::Red << "HP無限", nullptr, infhp, Color::Yellow << "HPを無限にします。\n"
																							"Code by ymyn");
			*player += new MenuEntry(Color::Red << "無敵", nullptr, invicible, Color::Yellow << "無敵になります。\n"
																								"Code by ymyn");
			*player += new MenuEntry(Color::Red << "スーパーアーマー", nullptr, superarmor, Color::Yellow << "スーパーアーマーになります。\n"
																											"Code by ymyn");
			*player += new MenuEntry(Color::Red << "スタミナ無限", nullptr, infstamina, Color::Yellow << "スタミナを無限にします。\n"
																										"Code by ymyn");
			*player += new MenuEntry(Color::Red << "狩技ゲージ無限", nullptr, infkariwaza, Color::Yellow << "狩技ゲージが無限になります。\n"
																											"Code by ymyn");
			*player += new MenuEntry(Color::Red << "全スタイルで狩技3つ装着可能", nullptr, always3kariwaza, Color::Yellow << "全スタイルで狩技を3つ装着可能になります。\n"
																															"Code by ymyn");
			*player += new MenuEntry(Color::Red << "常時地図表示", nullptr, alwaysmap, Color::Yellow << "常に地図を表示します。\n"
																										"Code by ymyn");
			*player += new MenuEntry(Color::Red << "常にモンスターペイント", nullptr, alwayspeint, Color::Yellow << "常にマップにモンスターが表示されます。\n"
																													"Code by ymyn");
			*player += new MenuEntry(Color::Red << "スピードハック", nullptr, speedhack, Color::Yellow << "速度の変更ができます。");
			*player += new MenuEntry(Color::Red << "クエスト中スピードハック", nullptr, speedquebukiari, Color::Yellow << "クエスト中での速度を変更できます。");
			*player += new MenuEntry(Color::Red << "走った時にムーンウォーク", nullptr, hasirustop, Color::Yellow << "走った時にムーンウォークをします。");
			*player += new MenuEntry(Color::Red << "プレイヤー名前変更", nullptr, huntername, Color::Yellow << "定型文では1ページ目の一番左下にある定型文を名前にコピーします。\n"
																											"キーボードでは、メニュー内で直接変更することができます。\n"
																											"変換候補変換の改行やタブが使えます。");
		}
		menu += player;

		MenuFolder *item = new MenuFolder(Color::Orange << "アイテム");
		{
			MenuFolder *soubi = new MenuFolder(Color::Magenta << "装備");
			{
				MenuFolder *goseki = new MenuFolder(Color::Red << "護石編集", Color::Yellow << "編集したい護石を、装備BOX14ページ目の一番右下に移動させてください。\n"
																							"14ページ目がない場合は、アイテムフォルダにある「ボックス1400個に拡張」をオンにしてください。");
				{
					*goseki += new MenuEntry(Color::Red << "新護石作成", nullptr, gosekisakusei, Color::Yellow << "新たに護石を作成できます。");
					*goseki += new MenuEntry(Color::Red << "護石種類変更", nullptr, gosekirare, Color::Yellow << "護石の種類を変更します。");
					*goseki += new MenuEntry(Color::Red << "第一スキル変更", nullptr, gosekiskill1, Color::Yellow << "第一スキルを変更します。");
					*goseki += new MenuEntry(Color::Red << "第二スキル変更", nullptr, gosekiskill2, Color::Yellow << "第二スキルを変更します。");
					*goseki += new MenuEntry(Color::Red << "第一スキルポイント変更", nullptr, gosekiskill1p, Color::Yellow << "第一スキルポイントを変更します。");
					*goseki += new MenuEntry(Color::Red << "第二スキルポイント変更", nullptr, gosekiskill2p, Color::Yellow << "第二スキルポイントを変更します。");
					*goseki += new MenuEntry(Color::Red << "スロット数変更", nullptr, gosekislot, Color::Yellow << "スロット数を変更します。");
				}
				*soubi += goseki;

				MenuFolder *musi = new MenuFolder(Color::Cyan << "猟虫編集", Color::Yellow << "編集したい猟虫がついている操虫棍を、装備BOX14ページ目の一番下の右から4番目に移動させてください。\n"
																							"14ページ目がない場合は、アイテムフォルダにある「ボックス1400個に拡張」をオンにしてください。");
				{
					*musi += new MenuEntry(Color::Cyan << "猟虫種類変更", nullptr, musisyurui, Color::Yellow << "猟虫の種類を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫レベル変更", nullptr, musilevel, Color::Yellow << "猟虫のレベルを変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫パワー補正変更", nullptr, musipower, Color::Yellow << "猟虫のパワー補正を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫ウェイト補正変更", nullptr, musiweight, Color::Yellow << "猟虫のウェイト補正を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫スタミナ補正変更", nullptr, musistamina, Color::Yellow << "猟虫のスタミナ補正を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫火属性変更", nullptr, musihi, Color::Yellow << "猟虫の火属性を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫水属性変更", nullptr, musimizu, Color::Yellow << "猟虫の水属性を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫雷属性変更", nullptr, musikaminari, Color::Yellow << "猟虫の雷属性を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫氷属性変更", nullptr, musikori, Color::Yellow << "猟虫の氷属性を変更します。");
					*musi += new MenuEntry(Color::Cyan << "猟虫龍属性変更", nullptr, musiryu, Color::Yellow << "猟虫の龍属性を変更します。");
				}
				*soubi += musi;

				*soubi += new MenuEntry(Color::Magenta << "他プレイヤーの装備コピー", nullptr, soubicopy, Color::Yellow << "コピーしたいプレイヤーが猫の場合、コピーしないでください。");
			}
			*item += soubi;

			*item += new MenuEntry(Color::Orange << "爆弾を無限に置ける", infbakudan, Color::Yellow << "見た目だけです。");
			*item += new MenuEntry(Color::Orange << "たんほれアイテムセット", tanhoreitem, Color::Yellow << "ポーチの\n"
																											"1枠目を 燃石炭\n"
																											"2枠目を ネコタクチケット\n"
																											"3枠目を モドリ玉\nにします。");
			*item += new MenuEntry(Color::Orange << "所持金最大", nullptr, money, Color::Yellow << "所持金を変更できます。");
			*item += new MenuEntry(Color::Orange << "龍歴員ポイント最大", nullptr, point, Color::Yellow << "龍歴員ポイントを変更できます。");
			*item += new MenuEntry(Color::Orange << "アイテム&弾丸無限", nullptr, infitemammo, Color::Yellow << "アイテムと弾丸を無限にします。\n"
																												"しゃがみの弾は無限になりません。\n"
																												"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "素材無しで調合可能", nullptr, nosozaityougou, Color::Yellow << "素材無しで調合を可能にします。\n"
																													"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "運搬物を持たずにポーチに入れる", nullptr, tamagoporch, Color::Yellow << "運搬物がポーチに入ります。\n"
																															"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "採取無限", nullptr, infsaisyu, Color::Yellow << "採集ポイントで無限に採取ができます。\n"
																									"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "装備を素材無しで作れる", nullptr, nosozaisoubi, Color::Yellow << "素材なしで装備生産をすることができます。\n"
																													"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "装備欄全て開放", nullptr, soubikaihou, Color::Yellow << "装備生産リストを全て開放します。\n"
																											"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "全てのアイテム販売", nullptr, allitemsold, Color::Yellow << "全てのアイテムがギルドストアや雑貨屋に売り出されます。\n"
																												"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "ボックス1400個に拡張", nullptr, itembox1400, Color::Yellow << "ボックスのページを1400個に拡張します。\n"
																												"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "持てるアイテム99個", nullptr, haveitem99, Color::Yellow << "持てるアイテムの最大数を99個にします。\n"
																												"Code by ymyn");
			*item += new MenuEntry(Color::Orange << "アイテムボックス編集", nullptr, itemboxedit, Color::Yellow << "アイテムボックスの編集をします。");
			*item += new MenuEntry(Color::Orange << "アイテムマイセットをポーチにコピー", nullptr, mysetitemcopy, Color::Yellow << "アイテムマイセットに登録されているアイテムを、アイテムポーチにコピーします。");
			*item += new MenuEntry(Color::Orange << "納品アイテムをポーチにコピー", nullptr, nouhinitemcopy, Color::Yellow << "納品アイテムを、アイテムポーチの1番目と2番目にコピーします。\n空きを作ってください。");
			*item += new MenuEntry(Color::Orange << "ポーチを納品アイテムにコピー", nullptr, nouhinitemres, Color::Yellow << "アイテムポーチの1番目をメインの納品に、2番目をサブの納品にコピーします。\n空きを作ってください。");
			*item += new MenuEntry(Color::Orange << "ポーチのアイテム全消去", nullptr, porchclear, Color::Yellow << "ポーチのアイテムを全消去します。\n"
																													"消せないアイテムや、ボックスにしまえないアイテムがあるときに実行してください。");
			*item += new MenuEntry(Color::Orange << "特殊許可チケットの数変更", nullptr, tokusyuticket, Color::Yellow << "特殊許可チケットの枚数を変更します。");
		}
		menu += item;

		MenuFolder *weapon = new MenuFolder(Color::Yellow << "武器");
		{
			MenuFolder *bukibetu = new MenuFolder(Color::Red << "武器別チート");
			{
				MenuFolder *gunlance = new MenuFolder(Color::Orange << "ガンランスチート");
				{
					*gunlance += new MenuEntry(Color::Orange << "ヒートゲージ固定", heatgage, heatgagechange, Color::Yellow << "ヒートゲージを固定します。");
					*gunlance += new MenuEntry(Color::Orange << "ガンランスの弾無限", gunlanceammo, Color::Yellow << "ガンランスの弾を無限にします。");
					*gunlance += new MenuEntry(Color::Orange << "オーバーヒート無効", nooverheat, Color::Yellow << "オーバーヒートを無効にします。");
				}
				*bukibetu += gunlance;

				MenuFolder *soutyukon = new MenuFolder(Color::Green << "操虫棍チート");
				{
					*soutyukon += new MenuEntry(Color::Green << "常時トリプルアップ", tripleup, Color::Yellow << "常時トリプルアップになります。");
					*soutyukon += new MenuEntry(Color::Green << "虫のスタミナ無限", infmusistamina, Color::Yellow << "虫のスタミナが無限になります。");
				}
				*bukibetu += soutyukon;

				MenuFolder *bowgun = new MenuFolder(Color::Magenta << "ボウガンチート");
				{
					*bowgun += new MenuEntry(Color::Magenta << "ボウガンの弾無限", tamakazu, Color::Yellow << "ボウガンの弾が無限になります。");
					*bowgun += new MenuEntry(Color::Magenta << "しゃがみの弾無限", syagami, Color::Yellow << "しゃがみ撃ちの弾が無限になります。");
				}
				*bukibetu += bowgun;

				*bukibetu += new MenuEntry(Color::Red << "溜め段階固定", tamekotei, tamedankai, Color::Yellow << "大剣などの溜め段階を固定します。");
				*bukibetu += new MenuEntry(Color::Red << "武器ゲージ固定", bukigage, Color::Yellow << "太刀や双剣のゲージを固定します。");
				*bukibetu += new MenuEntry(Color::Red << "チャージアックスビン固定", tyaakubin, Color::Yellow << "チャージアックスのビン数を固定します。");
				*bukibetu += new MenuEntry(Color::Red << "狩猟笛の全効果付与", huegodmode, Color::Yellow << "反映されない効果があります。");
			}
			*weapon += bukibetu;

			*weapon += new MenuEntry(Color::Yellow << "属性値変更", nullptr, zokusei, Color::Yellow << "属性値を変更できます。");
			*weapon += new MenuEntry(Color::Yellow << "モーション無し", nullptr, nova, Color::Yellow << "モーションを無くします。\n"
																										"Code by 舞姫");
			*weapon += new MenuEntry(Color::Yellow << "会心率100%", nullptr, critical100, Color::Yellow << "会心率が100%になります。\n"
																										"Code by Fort42");
			*weapon += new MenuEntry(Color::Yellow << "ボウガン自動装填", nullptr, autoreload, Color::Yellow << "ボウガンの弾が自動で装填されます。\n"
																												"Code by ymyn");
			*weapon += new MenuEntry(Color::Yellow << "斬れ味無限", nullptr, infsharpness, Color::Yellow << "斬れ味が無限になります。\n"
																											"Code by ymyn");
			*weapon += new MenuEntry(Color::Yellow << "斬れ味+2", nullptr, sharpness2, Color::Yellow << "斬れ味レベル+2の効果を付与します。\n"
																										"Code by Fort42");
			*weapon += new MenuEntry(Color::Yellow << "高速溜め短縮", nullptr, chargespeedup, Color::Yellow << "大剣等の溜めが短縮されます。\n"
																											"Code by Fort42");
			*weapon += new MenuEntry(Color::Yellow << "チャージゲージ最大", nullptr, chargemax, Color::Yellow << "チャージゲージが最大になります。\n"
																												"Code by Fort42");
		}
		menu += weapon;

		MenuFolder *monster = new MenuFolder(Color::Green << "モンスター", Color::Yellow << "オンラインだとラグがあったり、使えない場合があります。");
		{
			MenuFolder *monhyouji = new MenuFolder(Color::LimeGreen << "モンスター情報画面表示");
			{
				*monhyouji += new MenuEntry(Color::LimeGreen << "1番目のモンスターのHP表示", monhp1, Color::Yellow << "1番目のモンスターのHPを画面上に表示します。");
				*monhyouji += new MenuEntry(Color::LimeGreen << "2番目のモンスターのHP表示", monhp2, Color::Yellow << "2番目のモンスターのHPを画面上に表示します。");
				*monhyouji += new MenuEntry(Color::LimeGreen << "1番目のモンスターのサイズ倍率表示", mon1size, Color::Yellow << "1番目のモンスターのサイズ倍率を画面上に表示します。\n"
																																"1.2付近がキンズサイズ、0.9付近がスモールサイズの目安です。");
				*monhyouji += new MenuEntry(Color::LimeGreen << "2番目のモンスターのサイズ倍率表示", mon2size, Color::Yellow << "2番目のモンスターのサイズ倍率を画面上に表示します。\n"
																																"1.2付近がキングサイズ、0.9付近がスモールサイズの目安です。");
			}
			*monster += monhyouji;

			*monster += new MenuEntry(Color::Green << "乗り成功", norigage, Color::Yellow << "ハンターの乗りゲージを最大にします。\n"
																							"モンスターの乗りゲージが増えないようにします。");
			*monster += new MenuEntry(Color::Green << "モンスター座標移動", monzahyo, Color::Yellow << "1番目のモンスターはX+十字キーで操作できます。\n"
																									"2番目のモンスターはX+スライドパッドで操作できます。\n"
																									"操作したいモンスターと同じエリアにいてください。");
			*monster += new MenuEntry(Color::Green << "モンスターストーカー", monstalker, Color::Yellow << "1番目のモンスターはX+R+↑で追跡有効にできます。\n"
																										"2番目のモンスターはX+L+↑で追跡有効にできます。\n"
																										"X+R+↓で追跡停止できます。\n"
																										"追跡したいモンスターと同じエリアにいてください。");
			*monster += new MenuEntry(Color::Green << "モンスターリピートムーブ", monrepeat, monrepeatop, Color::Yellow << "リピートムーブの挙動の変更と、操作のオンオフができます。\n"
																														"1番目のモンスターはX+R+→で操作できます。\n"
																														"2番目のモンスターはX+L+→で操作できます。\n"
																														"操作したいモンスターと同じエリアにいてください。");
			*monster += new MenuEntry(Color::Green << "1番目と2番目のモンスターの動き停止", mon12stop, Color::Yellow << "動き停止は、速度変更より優先されます。");
			*monster += new MenuEntry(Color::Green << "1番目のモンスターのサイズ変更", mon1sizechange, mon1sizechangeop, Color::Yellow << "1番目のモンスターのサイズの変更ができます。");
			*monster += new MenuEntry(Color::Green << "2番目のモンスターのサイズ変更", mon2sizechange, mon2sizechangeop, Color::Yellow << "2番目のモンスターのサイズの変更ができます。");
			*monster += new MenuEntry(Color::Green << "1番目のモンスターの速度倍率変更", mon1speed, mon1speedop, Color::Yellow << "1番目のモンスターの速度の変更ができます。");
			*monster += new MenuEntry(Color::Green << "2番目のモンスターの速度倍率変更", mon2speed, mon2speedop, Color::Yellow << "2番目のモンスターの速度の変更ができます。");
			*monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター常時毒", mondoku, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
			*monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター常時麻痺", monmahi, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
			*monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター常時睡眠", monsuimin, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
			*monster += new MenuEntry(Color::Green << "1番目と2番目のモンスター透明化", nullptr, montoumei, Color::Yellow << "1番目と2番目のモンスターのサイズの変更ができます。");
			*monster += new MenuEntry(Color::Green << "瞬殺", nullptr, onekill, Color::Yellow << "モンスターを瞬殺できます。\n"
																								"Code by 舞姫");
		}
		menu += monster;

		MenuFolder *otomo = new MenuFolder(Color::Blue << "ねこ");
		{
			MenuFolder *otomoattackch = new MenuFolder(Color::Magenta << "ねこの攻撃力変更", Color::Yellow << "Code by Fort42");
			{
				*otomoattackch += new MenuEntry(Color::Magenta << "ねこの攻撃力変更", otomoattack, Color::Yellow << "Y+UPでON、Y+DOWNでOFF");
				*otomoattackch += new MenuEntry(Color::Magenta << "ねこの攻撃力変更設定", nullptr, otomoattackop, Color::Yellow << "ねこの攻撃力変更の倍率を変更します。");
			}
			*otomo += otomoattackch;

			MenuFolder *otomodefencech = new MenuFolder(Color::Cyan << "ねこの防御力変更", Color::Yellow << "Code by Fort42");
			{
				*otomodefencech += new MenuEntry(Color::Cyan << "ねこの防御力変更", otomodefence, Color::Yellow << "X+UPでON、X+DOWNでOFF");
				*otomodefencech += new MenuEntry(Color::Cyan << "ねこの防御力変更設定", nullptr, otomodefenceop, Color::Yellow << "ねこの防御力変更の倍率を変更します。");
			}
			*otomo += otomodefencech;

			MenuFolder *otomoedit = new MenuFolder(Color::LimeGreen << "ねこ編集");
			{

				*otomoedit += new MenuEntry(Color::LimeGreen << "ねこ選択", nullptr, otomosentaku, Color::Yellow << "編集するねこを選択します。");

				MenuFolder *otomosoubisupport = new MenuFolder(Color::Magenta << "装備サポート行動");
				{
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動1番目変更", nullptr, otomosoubisup1, Color::Yellow << "ねこの装備サポート行動の1番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動2番目変更", nullptr, otomosoubisup2, Color::Yellow << "ねこの装備サポート行動の2番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動3番目変更", nullptr, otomosoubisup3, Color::Yellow << "ねこの装備サポート行動の3番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動4番目変更", nullptr, otomosoubisup4, Color::Yellow << "ねこの装備サポート行動の4番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動5番目変更", nullptr, otomosoubisup5, Color::Yellow << "ねこの装備サポート行動の5番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動6番目変更", nullptr, otomosoubisup6, Color::Yellow << "ねこの装備サポート行動の6番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動7番目変更", nullptr, otomosoubisup7, Color::Yellow << "ねこの装備サポート行動の7番目を変更します。");
					*otomosoubisupport += new MenuEntry(Color::Magenta << "装備サポート行動8番目変更", nullptr, otomosoubisup8, Color::Yellow << "ねこの装備サポート行動の8番目を変更します。");
				}
				*otomoedit += otomosoubisupport;

				MenuFolder *otomosoubiskill = new MenuFolder(Color::Cyan << "装備オトモスキル");
				{
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル1番目変更", nullptr, otomosoubiski1, Color::Yellow << "ねこの装備オトモスキルの1番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル2番目変更", nullptr, otomosoubiski2, Color::Yellow << "ねこの装備オトモスキルの2番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル3番目変更", nullptr, otomosoubiski3, Color::Yellow << "ねこの装備オトモスキルの3番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル4番目変更", nullptr, otomosoubiski4, Color::Yellow << "ねこの装備オトモスキルの4番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル5番目変更", nullptr, otomosoubiski5, Color::Yellow << "ねこの装備オトモスキルの5番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル6番目変更", nullptr, otomosoubiski6, Color::Yellow << "ねこの装備オトモスキルの6番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル7番目変更", nullptr, otomosoubiski7, Color::Yellow << "ねこの装備オトモスキルの7番目を変更します。");
					*otomosoubiskill += new MenuEntry(Color::Cyan << "装備オトモスキル8番目変更", nullptr, otomosoubiski8, Color::Yellow << "ねこの装備オトモスキルの8番目を変更します。");
				}
				*otomoedit += otomosoubiskill;

				MenuFolder *otomosyutokusupport = new MenuFolder(Color::Orange << "習得サポート行動");
				{
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動1番目変更", nullptr, otomosyutokusup1, Color::Yellow << "ねこの習得サポート行動の1番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動2番目変更", nullptr, otomosyutokusup2, Color::Yellow << "ねこの習得サポート行動の2番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動3番目変更", nullptr, otomosyutokusup3, Color::Yellow << "ねこの習得サポート行動の3番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動4番目変更", nullptr, otomosyutokusup4, Color::Yellow << "ねこの習得サポート行動の4番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動5番目変更", nullptr, otomosyutokusup5, Color::Yellow << "ねこの習得サポート行動の5番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動6番目変更", nullptr, otomosyutokusup6, Color::Yellow << "ねこの習得サポート行動の6番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動7番目変更", nullptr, otomosyutokusup7, Color::Yellow << "ねこの習得サポート行動の7番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動8番目変更", nullptr, otomosyutokusup8, Color::Yellow << "ねこの習得サポート行動の8番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動9番目変更", nullptr, otomosyutokusup9, Color::Yellow << "ねこの習得サポート行動の9番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動10番目変更", nullptr, otomosyutokusup10, Color::Yellow << "ねこの習得サポート行動の10番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動11番目変更", nullptr, otomosyutokusup11, Color::Yellow << "ねこの習得サポート行動の11番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動12番目変更", nullptr, otomosyutokusup12, Color::Yellow << "ねこの習得サポート行動の12番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動13番目変更", nullptr, otomosyutokusup13, Color::Yellow << "ねこの習得サポート行動の13番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動14番目変更", nullptr, otomosyutokusup14, Color::Yellow << "ねこの習得サポート行動の14番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動15番目変更", nullptr, otomosyutokusup15, Color::Yellow << "ねこの習得サポート行動の15番目を変更します。");
					*otomosyutokusupport += new MenuEntry(Color::Orange << "習得サポート行動16番目変更", nullptr, otomosyutokusup16, Color::Yellow << "ねこの習得サポート行動の16番目を変更します。");
				}
				*otomoedit += otomosyutokusupport;

				MenuFolder *otomosyutokuskill = new MenuFolder(Color::Green << "習得オトモスキル");
				{
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル1番目変更", nullptr, otomosyutokuski1, Color::Yellow << "ねこの習得オトモスキルの1番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル2番目変更", nullptr, otomosyutokuski2, Color::Yellow << "ねこの習得オトモスキルの2番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル3番目変更", nullptr, otomosyutokuski3, Color::Yellow << "ねこの習得オトモスキルの3番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル4番目変更", nullptr, otomosyutokuski4, Color::Yellow << "ねこの習得オトモスキルの4番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル5番目変更", nullptr, otomosyutokuski5, Color::Yellow << "ねこの習得オトモスキルの5番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル6番目変更", nullptr, otomosyutokuski6, Color::Yellow << "ねこの習得オトモスキルの6番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル7番目変更", nullptr, otomosyutokuski7, Color::Yellow << "ねこの習得オトモスキルの7番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル8番目変更", nullptr, otomosyutokuski8, Color::Yellow << "ねこの習得オトモスキルの8番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル9番目変更", nullptr, otomosyutokuski9, Color::Yellow << "ねこの習得オトモスキルの9番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル10番目変更", nullptr, otomosyutokuski10, Color::Yellow << "ねこの習得オトモスキルの10番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル11番目変更", nullptr, otomosyutokuski11, Color::Yellow << "ねこの習得オトモスキルの11番目を変更します。");
					*otomosyutokuskill += new MenuEntry(Color::Green << "習得オトモスキル12番目変更", nullptr, otomosyutokuski12, Color::Yellow << "ねこの習得オトモスキルの12番目を変更します。");
				}
				*otomoedit += otomosyutokuskill;

				MenuFolder *otomomitame = new MenuFolder(Color::ForestGreen << "見た目");
				{
					MenuFolder *otomomitamergb = new MenuFolder(Color::Green << "見た目の色変更");
					{
						MenuFolder *otomokeiro = new MenuFolder(Color::Magenta << "毛色");
						{
							*otomokeiro += new MenuEntry(Color::Magenta << "R値変更", nullptr, otomokeiror, Color::Yellow << "ねこの毛色の赤色を変更します。");
							*otomokeiro += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, otomokeirog, Color::Yellow << "ねこの毛色の緑色を変更します。");
							*otomokeiro += new MenuEntry(Color::Cyan << "B値変更", nullptr, otomokeirob, Color::Yellow << "ねこの毛色の青色を変更します。");
						}
						*otomomitamergb += otomokeiro;

						MenuFolder *otomomigimeiro = new MenuFolder(Color::Cyan << "右目の色");
						{
							*otomomigimeiro += new MenuEntry(Color::Magenta << "R値変更", nullptr, otomomigimeiror, Color::Yellow << "ねこの右目の赤色を変更します。");
							*otomomigimeiro += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, otomomigimeirog, Color::Yellow << "ねこの右目の緑色を変更します。");
							*otomomigimeiro += new MenuEntry(Color::Cyan << "B値変更", nullptr, otomomigimeirob, Color::Yellow << "ねこの右目の青色を変更します。");
						}
						*otomomitamergb += otomomigimeiro;

						MenuFolder *otomohidarimeiro = new MenuFolder(Color::LimeGreen << "左目の色");
						{
							*otomohidarimeiro += new MenuEntry(Color::Magenta << "R値変更", nullptr, otomohidarimeiror, Color::Yellow << "ねこの左目の赤色を変更します。");
							*otomohidarimeiro += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, otomohidarimeirog, Color::Yellow << "ねこの左目の緑色を変更します。");
							*otomohidarimeiro += new MenuEntry(Color::Cyan << "B値変更", nullptr, otomohidarimeirob, Color::Yellow << "ねこの左目の青色を変更します。");
						}
						*otomomitamergb += otomohidarimeiro;

						MenuFolder *otomoinneriro = new MenuFolder(Color::Yellow << "インナーの色");
						{
							*otomoinneriro += new MenuEntry(Color::Magenta << "R値変更", nullptr, otomoinneriror, Color::Yellow << "ねこのインナーの色の赤色を変更します。");
							*otomoinneriro += new MenuEntry(Color::LimeGreen << "G値変更", nullptr, otomoinnerirog, Color::Yellow << "ねこのインナーの色の緑色を変更します。");
							*otomoinneriro += new MenuEntry(Color::Cyan << "B値変更", nullptr, otomoinnerirob, Color::Yellow << "ねこのインナーの色の青色を変更します。");
						}
						*otomomitamergb += otomoinneriro;
					}
					*otomomitame += otomomitamergb;

					*otomomitame += new MenuEntry(Color::ForestGreen << "声変更", nullptr, otomovoice, Color::Yellow << "ねこの声を変更します。");
					*otomomitame += new MenuEntry(Color::ForestGreen << "目変更", nullptr, otomoeye, Color::Yellow << "ねこの目を変更します。");
					*otomomitame += new MenuEntry(Color::ForestGreen << "インナー変更", nullptr, otomoinner, Color::Yellow << "ねこのインナーを変更します。");
					*otomomitame += new MenuEntry(Color::ForestGreen << "毛並み変更", nullptr, otomokenami, Color::Yellow << "ねこの毛並みを変更します。");
					*otomomitame += new MenuEntry(Color::ForestGreen << "耳変更", nullptr, otomomimi, Color::Yellow << "ねこの耳を変更します。");
					*otomomitame += new MenuEntry(Color::ForestGreen << "尻尾変更", nullptr, otomosippo, Color::Yellow << "ねこの尻尾を変更します。");
				}
				*otomoedit += otomomitame;

				*otomoedit += new MenuEntry(Color::LimeGreen << "経験値変更", nullptr, otomoexp, Color::Yellow << "ねこの経験値を変更します。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "レベル変更", nullptr, otomolv, Color::Yellow << "ねこのレベルを変更します。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "サポート傾向変更", nullptr, otomosupport, Color::Yellow << "ねこのサポート傾向を変更します。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "親密度変更", nullptr, otomosinmitudo, Color::Yellow << "ねこの親密度を変更します。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "ターゲット変更", nullptr, otomotarget, Color::Yellow << "ねこのターゲットを変更します。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "オトモコメント編集可能変更", nullptr, otomokome, Color::Yellow << "ねこのオトモコメントを編集可能にするか選べます。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "特別配信表示変更", nullptr, otomotokubetu, Color::Yellow << "ねこの特別配信の表示を変更します。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "名前変更", nullptr, otomonamech, Color::Yellow << "ねこの名前を変更します。\n"
																												"定型文では1ページ目の一番左下にある定型文をねこの名前にコピーします。\n"
																												"キーボードでは、メニュー内で直接変更することができます。\n"
																												"変換候補変換の改行やタブが使えます。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "コメント変更", nullptr, otomocomech, Color::Yellow << "ねこのコメントを変更します。\n"
																													"定型文では1ページ目の一番左下にある定型文をねこのコメントにコピーします。\n"
																													"キーボードでは、メニュー内で直接変更することができます。\n"
																													"変換候補変換の改行やタブが使えます。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "名付け親変更", nullptr, otomonaduch, Color::Yellow << "ねこの名付け親を変更します。\n"
																													"定型文では1ページ目の一番左下にある定型文をねこの名付け親にコピーします。\n"
																													"キーボードでは、メニュー内で直接変更することができます。\n"
																													"変換候補変換の改行やタブが使えます。");
				*otomoedit += new MenuEntry(Color::LimeGreen << "先代旦那さん変更", nullptr, otomosendaich, Color::Yellow << "ねこの先代旦那さんを変更します。\n"
																															"定型文では1ページ目の一番左下にある定型文をねこの先代旦那さんにコピーします。\n"
																															"キーボードでは、メニュー内で直接変更することができます。\n"
																															"変換候補変換の改行やタブが使えます。");
			}
			*otomo += otomoedit;

			*otomo += new MenuEntry(Color::Blue << "ねこ吸収", otomokyusyu, Color::Yellow << "ねこをハンターに吸収させます。\n他プレイヤーからは見えません。");
			*otomo += new MenuEntry(Color::Blue << "サポートゲージ最大", otomogagemax, Color::Yellow << "ニャンターのサポートゲージを最大にします。");
		}
		menu += otomo;

		MenuFolder *other = new MenuFolder(Color::Purple << "その他");
		{
			MenuFolder *chat = new MenuFolder(Color::Magenta << "チャット");
			{
				*chat += new MenuEntry(Color::Magenta << "チャット無限", Chatmugen, Color::Yellow << "オンラインで赤文字を出現させなくします。");
				*chat += new MenuEntry(Color::Magenta << "変換候補変換", Chathenkan, Color::Yellow << "キーボードを開いて、Rを押しながら文字を打つことで、変換候補の文字が変わります。");
				*chat += new MenuEntry(Color::Magenta << "変換候補変換対応文字一覧", nullptr, henkanitiran, Color::Yellow << "変換対応文字が書かれています。\n"
																															"変換しづらい文字や、改造でしか入力できない文字を入れています。");
			}
			*other += chat;

			MenuFolder *yopparaif = new MenuFolder(Color::Cyan << "酔っぱらい", Color::Yellow << "クエスト中は酔っぱらえません。");
			{
				*yopparaif += new MenuEntry(Color::Cyan << "即酔っぱらい", yopparai, yopparaiop, Color::Yellow << "酔っぱらいになるか変更できます。");
				*yopparaif += new MenuEntry(Color::Cyan << "1回お酒を飲むと酔っぱらい", yopparaikaisu, Color::Yellow << "1回お酒を飲むと酔っぱらいになります。");
			}
			*other += yopparaif;

			MenuFolder *hrf = new MenuFolder(Color::LimeGreen << "ハンターランク");
			{
				*hrf += new MenuEntry(Color::LimeGreen << "ハンターランク変更", nullptr, hrchange, Color::Yellow << "ハンターランクを変更できます。");
				*hrf += new MenuEntry(Color::LimeGreen << "ハンターランクポイント変更", nullptr, hrpchange, Color::Yellow << "ハンターランクポイントを変更できます。");
			}
			*other += hrf;

			MenuFolder *fenypugy = new MenuFolder(Color::Orange << "プーギー&フェニー");
			{
				*fenypugy += new MenuEntry(Color::Orange << "フェニー&プーギーの服変更", nullptr, fenypugyhuku, Color::Yellow << "フェニー&プーギーの服を変更できます。");
				*fenypugy += new MenuEntry(Color::Orange << "定型文でフェニー&プーギーの名前変更", nullptr, fenypugyname, Color::Yellow << "1ページ目の一番左下にある定型文を名前にコピーします。\n"
																																		"フェニー&プーギーの名前を変更できます。");
			}
			*other += fenypugy;

			MenuFolder *quest = new MenuFolder(Color::Yellow << "クエスト");
			{
				*quest += new MenuEntry(Color::Yellow << "クエストステータス変更", questclear, questclearchange, Color::Yellow << "クエストクリアか失敗を選択できます。");
				*quest += new MenuEntry(Color::Yellow << "クエストクリア後即リザルト", questwait, Color::Yellow << "クエストクリア後の待ち時間をスキップします。");
				*quest += new MenuEntry(Color::Yellow << "報酬画面スキップ", questresult, Color::Yellow << "報酬受取の時間を0にし、スキップします。");
				*quest += new MenuEntry(Color::Yellow << "最大ダウン回数変更", questdownsaidai, questdownsaidaiop, Color::Yellow << "最大ダウン回数を変更できます。");
				*quest += new MenuEntry(Color::Yellow << "現在のダウン回数変更", questdownima, questdownimaop, Color::Yellow << "現在のダウン回数を変更します。");
				*quest += new MenuEntry(Color::Yellow << "クエスト残り時間表示", questtime, Color::Yellow << "QT = Quest Timeです。\n"
																											"時:分:秒:フレーム\n"
																											"と表示します。");
				*quest += new MenuEntry(Color::Yellow << "選択肢を固定", savegamenkotei, saveyesno, Color::Yellow << "Rボタンを押すと固定できます。");
				*quest += new MenuEntry(Color::Yellow << "クエスト時間停止", nullptr, queststop, Color::Yellow << "クエスト時間を停止します。\n"
																												"Code by 舞姫");
				*quest += new MenuEntry(Color::Yellow << "全クエストクリア変更", nullptr, allquest, Color::Yellow << "ストーリーに不具合が起きる可能性があります。\n"
																													"予めバックアップを取ったり、サブキャラクターで実行してください。");
			}
			*other += quest;

			MenuFolder *syukaijo = new MenuFolder(Color::Lime << "集会所");
			{
				MenuFolder *syukaitukuru = new MenuFolder(Color::Magenta << "集会所を作る");
				{
					*syukaitukuru += new MenuEntry(Color::Magenta << "ターゲット変更", nullptr, syukaitukurutarget, Color::Yellow << "ターゲットを？？？？？にできます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "クエスト形式変更", nullptr, syukaitukuruquekeisiki, Color::Yellow << "クエスト形式を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "募集HR下限変更", nullptr, syukaitukuruhrkagen, Color::Yellow << "募集HRの下限を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "募集HR上限変更", nullptr, syukaitukuruhrjougen, Color::Yellow << "募集HRの上限を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "入室人数変更", nullptr, syukaitukuruninzuu, Color::Yellow << "入室人数を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "入室制限変更", nullptr, syukaitukuruseigen, Color::Yellow << "入室制限を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "パスワード有無変更", nullptr, syukaitukurupassumu, Color::Yellow << "パスワードの有無を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "募集文①変更", nullptr, syukaitukurubosyu1, Color::Yellow << "募集文①を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "募集文②変更", nullptr, syukaitukurubosyu2, Color::Yellow << "募集文②を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "募集文③変更", nullptr, syukaitukurubosyu3, Color::Yellow << "募集文③を変更できます。");
					*syukaitukuru += new MenuEntry(Color::Magenta << "募集文④変更", nullptr, syukaitukurubosyu4, Color::Yellow << "募集文④を変更できます。");
				}
				*syukaijo += syukaitukuru;

				MenuFolder *syukaisagasu = new MenuFolder(Color::Cyan << "集会所を探す");
				{
					*syukaisagasu += new MenuEntry(Color::Cyan << "ターゲット変更", nullptr, syukaisagasutarget, Color::Yellow << "ターゲットを？？？？？にできます。");
					*syukaisagasu += new MenuEntry(Color::Cyan << "クエスト形式変更", nullptr, syukaisagasuquekeisiki, Color::Yellow << "クエスト形式を変更できます。");
					*syukaisagasu += new MenuEntry(Color::Cyan << "ホストHR下限変更", nullptr, syukaisagasuhrkagen, Color::Yellow << "ホストHRの下限を変更できます");
					*syukaisagasu += new MenuEntry(Color::Cyan << "ホストHR上限変更", nullptr, syukaisagasuhrjougen, Color::Yellow << "ホストHRの上限を変更できます");
					*syukaisagasu += new MenuEntry(Color::Cyan << "クエスト中変更", nullptr, syukaisagasuquenow, Color::Yellow << "クエスト中を変更できます。");
					*syukaisagasu += new MenuEntry(Color::Cyan << "パスワード有無変更", nullptr, syukaisagasupassumu, Color::Yellow << "パスワードの有無を変更できます。");
				}
				*syukaijo += syukaisagasu;
			}
			*other += syukaijo;

			*other += new MenuEntry(Color::Purple << "画面に集会所のパス表示", passhyouji, Color::Yellow << "現在の部屋のパスワードを表示します。");
			*other += new MenuEntry(Color::Purple << "パスワード無効", Color::Yellow << "荒らしが可能となるので入れていません。");
			*other += new MenuEntry(Color::Purple << "主権限を自プレイヤーに変更", Color::Yellow << "荒らしが可能となるので入れていません。");
			*other += new MenuEntry(Color::Purple << "プレイヤーの現在座標表示", nowplayerzahyou, Color::Yellow << "プレイヤーの現在座標を表示します。");
			*other += new MenuEntry(Color::Purple << "宙に浮くバグ", tyubug, Color::Yellow << "L+Selectでオン、R+Selectでオフにできます。\n"
																							"高確率でエラーになります。注意してオンにしてください。\n"
																							"Code by 舞姫");
			*other += new MenuEntry(Color::Purple << "視野角変更", fovkotei, fovchange, Color::Yellow << "視野角を変更します。\n"
																										"(画面酔い注意)");
			*other += new MenuEntry(Color::Purple << "視野角変更改良版", nullptr, kamerasiyahack, Color::Yellow << "視野の倍率を変更できます。");
			*other += new MenuEntry(Color::Purple << "武器サイズ変更", nullptr, bukisizehack, Color::Yellow << "武器のサイズを変更できます。");
			*other += new MenuEntry(Color::Purple << "画面の明るさ変更", nullptr, kontorasuto, Color::Yellow << "画面の明るさ変更を変更できます。");
			*other += new MenuEntry(Color::Purple << "ギルドカード情報変更", nullptr, guildcardchange, Color::Yellow << "ギルドカードの情報を変更できます。\n"
																														"頑張って作りました。()");
			*other += new MenuEntry(Color::Purple << "リージョン変更", nullptr, Regionchange, Color::Yellow << "日本かヨーロッパに変更できます。");
			*other += new MenuEntry(Color::Purple << "村の貢献度変更", nullptr, murakoukendo, Color::Yellow << "村の貢献度を変更します。");
			*other += new MenuEntry(Color::Purple << "ルームサービス変更", nullptr, rumusabisuchange, Color::Yellow << "ルームサービスを変更します。");
			*other += new MenuEntry(Color::Purple << "障害物無視", nullptr, wallthrough, Color::Yellow << "障害物を無視するかどうか選択できます。\n"
																										"Code by 舞姫");
			*other += new MenuEntry(Color::Purple << "最大FPS変更", nullptr, Fpschange, Color::Yellow << "最大FPSを変更できます。");
		}
		menu += other;

		MenuFolder *omake = new MenuFolder(Color::Magenta << "おまけ");
		{
			MenuFolder *henkan = new MenuFolder(Color::Cyan << "変換");
			{
				*henkan += new MenuEntry(Color::Cyan << "32bit版符号あり16進数を10進数に変換", nullptr, HexToDecd32);
				*henkan += new MenuEntry(Color::Cyan << "32bit版符号なし16進数を10進数に変換", nullptr, HexToDecu32);
				*henkan += new MenuEntry(Color::Cyan << "16bit版符号あり16進数を10進数に変換", nullptr, HexToDecd16);
				*henkan += new MenuEntry(Color::Cyan << "16bit版符号なし16進数を10進数に変換", nullptr, HexToDecu16);
				*henkan += new MenuEntry(Color::Cyan << "8bit版符号あり16進数を10進数に変換", nullptr, HexToDecd8);
				*henkan += new MenuEntry(Color::Cyan << "8bit版符号なし16進数を10進数に変換", nullptr, HexToDecu8);
				*henkan += new MenuEntry(Color::Cyan << "10進数を16進数に変換", nullptr, DecToHex);
			}
			*omake += henkan;

			MenuFolder *dentaku = new MenuFolder(Color::LimeGreen << "電卓");
			{
				*dentaku += new MenuEntry(Color::LimeGreen << "16進数電卓", nullptr, hexcalc, Color::Yellow << "16進数を計算することができます。");
				*dentaku += new MenuEntry(Color::LimeGreen << "10進数電卓", nullptr, deccalc, Color::Yellow << "10進数を計算することができます。");
				*dentaku += new MenuEntry(Color::LimeGreen << "浮動小数点数電卓", nullptr, floatcalc, Color::Yellow << "浮動小数点数を計算することができます。");
			}
			*omake += dentaku;

			MenuFolder *rgbkakunin = new MenuFolder(Color::Orange << "RGBチェッカー");
			{
				*rgbkakunin += new MenuEntry(Color::Red << "R値入力", nullptr, rnyuryoku);
				*rgbkakunin += new MenuEntry(Color::Green << "G値入力", nullptr, gnyuryoku);
				*rgbkakunin += new MenuEntry(Color::Blue << "B値入力", nullptr, bnyuryoku);
				*rgbkakunin += new MenuEntry(Color::Yellow << "色確認", nullptr, rgbcheck);
			}
			*omake += rgbkakunin;

			//	MenuFolder *pointf = new MenuFolder(Color::LimeGreen << "ポインター表示");{
			//		*pointf += new MenuEntry(Color::LimeGreen << "ポインター表示", pointerhyoji);
			//		*pointf += new MenuEntry(Color::LimeGreen << "表示モード", nullptr, pointermode);
			//		*pointf += new MenuEntry(Color::LimeGreen << "ポインター1番目", nullptr, pointer1);
			//		*pointf += new MenuEntry(Color::LimeGreen << "ポインター2番目", nullptr, pointer2);
			//	}
			//	*omake += pointf;

			//	*omake += EntryWithHotkey(new MenuEntry("アドレス監視", HexEditor,
			//		Color::Yellow << "アドレスと値の監視ができます。\nA+↑で上に移動できます。\nA+↓で下に移動できます。"),{
			//			Hotkey(Key::R | A, "アドレス変更"),
			//			Hotkey(Key::R | B, "値を入力")});

			*omake += EntryWithHotkey(new MenuEntry(Color::Cyan << "アドレス監視", HexEditor2, Color::Yellow << "アドレスと値の監視ができます。\nA+↑で上に移動できます。\nA+↓で下に移動できます。"), {Hotkey(Key::R | A, "アドレス変更"), Hotkey(Key::R | B, "値を入力")});
			*omake += new MenuEntry(Color::Magenta << "3DSの情報を確認", nullptr, Information, Color::Yellow << "3DSの情報を確認できます。");
		}
		menu += omake;
	}

	//Plugin menu
	int main(void){
		PluginMenu *menu = new PluginMenu(	"" << Color::Red << "MHX"
											"" << Color::Green << "3gx"
											"" << Color::Blue << "dev6",
											0, 9, 4,
											"" << Color::Red << "ソース記述の人\n"
											"" << Color::Magenta << " ぽんぽこ\n"
											"" << Color::Blue << "サーチした人\n"
											"" << Color::Magenta << " ぽんぽこ\n"
											"" << Color::Yellow << " 舞姫氏\n"
											"" << Color::Yellow << " ymyn氏\n"
											"" << Color::Yellow << " Fort42氏\n"
											"" << Color::Green << "プラグイン作成において、ヒントを頂いた人\n"
											"" << Color::Yellow << " Naoki氏\n"
											"" << Color::Yellow << " クレラビ氏\n"
											"" << Color::Yellow << " だいち村長氏\n"
											"" << Color::Yellow << " けんじい氏\n"
											"" << Color::Red << "参考にしたサイト\n"
											"" << Color::Yellow << " mhgen.kiranico.com\n"
											"" << Color::Yellow << " www.sejuku.net/blog/24934\n"
											"" << Color::Red << "整合性チェックは行っていません。\n"
											"" << Color::Red << "データのバックアップは取ってください。\n"
											"" << Color::Red << "プラグインを楽しんでください。");
		// Synnchronize the menu with frame event
		menu->SynchronizeWithFrame(true);
		//HexEditorを無効化
		menu->SetHexEditorState(false);
		//Plugin Ready!を無効化
		menu->ShowWelcomeMessage(false);

		//オープニングメッセージ
		static bool file = false;
		std::string tid;
		Process::GetTitleID(tid);
		if (tid == "0004000000155400"){
			if (!file){
				if (!File::Exists("opskip.bin")){
					MessageBox("オープニングメッセージ", "ぽんぽこ @ponpoko094\nの3gxを使用していただき\nありがとうございます。\n次に利用規約が表示されます\n同意をお願いします。")();
					if (MessageBox("オープニングメッセージ", "利用規約\n①この3gxは無料で提供されます。\n②二次配布を禁止します。\n③この3gxを使用しデータが破損する等の\n損害に対して、ぽんぽこは一切の責任を負いません。\n④この3gxは日本版MHX\n  (タイトルID:0004000000155400)\n  でのみ使用できるものとします。\n利用規約に同意しますか？", DialogType::DialogYesNo)()){
						if (MessageBox("オープニングメッセージ", "利用規約に同意していただき\nありがとうございます。\n次回からオープニングメッセージを\nスキップしますか？", DialogType::DialogYesNo)()){
							File::Create("opskip.bin");
							MessageBox("オープニングメッセージ", "opskip.binを作成しました。\n設定を変更するために\n再起動をお願いします。")();
							abort();
						}else
							MessageBox("オープニングメッセージ", "プラグインを楽しんでください。")();
					}else{
						MessageBox("オープニングメッセージ", "利用規約に同意する必要があります。")();
						abort();
					}
				}
				file = true;
			}
		} else {
			MessageBox("オープニングメッセージ", "この3gxは日本版MHX(タイトルID:0004000000155400)でのみ動作します。")();
			abort();
		}

		//Plugin Ready!の代わり
		OSD::Notify(Color(234, 145, 152) << "ponpoko094's 3gx!");

		// Init our menu entries & folders
		InitMenu(*menu);
		// Launch menu and mainloop
		menu->Run();
		delete menu;
		return (0);
	}
}