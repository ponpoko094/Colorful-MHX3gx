#include "CTRPluginFramework.hpp"
#include "common.hpp"
#include "Unicode.h"
#include "csvc.h"
#include "3ds.h"
#include "Helpers.hpp"
#include <math.h>
#include <vector>
#include <stdio.h>

#define DU DPadUp
#define DD DPadDown
#define DL DPadLeft
#define DR DPadRight
#define CU CPadUp
#define CD CPadDown
#define CL CPadLeft
#define CR CPadRight

namespace CTRPluginFramework
{
	using StringVector = std::vector<std::string>;

	//宣言、定義
	u32 offset = 0, data = 0;
	u64 data64 = 0, cmp64 = 0;
	u32 data32 = 0, cmp32 = 0;
	u16 data16 = 0, cmp16 = 0;
	u8 data8 = 0, cmp8 = 0;
	u32 patch_address = 0;

	//スーパーノヴァ連射等
	void nova(MenuEntry *entry)
	{
		Keyboard keyboard("モーションを無くしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0xAF55A8, 0xE3A00001);
		if (choice == 1)
			Process::Write32(0xAF55A8, 0x13A00001);
	}

	//クエスト時間停止
	void queststop(MenuEntry *entry)
	{
		Keyboard keyboard("クエスト時間を停止しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x90E5BC, 0xEA000008);
		if (choice == 1)
			Process::Write32(0x90E5BC, 0xBA000008);
	}

	//名前変更
	void huntername(MenuEntry *entry)
	{
		std::string nameteikei, namenow, namekbd;
		Process::ReadString(0x83AE380, nameteikei, 0x1E, StringFormat::Utf8);
		Process::ReadString(0x831B72A, namenow, 0x1E, StringFormat::Utf8);
		Keyboard keyboard("どちらで変更しますか？\n現在の名前[" + namenow + "]", {"定型文", "キーボード"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			for (int i = 0; i < 8; i++)
				Process::Write32(i * 4 + 0x831B72A, 0);
			Process::WriteString(0x831B72A, nameteikei, StringFormat::Utf8);
		}
		if (choice == 1)
		{
			Keyboard keyboard("名前を入力してください。");
			keyboard.Open(namekbd);
			for (int i = 0; i < 8; i++)
				Process::Write32(i * 4 + 0x831B72A, 0);
			Process::WriteString(0x831B72A, namekbd, StringFormat::Utf8);
		}
	}

	//障害物無視
	void wallthrough(MenuEntry *entry)
	{
		Keyboard keyboard("障害物無視しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x3246F4, 0xEA00001E);
		if (choice == 1)
			Process::Write32(0x3246F4, 0x0A00001E);
	}

	//ハンターランク変更
	void hrchange(MenuEntry *entry)
	{
		u16 hr;
		Process::Read16(0x831B76A, hr);
		Keyboard keyboard(Utils::Format("ハンターランクを入力してください\n現在[%u]", hr));
		keyboard.IsHexadecimal(false);
		keyboard.Open(hr);
		Process::Write16(0x831B76A, hr);
	}

	//モンスターワンパンキル
	void onekill(MenuEntry *entry)
	{
		Keyboard keyboard("瞬殺しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x8CF54C, 0xE3A01000);
		if (choice == 1)
			Process::Write32(0x8CF54C, 0xE0911003);
	}

	//宙に浮くバグ
	void tyubug(MenuEntry *entry)
	{
		if (Controller::IsKeysPressed(L + Select))
		{
			Process::WriteFloat(0xC01410, 2);
			Process::Write32(0xC01414, 0xE51F000C);
			Process::Write32(0xC01418, 0xE5860040);
			Process::Write32(0xC0141C, 0xED960A10);
			Process::Write32(0xC01420, 0xE12FFF1E);
			Process::Write32(0x30A2AC, 0xEB23DC58);
			Process::Write32(0xC01424, 0xE51F001C);
			Process::Write32(0xC01428, 0xE5860040);
			Process::Write32(0xC0142C, 0xE3A00000);
			Process::Write32(0xC01430, 0xE12FFF1E);
			Process::Write32(0x2F7BA4, 0xEB24261E);
		}
		if (Controller::IsKeysPressed(R + Select))
			Process::WriteFloat(0xC01410, 1);
	}

	//属性
	void zokusei(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("属性値を入力してください。");
		keyboard.IsHexadecimal(false);
		keyboard.Open(a);
		Process::Write16(0x831B45A, a);
	}

	//ゼニー
	void money(MenuEntry *entry)
	{
		u32 a;
		Keyboard keyboard("所持金を入力してください。");
		keyboard.IsHexadecimal(false);
		keyboard.Open(a);
		Process::Write32(0x83B3818, a);
	}

	//ポイント
	void point(MenuEntry *entry)
	{
		u32 a;
		Keyboard keyboard("龍歴員ポイントを入力してください。");
		keyboard.IsHexadecimal(false);
		keyboard.Open(a);
		Process::Write32(0x83B3820, a);
	}

	//全狩技開放
	void kariwazakaihou(MenuEntry *entry)
	{
		Process::Read32(0x0DD9F30, offset);
		Process::Write32(offset + 0x9E0, 0xFFFFFFFE);
		Process::Write32(offset + 0x9E4, 0x00FFFFFF);
		Process::Write32(offset + 0x9E8, 0xFFFFFFFE);
		Process::Write32(offset + 0x9EC, 0xFFFFFFFF);
		Process::Write32(offset + 0x9F0, 0x0003FFFF);
	}

	//採取無限
	void infsaisyu(MenuEntry *entry)
	{
		Keyboard keyboard("採取無限にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0847594, 0xE2400000);
			Process::Write32(0x0847684, 0xE2400000);
			Process::Write32(0x08CD544, 0xE3A00000);
		}
		if (choice == 1)
		{
			Process::Write32(0x0847594, 0xE2400001);
			Process::Write32(0x0847684, 0xE2400001);
			Process::Write32(0x08CD544, 0xEBFF5F26);
		}
	}

	//素材なしで調合可能
	void nosozaityougou(MenuEntry *entry)
	{
		Keyboard keyboard("素材無しで調合可能にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x039D88C, 0xE3A00000);
			Process::Write32(0x0A0ADCC, 0xE3A00000);
		}
		if (choice == 1)
		{
			Process::Write32(0x039D88C, 0xE12FFF32);
			Process::Write32(0x0A0ADCC, 0xEB01A495);
		}
	}

	//素材無しで装備作成可能
	void nosozaisoubi(MenuEntry *entry)
	{
		Keyboard keyboard("素材無しで装備作成可能にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x018587C, 0xE3A00063);
			Process::Write32(0x018644C, 0xE3A00001);
			Process::Write32(0x041ABA8, 0xE3A00001);
			Process::Write32(0x0421AB0, 0xE3A00001);
		}
		if (choice == 1)
		{
			Process::Write32(0x018587C, 0xE0800004);
			Process::Write32(0x018644C, 0xA3A00001);
			Process::Write32(0x041ABA8, 0xEB1B2B79);
			Process::Write32(0x0421AB0, 0xEB1B0FB7);
		}
	}

	//スタミナ無限
	void infstamina(MenuEntry *entry)
	{
		Keyboard keyboard("スタミナ無限にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x0A87104, 0xE3A00001);
		if (choice == 1)
			Process::Write32(0x0A87104, 0xE12FFF32);
	}

	//常にマップ表示
	void alwaysmap(MenuEntry *entry)
	{
		Keyboard keyboard("常にマップ表示しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x02CFF30, 0xE3A00001);
		if (choice == 1)
			Process::Write32(0x02CFF30, 0xEB207503);
	}

	//常にモンスターペイント
	void alwayspeint(MenuEntry *entry)
	{
		Keyboard keyboard("常にモンスターペイントしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x039CEB0, 0xE3A00001);
			Process::Write32(0x08ECBB4, 0xE3A00001);
		}
		if (choice == 1)
		{
			Process::Write32(0x039CEB0, 0xEB1D4123);
			Process::Write32(0x08ECBB4, 0xD3A00000);
		}
	}

	//会心率100パーセント
	void critical100(MenuEntry *entry)
	{
		Keyboard keyboard("会心率を100％にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x08F3150, 0xE3A000C8);
		if (choice == 1)
			Process::Write32(0x08F3150, 0xEB07E80A);
	}

	//狩技無限
	void infkariwaza(MenuEntry *entry)
	{
		Keyboard keyboard("狩技を無限にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0A89F70, 0xE92D0001);
			Process::Write32(0x0A89F74, 0xE1DC00F2);
			Process::Write32(0x0A89F78, 0xE18300B2);
			Process::Write32(0x0A89F7C, 0xE8BD0001);
			Process::Write32(0x0A89F80, 0xEA000000);
		}
		if (choice == 1)
		{
			Process::Write32(0x0A89F70, 0xE19320F2);
			Process::Write32(0x0A89F74, 0xE1DC30F2);
			Process::Write32(0x0A89F78, 0xE1520003);
			Process::Write32(0x0A89F7C, 0xAA000001);
			Process::Write32(0x0A89F80, 0xE3A00000);
		}
	}

	//ボウガンオートリロード
	void autoreload(MenuEntry *entry)
	{
		Keyboard keyboard("ボウガン自動装填しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0324984, 0xE5C405AA);
			Process::Write32(0x032498C, 0xE5C405AB);
		}
		if (choice == 1)
		{
			Process::Write32(0x0324984, 0xE1A02C23);
			Process::Write32(0x032498C, 0xE5C425AB);
		}
	}

	//HP無限
	void infhp(MenuEntry *entry)
	{
		Keyboard keyboard("HP無限にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x046C37C, 0xE1D025F4);
			Process::Write32(0x046C398, 0xE1C025B2);
		}
		if (choice == 1)
		{
			Process::Write32(0x046C37C, 0xE1D025F2);
			Process::Write32(0x046C398, 0xE1D025F4);
		}
	}

	//斬れ味無限
	void infsharpness(MenuEntry *entry)
	{
		Keyboard keyboard("斬れ味無限にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x035B270, 0xE5901218);
		if (choice == 1)
			Process::Write32(0x035B270, 0xE0811004);
	}

	//ボウガンの弾、アイテム無限
	void infitemammo(MenuEntry *entry)
	{
		Keyboard keyboard("アイテム&弾丸を無限しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x035C658, 0xE3A07000);
		if (choice == 1)
			Process::Write32(0x035C658, 0xE1A07002);
	}

	//溜め最大
	void chargemax(MenuEntry *entry)
	{
		Keyboard keyboard("チャージゲージ最大にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x032D004, 0xE3A01064);
		if (choice == 1)
			Process::Write32(0x032D004, 0xE0811005);
	}

	//運搬物をポーチに入れる
	void tamagoporch(MenuEntry *entry)
	{
		Keyboard keyboard("運搬物をポーチに入れますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x0AE5488, 0x93A00000);
		if (choice == 1)
			Process::Write32(0x0AE5488, 0x93A00001);
	}

	//常に3つ狩技装着可能
	void always3kariwaza(MenuEntry *entry)
	{
		Keyboard keyboard("常に3つ狩技装着可能にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0AF8C0C, 0xE3A00003);
			Process::Write32(0x0AF8C10, 0xE12FFF1E);
		}
		if (choice == 1)
		{
			Process::Write32(0x0AF8C0C, 0xE3510000);
			Process::Write32(0x0AF8C10, 0xE3A00000);
		}
	}

	//スーパーアーマー
	void superarmor(MenuEntry *entry)
	{
		Keyboard keyboard("スーパーアーマーにしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0322C60, 0xE3A05001);
			Process::Write32(0x03322F0, 0xE3A00001);
		}
		if (choice == 1)
		{
			Process::Write32(0x0322C60, 0xE3A05000);
			Process::Write32(0x03322F0, 0xE3A00000);
		}
	}

	//アイテムボックス1400枠拡張
	void itembox1400(MenuEntry *entry)
	{
		Keyboard keyboard("アイテムボックス1400枠拡張しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x09F1AB0, 0xE5901734);
			Process::Write32(0x09F1AB4, 0xE3811606);
			Process::Write32(0x09F1AB8, 0xE5801734);
			Process::Write32(0x09F1ABC, 0xE3A01002);
			Process::Write32(0x09F1AC0, 0xE1A00000);
		}
		if (choice == 1)
		{
			Process::Write32(0x09F1AB0, 0xE5900734);
			Process::Write32(0x09F1AB4, 0xE3100602);
			Process::Write32(0x09F1AB8, 0x13A01001);
			Process::Write32(0x09F1ABC, 0xE3100501);
			Process::Write32(0x09F1AC0, 0x12811001);
		}
	}

	//装備欄開放
	void soubikaihou(MenuEntry *entry)
	{
		Keyboard keyboard("装備欄開放しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0B0832C, 0xE3A00001);
			Process::Write32(0x0B0825C, 0xE3A00001);
			Process::Write32(0x0AE59AC, 0xE3A00001);
		}
		if (choice == 1)
		{
			Process::Write32(0x0B0832C, 0x13A00001);
			Process::Write32(0x0B0825C, 0x13A00001);
			Process::Write32(0x0AE59AC, 0x13A00001);
		}
	}

	//無敵
	void invicible(MenuEntry *entry)
	{
		Keyboard keyboard("無敵にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x0A2E3D0, 0xE3A00000);
		if (choice == 1)
			Process::Write32(0x0A2E3D0, 0xE3A00001);
	}

	//斬れ味レベル+2
	void sharpness2(MenuEntry *entry)
	{
		Keyboard keyboard("斬れ味レベル+2にしますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x04F5954, 0xE1A00000);
			Process::Write32(0x0C18EF4, 0xE3510053);
			Process::Write32(0x0C18EF8, 0x03A00001);
			Process::Write32(0x0C18EFC, 0xE12FFF1E);
			Process::Write32(0x0AED3D0, 0xEA04AEC7);
		}
		if (choice == 1)
		{
			Process::Write32(0x04F5954, 0x0A000010);
			Process::Write32(0x0C18EF4, 0x0);
			Process::Write32(0x0C18EF8, 0x0);
			Process::Write32(0x0C18EFC, 0x0);
			Process::Write32(0x0AED3D0, 0xE3500000);
		}
	}

	//全アイテム販売
	void allitemsold(MenuEntry *entry)
	{
		Keyboard keyboard("全アイテム販売しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x02A124C, 0xE3A01E7A);
			Process::Write32(0x02A184C, 0xE08A9007);
			Process::Write32(0x02A1854, 0xE2899001);
			Process::Write32(0x02A1868, 0xE08A1007);
		}
		if (choice == 1)
		{
			Process::Write32(0x02A124C, 0xE1A01006);
			Process::Write32(0x02A184C, 0xE0860080);
			Process::Write32(0x02A1854, 0xE1D090BE);
			Process::Write32(0x02A1868, 0xE1D110BE);
		}
	}

	//サポートゲージ無限
	void otomogagemax(MenuEntry *entry)
	{
		Process::Read32(0xDD5348, offset);
		if (Process::Read32(offset + 0x14, cmp32) && cmp32 != 0x0)
		{
			Process::Read32(offset + 0x14, offset);
			Process::Write16(offset + 0x2220, 0x384);
		}
	}

	//アイテムを99個まで持てる
	void haveitem99(MenuEntry *entry)
	{
		Keyboard keyboard("アイテムを99個まで持ちますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0C18DB0, 0xE5C50021);
			Process::Write32(0x0C18DB4, 0xE92D4007);
			Process::Write32(0x0C18DB8, 0xE59F0044);
			Process::Write32(0x0C18DBC, 0xE5900000);
			Process::Write32(0x0C18DC0, 0xE5900014);
			Process::Write32(0x0C18DC4, 0xE5900068);
			Process::Write32(0x0C18DC8, 0xE5901000);
			Process::Write32(0x0C18DCC, 0xE59F2034);
			Process::Write32(0x0C18DD0, 0xE1510002);
			Process::Write32(0x0C18DD4, 0x18BD8007);
			Process::Write32(0x0C18DD8, 0xE5D0100E);
			Process::Write32(0x0C18DDC, 0xE3510001);
			Process::Write32(0x0C18DE0, 0x18BD8007);
			Process::Write32(0x0C18DE4, 0xE280000E);
			Process::Write32(0x0C18DE8, 0xE59F101C);
			Process::Write32(0x0C18DEC, 0xE0811000);
			Process::Write32(0x0C18DF0, 0xE3A02063);
			Process::Write32(0x0C18DF4, 0xE4C02038);
			Process::Write32(0x0C18DF8, 0xE1510000);
			Process::Write32(0x0C18DFC, 0x1AFFFFFC);
			Process::Write32(0x0C18E00, 0xE8BD8007);
			Process::Write32(0x0C18E04, 0x00DD41B8);
			Process::Write32(0x0C18E08, 0x00DA0CA8);
			Process::Write32(0x0C18E0C, 0x0001AA58);
			Process::Write32(0x031689C, 0xEB240943);
		}
		if (choice == 1)
		{
			Process::Write32(0x0C18DB0, 0x0);
			Process::Write32(0x0C18DB4, 0x0);
			Process::Write32(0x0C18DB8, 0x0);
			Process::Write32(0x0C18DBC, 0x0);
			Process::Write32(0x0C18DC0, 0x0);
			Process::Write32(0x0C18DC4, 0x0);
			Process::Write32(0x0C18DC8, 0x0);
			Process::Write32(0x0C18DCC, 0x0);
			Process::Write32(0x0C18DD0, 0x0);
			Process::Write32(0x0C18DD4, 0x0);
			Process::Write32(0x0C18DD8, 0x0);
			Process::Write32(0x0C18DDC, 0x0);
			Process::Write32(0x0C18DE0, 0x0);
			Process::Write32(0x0C18DE4, 0x0);
			Process::Write32(0x0C18DE8, 0x0);
			Process::Write32(0x0C18DEC, 0x0);
			Process::Write32(0x0C18DF0, 0x0);
			Process::Write32(0x0C18DF4, 0x0);
			Process::Write32(0x0C18DF8, 0x0);
			Process::Write32(0x0C18DFC, 0x0);
			Process::Write32(0x0C18E00, 0x0);
			Process::Write32(0x0C18E04, 0x0);
			Process::Write32(0x0C18E08, 0x0);
			Process::Write32(0x0C18E0C, 0x0);
			Process::Write32(0x031689C, 0xE5C50021);
		}
	}

	//溜め高速化
	void chargespeedup(MenuEntry *entry)
	{
		Keyboard keyboard("溜め高速化しますか？", {"はい", "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write32(0x0C18E24, 0xE24F0000);
			Process::Write32(0x0C18E28, 0xEAF96EC2);
			Process::Write32(0x0C18E2C, 0xE92D0002);
			Process::Write32(0x0C18E30, 0xE59F1014);
			Process::Write32(0x0C18E34, 0xE151000E);
			Process::Write32(0x0C18E38, 0x024F0014);
			Process::Write32(0x0C18E3C, 0xEDD01A07);
			Process::Write32(0x0C18E40, 0xE8BD0002);
			Process::Write32(0x0C18E44, 0xEAF96EC2);
			Process::Write32(0x0C18E48, 0x41200000);
			Process::Write32(0x0C18E4C, 0x0156B438);
			Process::Write32(0x0A74950, 0xEA069135);
			Process::Write32(0x0326228, 0xEA23CAFD);
		}
		if (choice == 1)
		{
			Process::Write32(0x0C18E24, 0x0);
			Process::Write32(0x0C18E28, 0x0);
			Process::Write32(0x0C18E2C, 0x0);
			Process::Write32(0x0C18E30, 0x0);
			Process::Write32(0x0C18E34, 0x0);
			Process::Write32(0x0C18E38, 0x0);
			Process::Write32(0x0C18E3C, 0x0);
			Process::Write32(0x0C18E40, 0x0);
			Process::Write32(0x0C18E44, 0x0);
			Process::Write32(0x0C18E48, 0x0);
			Process::Write32(0x0C18E4C, 0x0);
			Process::Write32(0x0A74950, 0xEDD01A07);
			Process::Write32(0x0326228, 0xEA1D39C2);
		}
	}

	static float pspeed = 1;
	void speedop(MenuEntry *entry)
	{
		Keyboard keyboard("速度を何倍にしますか？", {"1倍", "2倍", "3倍", "4倍", "5倍", "6倍", "7倍", "8倍", "9倍", "10倍"});
		if (int choice = keyboard.Open() != -1)
			pspeed = choice + 1;
	}
	//速度変更
	void speedchange(MenuEntry *entry)
	{
		Process::Write32(0xC18D80, 0xED9F1A04);
		Process::Write32(0xC18D84, 0xED9F2A04);
		Process::Write32(0xC18D88, 0xEE311A02);
		Process::Write32(0xC18D8C, 0xEE000A01);
		Process::Write32(0xC18D90, 0xE1A00004);
		Process::Write32(0xC18D94, 0xE12FFF1E);
		Process::Write32(0xC18D98, 0xBF800000);
		Process::WriteFloat(0xC18D9C, pspeed);
		Process::Write32(0xC18DA0, 0xE51F000C);
		Process::Write32(0xC18DA4, 0xE5860040);
		Process::Write32(0xC18DA8, 0xE3A00000);
		Process::Write32(0xC18DAC, 0xE12FFF1E);
		Process::Write32(0x316898, 0xEB240940);
		Process::Write32(0x320534, 0xEB23E211);
		if (Controller::IsKeysPressed(L + Select))
		{
			Process::WriteFloat(0xC18D9C, pspeed);
			OSD::Notify("Speed:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(R + Select))
		{
			Process::WriteFloat(0xC18D9C, 1);
			OSD::Notify("Speed:" << Color::Red << "OFF!");
		}
	}

	static u8 pattack = 0x1;
	//攻撃力倍率変更設定
	void attackop(MenuEntry *entry)
	{
		Keyboard keyboard("攻撃力を何倍にしますか?\n1~255の間");
		keyboard.IsHexadecimal(false);
		keyboard.Open(pattack);
	}

	//攻撃力変更
	void attackchange(MenuEntry *entry)
	{
		if (Controller::IsKeysPressed(Y + DU))
		{
			Process::Write32(0xC18E50, 0xE3A01000);
			Process::Write32(0xC18E54, 0xE92D4018);
			Process::Write8(0xC18E58, pattack);
			Process::Write8(0xC18E59, 0x40);
			Process::Write16(0xC18E5A, 0xE3A0);
			Process::Write32(0xC18E5C, 0xE1D232B2);
			Process::Write32(0xC18E60, 0xE0030493);
			Process::Write32(0xC18E64, 0xE3530C7D);
			Process::Write32(0xC18E68, 0xA3A03C7D);
			Process::Write32(0xC18E6C, 0xE1C232B2);
			Process::Write32(0xC18E70, 0xE8BD8018);
			Process::Write32(0x8F1B84, 0xEB0C9CB1);
			OSD::Notify("Attack:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(Y + DD))
		{
			Process::Write32(0xC18E50, 0xE3A01000);
			Process::Write32(0xC18E54, 0xE92D4018);
			Process::Write8(0xC18E58, 0x1);
			Process::Write8(0xC18E59, 0x40);
			Process::Write16(0xC18E5A, 0xE3A0);
			Process::Write32(0xC18E5C, 0xE1D232B2);
			Process::Write32(0xC18E60, 0xE0030493);
			Process::Write32(0xC18E64, 0xE3530C7D);
			Process::Write32(0xC18E68, 0xA3A03C7D);
			Process::Write32(0xC18E6C, 0xE1C232B2);
			Process::Write32(0xC18E70, 0xE8BD8018);
			Process::Write32(0x8F1B84, 0xEB0C9CB1);
			OSD::Notify("Attack:" << Color::Red << "OFF!");
		}
	}

	static u8 pdefence = 0x1;
	//防御力倍率変更設定
	void defenceop(MenuEntry *entry)
	{
		Keyboard keyboard("防御力を何倍にしますか?\n1~255の間");
		keyboard.IsHexadecimal(false);
		keyboard.Open(pdefence);
	}

	//防御力変更
	void defencechange(MenuEntry *entry)
	{
		if (Controller::IsKeysPressed(X + DU))
		{
			Process::Write32(0x0C18E80, 0xE92D4004);
			Process::Write8(0x0C18E84, pdefence);
			Process::Write8(0x0C18E85, 0x20);
			Process::Write16(0x0C18E86, 0xE3A0);
			Process::Write32(0x0C18E88, 0xE0000290);
			Process::Write32(0x0C18E8C, 0xE3500C7D);
			Process::Write32(0x0C18E90, 0xA3A00C7D);
			Process::Write32(0x0C18E94, 0xE18100B5);
			Process::Write32(0x0C18E98, 0xE8BD8004);
			Process::Write32(0x08F2AC4, 0xEB0C98ED);
			OSD::Notify("Defence:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(X + DD))
		{
			Process::Write32(0x0C18E80, 0xE92D4004);
			Process::Write8(0x0C18E84, 0x1);
			Process::Write8(0x0C18E85, 0x20);
			Process::Write16(0x0C18E86, 0xE3A0);
			Process::Write32(0x0C18E88, 0xE0000290);
			Process::Write32(0x0C18E8C, 0xE3500C7D);
			Process::Write32(0x0C18E90, 0xA3A00C7D);
			Process::Write32(0x0C18E94, 0xE18100B5);
			Process::Write32(0x0C18E98, 0xE8BD8004);
			Process::Write32(0x08F2AC4, 0xEB0C98ED);
			OSD::Notify("Defence:" << Color::Red << "OFF!");
		}
	}

	//肌の色変更
	void skinrgbchange(MenuEntry *entry)
	{
		Keyboard keyboard("肌の色を何色にしますか？", {"赤色",
													   "橙色",
													   "黄色",
													   "黄緑",
													   "緑色",
													   "緑水",
													   "水色",
													   "水青",
													   "青色",
													   "紫色",
													   "紫桃",
													   "白色",
													   "灰色",
													   "黒色"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x831B70C, 0x000000FF);
		if (choice == 1)
			Process::Write32(0x831B70C, 0x000080FF);
		if (choice == 2)
			Process::Write32(0x831B70C, 0x0000FFFF);
		if (choice == 3)
			Process::Write32(0x831B70C, 0x0000FF80);
		if (choice == 4)
			Process::Write32(0x831B70C, 0x0000FF00);
		if (choice == 5)
			Process::Write32(0x831B70C, 0x0080FF00);
		if (choice == 6)
			Process::Write32(0x831B70C, 0x00FFFF00);
		if (choice == 7)
			Process::Write32(0x831B70C, 0x00FF8000);
		if (choice == 8)
			Process::Write32(0x831B70C, 0x00FF0000);
		if (choice == 9)
			Process::Write32(0x831B70C, 0x00FF0080);
		if (choice == 10)
			Process::Write32(0x831B70C, 0x00FF00FF);
		if (choice == 11)
			Process::Write32(0x831B70C, 0x008000FF);
		if (choice == 12)
			Process::Write32(0x831B70C, 0x00FFFFFF);
		if (choice == 13)
			Process::Write32(0x831B70C, 0x00808080);
		if (choice == 14)
			Process::Write32(0x831B70C, 0x00000000);
	}

	//肌の色R設定
	void skinrchange(MenuEntry *entry)
	{
		u8 r;
		Keyboard keyr("赤の値を入力してください\n1~255の間");
		keyr.IsHexadecimal(false);
		if (keyr.Open(r) != -1)
			Process::Write8(0x831B70C, r);
	}

	//肌の色G設定
	void skingchange(MenuEntry *entry)
	{
		u8 g;
		Keyboard keyg("緑の値を入力してください\n1~255の間");
		keyg.IsHexadecimal(false);
		if (keyg.Open(g) != -1)
			Process::Write8(0x831B70D, g);
	}

	//肌の色B設定
	void skinbchange(MenuEntry *entry)
	{
		u8 b;
		Keyboard keyb("青の値を入力してください\n1~255の間");
		keyb.IsHexadecimal(false);
		if (keyb.Open(b) != -1)
			Process::Write8(0x831B70E, b);
	}

	static u8 nattack = 0x1;
	//ニャンター攻撃力変更
	void otomoattack(MenuEntry *entry)
	{
		if (Controller::IsKeysPressed(Y + DU))
		{
			Process::Write32(0xC18F80, 0xE92D400C);
			Process::Write8(0xC18F84, nattack);
			Process::Write8(0xC18F85, 0x30);
			Process::Write16(0xC18F86, 0xE3A0);
			Process::Write32(0xC18F88, 0xE1D522B2);
			Process::Write32(0xC18F8C, 0xE0020392);
			Process::Write32(0xC18F90, 0xE3520C7D);
			Process::Write32(0xC18F94, 0xA3A02C7D);
			Process::Write32(0xC18F98, 0xE1C522B2);
			Process::Write32(0xC18F9C, 0xE1D523BA);
			Process::Write32(0xC18FA0, 0xE0020392);
			Process::Write32(0xC18FA4, 0xE3520C7D);
			Process::Write32(0xC18FA8, 0xA3A02C7D);
			Process::Write32(0xC18FAC, 0xE1C523BA);
			Process::Write32(0xC18FB0, 0xE3A01010);
			Process::Write32(0xC18FB4, 0xE8BD800C);
			Process::Write32(0xC18FB8, 0x00000005);
			Process::Write32(0x8F4198, 0xEB0C9378);
			Process::Write32(0x5D60BC, 0xEA000002);
			OSD::Notify("Prowler Attack:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(Y + DD))
		{
			Process::Write32(0xC18F80, 0xE92D400C);
			Process::Write8(0xC18F84, 0x1);
			Process::Write8(0xC18F85, 0x30);
			Process::Write16(0xC18F86, 0xE3A0);
			Process::Write32(0xC18F88, 0xE1D522B2);
			Process::Write32(0xC18F8C, 0xE0020392);
			Process::Write32(0xC18F90, 0xE3520C7D);
			Process::Write32(0xC18F94, 0xA3A02C7D);
			Process::Write32(0xC18F98, 0xE1C522B2);
			Process::Write32(0xC18F9C, 0xE1D523BA);
			Process::Write32(0xC18FA0, 0xE0020392);
			Process::Write32(0xC18FA4, 0xE3520C7D);
			Process::Write32(0xC18FA8, 0xA3A02C7D);
			Process::Write32(0xC18FAC, 0xE1C523BA);
			Process::Write32(0xC18FB0, 0xE3A01010);
			Process::Write32(0xC18FB4, 0xE8BD800C);
			Process::Write32(0xC18FB8, 0x00000005);
			Process::Write32(0x8F4198, 0xEB0C9378);
			Process::Write32(0x5D60BC, 0xEA000002);
			OSD::Notify("Prowler Attack:" << Color::Red << "OFF!");
		}
		if (Process::Read32(0xC18FB8, cmp32) && cmp32 != 0x0)
		{
			Process::Read32(0xC18FB8, data32);
			data32 += 0xFFFFFFFF;
			Process::Write32(0xC18FB8, data32);
		}
		if (Process::Read32(0xC18FB8, cmp32) && cmp32 == 0x1)
			Process::Write32(0x5D60BC, 0x0A000002);
	}

	//ニャンター攻撃力変更設定
	void otomoattackop(MenuEntry *entry)
	{
		Keyboard keyboard("防御力を何倍にしますか?\n1~255の間");
		keyboard.IsHexadecimal(false);
		keyboard.Open(nattack);
	}

	static u8 ndefence = 0x1;
	//ニャンター防御力変更
	void otomodefence(MenuEntry *entry)
	{
		if (Controller::IsKeysPressed(X + DU))
		{
			Process::Write32(0xC18FE0, 0xE92D4004);
			Process::Write8(0xC18FE4, ndefence);
			Process::Write8(0xC18FE5, 0x20);
			Process::Write16(0xC18FE6, 0xE3A0);
			Process::Write32(0xC18FE8, 0xE0000290);
			Process::Write32(0xC18FEC, 0xE3500C7D);
			Process::Write32(0xC18FF0, 0xA3A00C7D);
			Process::Write32(0xC18FF4, 0xE18100B5);
			Process::Write32(0xC18FF8, 0xE8BD8004);
			Process::Write32(0x8F4C1C, 0xEB0C90EF);
			Process::Write32(0xC18FFC, 0x00000005);
			Process::Write32(0x5D60BC, 0xEA000002);
			OSD::Notify("Prowler Defence:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(X + DD))
		{
			Process::Write8(0xC18FE4, 0x01);
			OSD::Notify("Prowler Defence:" << Color::Red << "OFF!");
		}
		if (Process::Read32(0xC18FFC, cmp32) && cmp32 != 0x0)
		{
			Process::Read32(0xC18FFC, data32);
			data32 += 0xFFFFFFFF;
			Process::Write32(0xC18FFC, data32);
		}
		offset = 0x00000000;
		if (Process::Read32(0xC18FFC, cmp32) && cmp32 == 0x1)
			Process::Write32(0x5D60BC, 0xA000002);
	}

	//ニャンター防御力変更設定
	void otomodefenceop(MenuEntry *entry)
	{
		Keyboard keyboard("防御力を何倍にしますか?\n1~255の間");
		keyboard.IsHexadecimal(false);
		keyboard.Open(ndefence);
	}

	//画面にパス表示
	void passhyouji(MenuEntry *entry)
	{
		static int adrs_on = 0;
		static u16 pass;
		u16 online;
		adrs_on = true;
		Process::Read16(0xE2251C, pass);
		Process::Read16(0x80913EC, online);

		if (online == 0x100)
		{
			adrs_on = true;
			OSD::Run([](const Screen &screen) {
				if (!screen.IsTop)
					return (false);
				if (adrs_on == true)
				{
					if (pass <= 9999)
					{
						if (pass <= 999)
						{
							screen.Draw(Utils::Format("Pass 0%u", pass), 10, 80, Color::Yellow);
							adrs_on = false;
						}
						else
						{
							screen.Draw(Utils::Format("Pass %u", pass), 10, 80, Color::Yellow);
							adrs_on = false;
						}
					}
				}
				return (true);
			});
		}
		else
			adrs_on = false;
	}

	//ガンランス弾無限
	void gunlanceammo(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write8(offset + 0x1922, 0xFF);
	}

	//ガンランスオーバーヒート無効
	void nooverheat(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write32(offset + 0x1FF8, 0x0);
	}

	static u16 heat;
	//ヒートゲージ変更
	void heatgagechange(MenuEntry *entry)
	{
		Keyboard keyboard("固定したい値を決めてください。\n0:最小\n4D:橙\nD4:赤\n12C:最大");
		keyboard.Open(heat);
	}

	//ガンランスヒートゲージ固定
	void heatgage(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write16(offset + 0x2018, heat);
	}

	//護石作成
	void gosekisakusei(MenuEntry *entry)
	{
		Keyboard keyboard("護石を作成しますか？", {"はい",
												   "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write8(0x8386D78, 0x6);
			Process::Write8(0x8386D7A, 0x1);
			Process::Write16(0x8386D8E, 0x147);
		}
	}

	//護石種類変更
	void gosekirare(MenuEntry *entry)
	{
		Keyboard keyboard("護石の種類を選んでください", {"表示無し",
														 "兵士の護石",
														 "闘士の護石",
														 "騎士の護石",
														 "城塞の護石",
														 "女王の護石",
														 "王の護石",
														 "龍の護石"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x8386D7A, choice);
	}

	//護石第一スキル変更
	void gosekiskill1(MenuEntry *entry)
	{
		Keyboard keyboard("第一スキルを選んでください", {"スキル無し",
														 "毒",
														 "麻痺",
														 "睡眠",
														 "気絶",
														 "聴覚保護",
														 "風圧",
														 "耐震",
														 "だるま",
														 "耐暑",
														 "耐寒",
														 "寒冷適応",
														 "炎熱適応",
														 "盗み無効",
														 "対防御DOWN",
														 "狂撃耐性",
														 "細菌学",
														 "裂傷",
														 "攻撃",
														 "防御",
														 "体力",
														 "火耐性",
														 "水耐性",
														 "雷耐性",
														 "氷耐性",
														 "龍耐性",
														 "属性耐性",
														 "火属性攻撃",
														 "水属性攻撃",
														 "雷属性攻撃",
														 "氷属性攻撃",
														 "龍属性攻撃",
														 "属性攻撃",
														 "特殊攻撃",
														 "研ぎ師",
														 "匠",
														 "斬れ味",
														 "剣術",
														 "研磨術",
														 "鈍器",
														 "抜刀会心",
														 "抜刀滅気",
														 "納刀",
														 "装填速度",
														 "反動",
														 "精密射撃",
														 "通常弾強化",
														 "貫通弾強化",
														 "散弾強化",
														 "重撃弾強化",
														 "通常弾追加",
														 "貫通弾追加",
														 "散弾追加",
														 "榴弾追加",
														 "拡散弾追加",
														 "毒瓶追加",
														 "麻痺瓶追加",
														 "睡眠瓶追加",
														 "強撃瓶追加",
														 "属強瓶追加",
														 "接撃瓶追加",
														 "滅気瓶追加",
														 "爆破瓶追加",
														 "速射",
														 "射法",
														 "装填数",
														 "変則射撃",
														 "弾薬節約",
														 "達人",
														 "痛撃",
														 "連撃",
														 "特殊会心",
														 "属性会心",
														 "会心強化",
														 "溜め短縮",
														 "スタミナ",
														 "体術",
														 "気力回復",
														 "回避性能",
														 "回避距離",
														 "泡沫",
														 "ガード性能",
														 "ガード強化",
														 "KO",
														 "滅気攻撃",
														 "笛",
														 "砲術",
														 "重撃",
														 "爆弾強化",
														 "本気",
														 "闘魂",
														 "無傷",
														 "チャンス",
														 "底力",
														 "逆境",
														 "逆上",
														 "窮地",
														 "根性",
														 "気配",
														 "采配",
														 "号令",
														 "乗り",
														 "跳躍",
														 "無心",
														 "千里眼",
														 "観察眼",
														 "狩人",
														 "運搬",
														 "加護",
														 "英雄の盾",
														 "回復量",
														 "回復速度",
														 "効果持続",
														 "広域",
														 "腹減り",
														 "食いしん坊",
														 "食事",
														 "節食",
														 "肉食",
														 "茸食",
														 "野草知識",
														 "調合成功率",
														 "調合数",
														 "高速設置",
														 "採取",
														 "ハチミツ",
														 "護石王",
														 "気まぐれ",
														 "運気",
														 "剥ぎ取り",
														 "捕獲",
														 "ベルナ",
														 "ココット",
														 "ポッケ",
														 "ユクモ",
														 "紅兜",
														 "大雪主",
														 "矛砕",
														 "岩穿",
														 "紫毒姫",
														 "宝纏",
														 "白疾風",
														 "隻眼",
														 "黒炎王",
														 "金雷公",
														 "荒鉤爪",
														 "燼滅刃",
														 "北辰納豆流",
														 "胴系統倍加"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x8386D88, choice);
	}

	//護石第一スキルポイント変更
	void gosekiskill1p(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("第一スキルポイントを入力してください\n+127~-128ポイントまで指定できます。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386D8A, a);
	}

	//護石第二スキル変更
	void gosekiskill2(MenuEntry *entry)
	{
		Keyboard keyboard("第二スキルを選んでください", {"スキル無し",
														 "毒",
														 "麻痺",
														 "睡眠",
														 "気絶",
														 "聴覚保護",
														 "風圧",
														 "耐震",
														 "だるま",
														 "耐暑",
														 "耐寒",
														 "寒冷適応",
														 "炎熱適応",
														 "盗み無効",
														 "対防御DOWN",
														 "狂撃耐性",
														 "細菌学",
														 "裂傷",
														 "攻撃",
														 "防御",
														 "体力",
														 "火耐性",
														 "水耐性",
														 "雷耐性",
														 "氷耐性",
														 "龍耐性",
														 "属性耐性",
														 "火属性攻撃",
														 "水属性攻撃",
														 "雷属性攻撃",
														 "氷属性攻撃",
														 "龍属性攻撃",
														 "属性攻撃",
														 "特殊攻撃",
														 "研ぎ師",
														 "匠",
														 "斬れ味",
														 "剣術",
														 "研磨術",
														 "鈍器",
														 "抜刀会心",
														 "抜刀滅気",
														 "納刀",
														 "装填速度",
														 "反動",
														 "精密射撃",
														 "通常弾強化",
														 "貫通弾強化",
														 "散弾強化",
														 "重撃弾強化",
														 "通常弾追加",
														 "貫通弾追加",
														 "散弾追加",
														 "榴弾追加",
														 "拡散弾追加",
														 "毒瓶追加",
														 "麻痺瓶追加",
														 "睡眠瓶追加",
														 "強撃瓶追加",
														 "属強瓶追加",
														 "接撃瓶追加",
														 "滅気瓶追加",
														 "爆破瓶追加",
														 "速射",
														 "射法",
														 "装填数",
														 "変則射撃",
														 "弾薬節約",
														 "達人",
														 "痛撃",
														 "連撃",
														 "特殊会心",
														 "属性会心",
														 "会心強化",
														 "溜め短縮",
														 "スタミナ",
														 "体術",
														 "気力回復",
														 "回避性能",
														 "回避距離",
														 "泡沫",
														 "ガード性能",
														 "ガード強化",
														 "KO",
														 "滅気攻撃",
														 "笛",
														 "砲術",
														 "重撃",
														 "爆弾強化",
														 "本気",
														 "闘魂",
														 "無傷",
														 "チャンス",
														 "底力",
														 "逆境",
														 "逆上",
														 "窮地",
														 "根性",
														 "気配",
														 "采配",
														 "号令",
														 "乗り",
														 "跳躍",
														 "無心",
														 "千里眼",
														 "観察眼",
														 "狩人",
														 "運搬",
														 "加護",
														 "英雄の盾",
														 "回復量",
														 "回復速度",
														 "効果持続",
														 "広域",
														 "腹減り",
														 "食いしん坊",
														 "食事",
														 "節食",
														 "肉食",
														 "茸食",
														 "野草知識",
														 "調合成功率",
														 "調合数",
														 "高速設置",
														 "採取",
														 "ハチミツ",
														 "護石王",
														 "気まぐれ",
														 "運気",
														 "剥ぎ取り",
														 "捕獲",
														 "ベルナ",
														 "ココット",
														 "ポッケ",
														 "ユクモ",
														 "紅兜",
														 "大雪主",
														 "矛砕",
														 "岩穿",
														 "紫毒姫",
														 "宝纏",
														 "白疾風",
														 "隻眼",
														 "黒炎王",
														 "金雷公",
														 "荒鉤爪",
														 "燼滅刃",
														 "北辰納豆流",
														 "胴系統倍加"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x8386D89, choice);
	}

	//護石第二スキルポイント変更
	void gosekiskill2p(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("第二スキルポイントを入力してください\n+127~-128ポイントまで指定できます。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386D8B, a);
	}

	//護石スロット数変更
	void gosekislot(MenuEntry *entry)
	{
		Keyboard keyboard("スロット数を選んでください", {"0スロット",
														 "1スロット",
														 "2スロット",
														 "3スロット"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x8386D8C, choice);
	}

	//クイックメニュー
	/*	struct Quick{
			const char *name;
			const u8 id;
		};
		static const std::vector<Quick> g_quicks ={
			{"HP無限", 1},
			{"スタミナ無限", 2},
			{"無敵", 3},
			{"スーパーアーマー", 4},
			{"アイテム&弾丸無限", 5},
			{"斬れ味無限", 6},
		};
		void	Quickmenu(MenuEntry *entry){
			static StringVector quicks;
			static u8 on
			if( entry->Hotkeys[0].IsDown()){
				if (quicks.empty())
				for (const Quick &i : g_quicks)
				quicks.push_back(i.name);
				Keyboard keyboard("オンにしたいチートを選択してください", quicks);
				int choice = keyboard.Open();
				if (choice >= 0)
				on = g_quicks[choice].id;
			}
			if (on == 1){
				Process::Write32(0x046C37C, 0xE1D025F4);
				Process::Write32(0x046C398, 0xE1C025B2);
			}
			if (on == 2){
				Process::Write32(0x0A87104, 0xE3A00001);
			}
			if (on == 3){
				Process::Write32(0x0A2E3D0, 0xE3A00000);
			}
			if (on == 4){
				Process::Write32(0x0322C60, 0xE3A05001);
				Process::Write32(0x03322F0, 0xE3A00001);
			}
			if (on == 5){
				Process::Write32(0x035C658, 0xE3A07000);
			}
			if (on == 6){
				Process::Write32(0x035B270, 0xE5901218);
			}
		}*/

	//チャット無限
	void Chatmugen(MenuEntry *entry)
	{
		Process::Write8(0xDD4CA0, 0x0);
	}

	//装備コピー
	void soubicopy(MenuEntry *entry)
	{
		u32 a, b, c, d, e, f, g, h, i, j, k, l;
		u32 online;
		Process::Read32(0x80913EC, online);
		Keyboard keyboard("装備をコピーしたいプレイヤーを選んで下さい", {"P1", "P2", "P3", "P4"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			if (online == 0x100)
			{
				Process::Read32(0x831C9E4, a);
				Process::Read32(0x831CA14, b);
				Process::Read32(0x831CA44, c);
				Process::Read32(0x831CA74, d);
				Process::Read32(0x831CAA4, e);
				Process::Read32(0x831CAD4, f);
				Process::Read32(0x831CB04, g);
				Process::Read32(0x831CB08, h);
				Process::Read32(0x831CB0C, i);
				Process::Read32(0x831CB10, j);
				Process::Read32(0x831CB14, k);
				Process::Read32(0x831CB18, l);
				Process::Write32(0x8386C58, a);
				Process::Write32(0x8386C88, b);
				Process::Write32(0x8386CB8, c);
				Process::Write32(0x8386CE8, d);
				Process::Write32(0x8386D18, e);
				Process::Write32(0x8386D48, f);
				Process::Write32(0x8386D78, g);
				Process::Write32(0x8386D7C, h);
				Process::Write32(0x8386D80, i);
				Process::Write32(0x8386D84, j);
				Process::Write32(0x8386D88, k);
				Process::Write32(0x8386D8C, l);
			}
			else
				MessageBox("オフラインではコピーできません")();
		}
		if (choice == 1)
		{
			if (online == 0x100)
			{
				Process::Read32(0x831CE78, a);
				Process::Read32(0x831CEA8, b);
				Process::Read32(0x831CED8, c);
				Process::Read32(0x831CF08, d);
				Process::Read32(0x831CF38, e);
				Process::Read32(0x831CF68, f);
				Process::Read32(0x831CF98, g);
				Process::Read32(0x831CF9C, h);
				Process::Read32(0x831CFA0, i);
				Process::Read32(0x831CFA4, j);
				Process::Read32(0x831CFA8, k);
				Process::Read32(0x831CFAC, l);
				Process::Write32(0x8386C58, a);
				Process::Write32(0x8386C88, b);
				Process::Write32(0x8386CB8, c);
				Process::Write32(0x8386CE8, d);
				Process::Write32(0x8386D18, e);
				Process::Write32(0x8386D48, f);
				Process::Write32(0x8386D78, g);
				Process::Write32(0x8386D7C, h);
				Process::Write32(0x8386D80, i);
				Process::Write32(0x8386D84, j);
				Process::Write32(0x8386D88, k);
				Process::Write32(0x8386D8C, l);
			}
			else
				MessageBox("オフラインではコピーできません")();
		}
		if (choice == 2)
		{
			if (online == 0x100)
			{
				Process::Read32(0x831D30C, a);
				Process::Read32(0x831D33C, b);
				Process::Read32(0x831D36C, c);
				Process::Read32(0x831D39C, d);
				Process::Read32(0x831D3CC, e);
				Process::Read32(0x831D3FC, f);
				Process::Read32(0x831D42C, g);
				Process::Read32(0x831D430, h);
				Process::Read32(0x831D434, i);
				Process::Read32(0x831D438, j);
				Process::Read32(0x831D43C, k);
				Process::Read32(0x831D440, l);
				Process::Write32(0x8386C58, a);
				Process::Write32(0x8386C88, b);
				Process::Write32(0x8386CB8, c);
				Process::Write32(0x8386CE8, d);
				Process::Write32(0x8386D18, e);
				Process::Write32(0x8386D48, f);
				Process::Write32(0x8386D78, g);
				Process::Write32(0x8386D7C, h);
				Process::Write32(0x8386D80, i);
				Process::Write32(0x8386D84, j);
				Process::Write32(0x8386D88, k);
				Process::Write32(0x8386D8C, l);
			}
			else
				MessageBox("オフラインではコピーできません")();
		}
		if (choice == 3)
		{
			if (online == 0x100)
			{
				Process::Read32(0x831D7A0, a);
				Process::Read32(0x831D7D0, b);
				Process::Read32(0x831D800, c);
				Process::Read32(0x831D830, d);
				Process::Read32(0x831D860, e);
				Process::Read32(0x831D890, f);
				Process::Read32(0x831D8C0, g);
				Process::Read32(0x831D8C4, h);
				Process::Read32(0x831D8C8, i);
				Process::Read32(0x831D8CC, j);
				Process::Read32(0x831D8D0, k);
				Process::Read32(0x831D8D4, l);
				Process::Write32(0x8386C58, a);
				Process::Write32(0x8386C88, b);
				Process::Write32(0x8386CB8, c);
				Process::Write32(0x8386CE8, d);
				Process::Write32(0x8386D18, e);
				Process::Write32(0x8386D48, f);
				Process::Write32(0x8386D78, g);
				Process::Write32(0x8386D7C, h);
				Process::Write32(0x8386D80, i);
				Process::Write32(0x8386D84, j);
				Process::Write32(0x8386D88, k);
				Process::Write32(0x8386D8C, l);
			}
			else
				MessageBox("オフラインではコピーできません")();
		}
	}

	//プレイヤー座標移動
	void zahyo(MenuEntry *entry)
	{
		float x, z;
		Process::Read32(0x8195350, offset);
		Process::ReadFloat(offset + 0x40, x);
		Process::ReadFloat(offset + 0x48, z);

		if (Controller::IsKeysDown(A + DU))
		{
			z -= 50.0;
			Process::WriteFloat(offset + 0x48, z);
		}
		if (Controller::IsKeysDown(A + DD))
		{
			z += 50.0;
			Process::WriteFloat(offset + 0x48, z);
		}
		if (Controller::IsKeysDown(A + DL))
		{
			x -= 50.0;
			Process::WriteFloat(offset + 0x40, x);
		}
		if (Controller::IsKeysDown(A + DR))
		{
			x += 50.0;
			Process::WriteFloat(offset + 0x40, x);
		}
	}

	//ムーンジャンプ
	void moonjump(MenuEntry *entry)
	{
		float y;
		Process::Read32(0x8195350, offset);
		Process::ReadFloat(offset + 0x44, y);

		if (Controller::IsKeysDown(R + B))
		{
			y += 50.0;
			Process::WriteFloat(offset + 0x44, y);
		}
	}

	//他プレイヤーストーカー
	void stalker(MenuEntry *entry)
	{
		u16 on;
		u32 player, p1, p2, p3, p4, p1x, p2x, p3x, p4x, p1y, p2y, p3y, p4y, p1z, p2z, p3z, p4z;
		static u8 playeriti;
		static bool pston1 = false;
		static bool pston2 = false;
		static bool pston3 = false;
		Process::Read32(0x8195350, player);
		Process::Read16(0x80913EC, on);
		Process::Read32(0x831B284, p1);
		Process::Read32(0x831B288, p2);
		Process::Read32(0x831B28C, p3);
		Process::Read32(0x831B290, p4);
		Process::Read32(p1 + 0x40, p1x);
		Process::Read32(p1 + 0x44, p1y);
		Process::Read32(p1 + 0x48, p1z);
		Process::Read32(p2 + 0x40, p2x);
		Process::Read32(p2 + 0x44, p2y);
		Process::Read32(p2 + 0x48, p2z);
		Process::Read32(p3 + 0x40, p3x);
		Process::Read32(p3 + 0x44, p3y);
		Process::Read32(p3 + 0x48, p3z);
		Process::Read32(p4 + 0x40, p4x);
		Process::Read32(p4 + 0x44, p4y);
		Process::Read32(p4 + 0x48, p4z);
		Process::Read8(0x831B1C8, playeriti);
		if (on == 0x100)
		{
			if (Controller::IsKeysPressed(R + DU))
			{
				pston1 = true;
				pston2 = false;
				pston3 = false;
				OSD::Notify("StalkerP1:" << Color::Green << "ON!");
			}
			if (Controller::IsKeysPressed(R + DR))
			{
				pston2 = true;
				pston1 = false;
				pston3 = false;
				OSD::Notify("StalkerP2:" << Color::Green << "ON!");
			}
			if (Controller::IsKeysPressed(R + DD))
			{
				pston3 = true;
				pston1 = false;
				pston2 = false;
				OSD::Notify("StalkerP3:" << Color::Green << "ON!");
			}
			if (Controller::IsKeysPressed(R + DL))
			{
				pston1 = false;
				pston2 = false;
				pston3 = false;
				OSD::Notify("Stalker:" << Color::Red << "OFF!");
			}

			if (playeriti == 0x0)
			{
				if (pston1 == true && p2 != 0x0)
				{
					Process::Write32(player + 0x40, p2x);
					Process::Write32(player + 0x44, p2y);
					Process::Write32(player + 0x48, p2z);
				}
				if (pston2 == true && p3 != 0x0)
				{
					Process::Write32(player + 0x40, p3x);
					Process::Write32(player + 0x44, p3y);
					Process::Write32(player + 0x48, p3z);
				}
				if (pston3 == true && p4 != 0x0)
				{
					Process::Write32(player + 0x40, p4x);
					Process::Write32(player + 0x44, p4y);
					Process::Write32(player + 0x48, p4z);
				}
			}
			if (playeriti == 0x1)
			{
				if (pston1 == true && p1 != 0x0)
				{
					Process::Write32(player + 0x40, p1x);
					Process::Write32(player + 0x44, p1y);
					Process::Write32(player + 0x48, p1z);
				}
				if (pston2 == true && p3 != 0x0)
				{
					Process::Write32(player + 0x40, p3x);
					Process::Write32(player + 0x44, p3y);
					Process::Write32(player + 0x48, p3z);
				}
				if (pston3 == true && p4 != 0x0)
				{
					Process::Write32(player + 0x40, p4x);
					Process::Write32(player + 0x44, p4y);
					Process::Write32(player + 0x48, p4z);
				}
			}
			if (playeriti == 0x2)
			{
				if (pston1 == true && p1 != 0x0)
				{
					Process::Write32(player + 0x40, p1x);
					Process::Write32(player + 0x44, p1y);
					Process::Write32(player + 0x48, p1z);
				}
				if (pston2 == true && p2 != 0x0)
				{
					Process::Write32(player + 0x40, p2x);
					Process::Write32(player + 0x44, p2y);
					Process::Write32(player + 0x48, p2z);
				}
				if (pston3 == true && p4 != 0x0)
				{
					Process::Write32(player + 0x40, p4x);
					Process::Write32(player + 0x44, p4y);
					Process::Write32(player + 0x48, p4z);
				}
			}
			if (playeriti == 0x3)
			{
				if (pston1 == true && p1 != 0x0)
				{
					Process::Write32(player + 0x40, p1x);
					Process::Write32(player + 0x44, p1y);
					Process::Write32(player + 0x48, p1z);
				}
				if (pston2 == true && p2 != 0x0)
				{
					Process::Write32(player + 0x40, p2x);
					Process::Write32(player + 0x44, p2y);
					Process::Write32(player + 0x48, p2z);
				}
				if (pston3 == true && p3 != 0x0)
				{
					Process::Write32(player + 0x40, p3x);
					Process::Write32(player + 0x44, p3y);
					Process::Write32(player + 0x48, p3z);
				}
			}
		}
	}

	//モンスター座標移動
	void monzahyo(MenuEntry *entry)
	{
		float mon1x, mon1z, mon2x, mon2z;
		u32 offset1, offset2;
		u8 erea1, erea2;
		Process::Read32(0x8325244, offset1);
		Process::Read32(0x8325248, offset2);
		Process::ReadFloat(offset1 + 0xFF8, mon1x);
		Process::ReadFloat(offset1 + 0x1000, mon1z);
		Process::ReadFloat(offset2 + 0xFF8, mon2x);
		Process::ReadFloat(offset2 + 0x1000, mon2z);
		Process::Read8(offset1 + 0xD, erea1);
		Process::Read8(offset2 + 0xD, erea2);

		if (Controller::IsKeysDown(X))
		{
			if (erea1 == 0x4C)
			{
				if (Controller::IsKeysDown(DU))
				{
					mon1z = mon1z - 50.0;
					Process::WriteFloat(offset1 + 0x1000, mon1z);
				}
				if (Controller::IsKeysDown(DD))
				{
					mon1z = mon1z + 50.0;
					Process::WriteFloat(offset1 + 0x1000, mon1z);
				}
				if (Controller::IsKeysDown(DL))
				{
					mon1x = mon1x - 50.0;
					Process::WriteFloat(offset1 + 0xFF8, mon1x);
				}
				if (Controller::IsKeysDown(DR))
				{
					mon1x = mon1x + 50.0;
					Process::WriteFloat(offset1 + 0xFF8, mon1x);
				}
			}
			if (erea2 == 0x4C)
			{
				if (Controller::IsKeysDown(CU))
				{
					mon2z = mon2z - 50.0;
					Process::WriteFloat(offset2 + 0x1000, mon2z);
				}
				if (Controller::IsKeysDown(CD))
				{
					mon2z = mon2z + 50.0;
					Process::WriteFloat(offset2 + 0x1000, mon2z);
				}
				if (Controller::IsKeysDown(CL))
				{
					mon2x = mon2x - 50.0;
					Process::WriteFloat(offset2 + 0xFF8, mon2x);
				}
				if (Controller::IsKeysDown(CR))
				{
					mon2x = mon2x + 50.0;
					Process::WriteFloat(offset2 + 0xFF8, mon2x);
				}
			}
		}
	}

	//モンスターストーカー
	void monstalker(MenuEntry *entry)
	{
		u32 player, mon1, mon2;
		u32 playerx, playerz, mon1x, mon1z, mon2x, mon2z;
		u8 erea1, erea2;
		static bool ston1 = false;
		static bool ston2 = false;
		Process::Read32(0x8195350, player);
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Process::Read32(player + 0x40, playerx);
		Process::Read32(player + 0x48, playerz);
		Process::Read32(mon1 + 0xFF8, mon1x);
		Process::Read32(mon1 + 0x1000, mon1z);
		Process::Read32(mon2 + 0xFF8, mon2x);
		Process::Read32(mon2 + 0x1000, mon2z);
		Process::Read8(mon1 + 0xD, erea1);
		Process::Read8(mon2 + 0xD, erea2);
		if (Controller::IsKeysPressed(X + DU + R))
		{
			ston1 = true;
			ston2 = false;
			OSD::Notify("Mon1Stalker:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(X + DU + L))
		{
			ston1 = false;
			ston2 = true;
			OSD::Notify("Mon2Stalker:" << Color::Green << "ON!");
		}
		if (Controller::IsKeysPressed(X + DD + R))
		{
			ston1 = false;
			ston2 = false;
			OSD::Notify("MonStalker:" << Color::Red << "OFF!");
		}
		if (ston1 == true)
		{
			if (erea1 == 0x4C)
			{
				Process::Write32(player + 0x40, mon1x);
				Process::Write32(player + 0x48, mon1z);
			}
		}
		if (ston2 == true)
		{
			if (erea2 == 0x4C)
			{
				Process::Write32(player + 0x40, mon2x);
				Process::Write32(player + 0x48, mon2z);
			}
		}
	}

	//1番目のモンスターHP表示
	void monhp1(MenuEntry *entry)
	{
		static u16 mon1hpmax, mon1hp;
		static int adrs_on = 0;
		adrs_on = true;
		Process::Read32(0x8325244, offset);
		Process::Read16(offset + 0x1318, mon1hp);
		Process::Read16(offset + 0x131C, mon1hpmax);

		if (offset != 0)
		{
			adrs_on = true;
			OSD::Run([](const Screen &screen) {
				if (!screen.IsTop)
					return (false);
				if (adrs_on == true)
				{
					if (mon1hp == 0)
					{ //0%
						screen.Draw(Utils::Format("Mon1HP %u", mon1hp), 10, 100, Color::Gray);
						adrs_on = false;
					}
					else if (mon1hp * 5 < mon1hpmax)
					{ //20%
						screen.Draw(Utils::Format("Mon1HP %u", mon1hp), 10, 100, Color::Red);
						adrs_on = false;
					}
					else if (mon1hp * 2 < mon1hpmax)
					{ //50%
						screen.Draw(Utils::Format("Mon1HP %u", mon1hp), 10, 100, Color::Orange);
						adrs_on = false;
					}
					else
					{
						screen.Draw(Utils::Format("Mon1HP %u", mon1hp), 10, 100, Color::Green);
						adrs_on = false;
					}
				}
				return (true);
			});
		}
		else
			adrs_on = false;
	}

	//2番目のモンスターHP表示
	void monhp2(MenuEntry *entry)
	{
		static u16 mon2hpmax, mon2hp;
		static int adrs_on = 0;
		Process::Read32(0x8325248, offset);
		Process::Read16(offset + 0x1318, mon2hp);
		Process::Read16(offset + 0x131C, mon2hpmax);
		if (offset != 0)
		{
			adrs_on = true;
			OSD::Run([](const Screen &screen) {
				if (!screen.IsTop)
					return (false);
				if (adrs_on == true)
				{
					if (mon2hp == 0)
					{ //0
						screen.Draw(Utils::Format("Mon2HP %u", mon2hp), 10, 110, Color::Gray);
						adrs_on = false;
					}
					else if (mon2hp * 5 < mon2hpmax)
					{ //20%
						screen.Draw(Utils::Format("Mon2HP %u", mon2hp), 10, 110, Color::Red);
						adrs_on = false;
					}
					else if (mon2hp * 2 < mon2hpmax)
					{ //50%
						screen.Draw(Utils::Format("Mon2HP %u", mon2hp), 10, 110, Color::Orange);
						adrs_on = false;
					}
					else
					{
						screen.Draw(Utils::Format("Mon2HP %u", mon2hp), 10, 110, Color::Green);
						adrs_on = false;
					}
				}
				return (true);
			});
		}
		else
			adrs_on = false;
	}

	//プレイヤーの現在座標表示
	void nowplayerzahyou(MenuEntry *entry)
	{
		static float x, y, z;
		static int adrs_on = 0;
		adrs_on = true;
		Process::Read32(0x8195350, offset);
		Process::ReadFloat(offset + 0x40, x);
		Process::ReadFloat(offset + 0x44, y);
		Process::ReadFloat(offset + 0x48, z);
		OSD::Run([](const Screen &screen) {
			if (!screen.IsTop)
				return (false);
			if (adrs_on == true)
			{
				screen.Draw(Utils::Format("Player X=%.f Y=%.f Z=%.f", x, y, z), 10, 50, Color::Yellow);
				adrs_on = false;
			}
			return (true);
		});
	}

	//リージョン変更
	void Regionchange(MenuEntry *entry)
	{
		Keyboard keyboard("リージョンを選択してください。", {"日本",
															 "ヨーロッパ"});
		int result = keyboard.Open();
		if (result == 0)
			Process::Write32(0x389BC4, 0xE3A01000);
		if (result == 1)
			Process::Write32(0x389BC4, 0xE3A01001);
	}

	//リピートムーブ
	void Repeatmove(MenuEntry *entry)
	{
		Process::Read32(0x8195350, offset);
		if (Controller::IsKeysDown(B + Y))
			Process::Write32(offset + 0x5, 0x0);
	}

	//特殊チケット変更
	void tokusyuticket(MenuEntry *entry)
	{
		Keyboard keyboard("変更したいチケットを選んでください。", {"紅兜アオアシラ",
																   "大雪主ウルクスス",
																   "矛砕ダイミョウザザミ",
																   "紫毒姫リオレイア",
																   "岩穿テツカブラ",
																   "白疾風ナルガクルガ",
																   "宝纏ウラガンキン",
																   "隻眼イャンガルルガ",
																   "黒炎王リオレウス",
																   "金雷公ジンオウガ",
																   "荒鉤爪ティガレックス",
																   "燼滅刃ディノバルド"});
		int result = keyboard.Open();
		static u8 ticket;
		if (result == 0)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B3835, ticket);
		}
		if (result == 1)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B3836, ticket);
		}
		if (result == 2)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B3837, ticket);
		}
		if (result == 3)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B3838, ticket);
		}
		if (result == 4)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B3839, ticket);
		}
		if (result == 5)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B383A, ticket);
		}
		if (result == 6)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B383B, ticket);
		}
		if (result == 7)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B383C, ticket);
		}
		if (result == 8)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B383D, ticket);
		}
		if (result == 9)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B383E, ticket);
		}
		if (result == 10)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B383F, ticket);
		}
		if (result == 11)
		{
			Keyboard keyboard("何枚に変えますか?");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(ticket) != -1)
				Process::Write8(0x83B3840, ticket);
		}
	}

	static u32 quest;
	//クエストクリア失敗変更
	void questclearchange(MenuEntry *entry)
	{
		Keyboard keyboard("クエストクリアか失敗かを選んでください。", {"クエストクリア",
																	"クエスト失敗"});
		int choice = keyboard.Open();
		if (choice == 0)
			quest = 0x29;
		if (choice == 1)
			quest = 0xC9;
	}
	//クエストクリア失敗固定
	void questclear(MenuEntry *entry)
	{
		Process::Write32(0x8363F94, quest);
		Process::Write32(0x8363FA0, quest);
	}

	//クエスト後即リザルト
	void questresult(MenuEntry *entry)
	{
		Process::Read32(0x83ACA40, offset);
		Process::Write32(offset + 0x104, 0);
	}

	//報酬画面スキップ
	void questwait(MenuEntry *entry)
	{
		Process::Read32(0x819DF68, offset);
		Process::Write32(offset + 0xAC, 0);
	}

	//たんほれアイテム
	void tanhoreitem(MenuEntry *entry)
	{
		Process::Write16(0x8372392, 0x0527); //燃石炭
		Process::Write8(0x8372394, 0x63);
		Process::Write16(0x8372396, 0x0455); //ネコタクチケット
		Process::Write8(0x8372398, 0x63);
		Process::Write16(0x837239A, 0x004C); //モドリ玉
		Process::Write8(0x837239C, 0x63);
	}

	//爆弾無限設置
	void infbakudan(MenuEntry *entry)
	{
		Process::Write32(0x83AC5F0, 0x00000003);
	}

	//視野角変更設定
	static float fov = 50.f;
	void fovchange(MenuEntry *entry)
	{
		Keyboard keyboard("どちらにしますか？", {"デフォルト",
												 "視野角変更"});
		int result = keyboard.Open();
		if (result == 0)
			fov = 50.f;
		if (result == 1)
		{
			Keyboard keyboard(Utils::Format("視野角を指定してください。\n現在の視野角[%f]", fov));
			if (keyboard.Open(fov) != -1)
				;
		}
	}

	//視野角変更
	void fovkotei(MenuEntry *entry)
	{
		Process::Read32(0x81943DC, offset);
		Process::WriteFloat(offset + 0x740, fov);
	}

	//村貢献度
	void murakoukendo(MenuEntry *entry)
	{
		u32 koukendo;
		Keyboard keyboard("貢献度を変更したい村を選んでください。", {"ベルナ村",
																	 "ココット村",
																	 "ポッケ村",
																	 "ユクモ村"});
		int result = keyboard.Open();
		if (result == 0)
		{
			Keyboard keyboard("貢献度を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(koukendo) != -1)
				Process::Write32(0x83B3824, koukendo);
		}
		if (result == 1)
		{
			Keyboard keyboard("貢献度を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(koukendo) != -1)
				Process::Write32(0x83B3828, koukendo);
		}
		if (result == 2)
		{
			Keyboard keyboard("貢献度を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(koukendo) != -1)
				Process::Write32(0x83B382C, koukendo);
		}
		if (result == 3)
		{
			Keyboard keyboard("貢献度を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(koukendo) != -1)
				Process::Write32(0x83B3830, koukendo);
		}
	}

	//ルームサービス変更
	void rumusabisuchange(MenuEntry *entry)
	{
		Keyboard keyboard("どのルームサービスに変更しますか？", {"ルームサービス",
																 "キャラバンの看板娘",
																 "モガの村の看板娘",
																 "タンジアの港の看板娘",
																 "ぽかぽか島の管理人"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x83B36D0, choice);
	}

	//ギルドカード変更
	void guildcardchange(MenuEntry *entry)
	{
		u16 syogo1, syogo2, syogo3, kaisu;
		float yuko;
		Keyboard keyboard("グループを選択してください。", {"称号",
														   "クリア回数",
														   "すれ違い回数",
														   "友好度",
														   "背景",
														   "ポーズ",
														   "武器使用回数",
														   "プレイ時間",
														   "モンスター狩猟記録"});
		int result = keyboard.Open();
		if (result == 0)
		{
			Keyboard keyboard("下画面の説明文に変更する称号を選んでください。", {"称号1",
																				 "称号2",
																				 "称号3"});
			int syogo = keyboard.Open();
			if (syogo == 0)
			{
				Process::Read16(0x8436978, syogo1);
				syogo1 = syogo1 + 0x3D4;
				Process::Write16(0x8436978, syogo1);
			}
			if (syogo == 1)
				Process::Write16(0x843697A, 0x65);
			if (syogo == 2)
			{
				Process::Read16(0x843697C, syogo3);
				syogo3 = syogo3 + 0x3D4;
				Process::Write16(0x843697C, syogo3);
			}
		}
		if (result == 1)
		{
			Keyboard keyboard("変更するクリア回数を選んでください。", {"村",
																	   "集会所下位",
																	   "集会所上位",
																	   "特殊許可クエスト",
																	   "闘技大会"});
			int clear = keyboard.Open();
			if (clear == 0)
			{
				Keyboard keyboard("クリア回数を入力してください。");
				keyboard.IsHexadecimal(false);
				int clear = keyboard.Open(kaisu);
				if (clear >= 0)
					Process::Write16(0x843697E, kaisu);
			}
			if (clear == 1)
			{
				Keyboard keyboard("クリア回数を入力してください。");
				keyboard.IsHexadecimal(false);
				int clear = keyboard.Open(kaisu);
				if (clear >= 0)
					Process::Write16(0x8436980, kaisu);
			}
			if (clear == 2)
			{
				Keyboard keyboard("クリア回数を入力してください。");
				keyboard.IsHexadecimal(false);
				int clear = keyboard.Open(kaisu);
				if (clear >= 0)
					Process::Write16(0x8436982, kaisu);
			}
			if (clear == 3)
			{
				Keyboard keyboard("クリア回数を入力してください。");
				keyboard.IsHexadecimal(false);
				int clear = keyboard.Open(kaisu);
				if (clear >= 0)
					Process::Write16(0x8436984, kaisu);
			}
			if (clear == 4)
			{
				Keyboard keyboard("クリア回数を入力してください。");
				keyboard.IsHexadecimal(false);
				int clear = keyboard.Open(kaisu);
				if (clear >= 0)
					Process::Write16(0x8436986, kaisu);
			}
		}
		if (result == 2)
		{
			Keyboard keyboard("すれ違い回数を入力してください。");
			keyboard.IsHexadecimal(false);
			int sure = keyboard.Open(kaisu);
			if (sure >= 0)
				Process::Write16(0x843698C, kaisu);
		}
		if (result == 3)
		{
			Keyboard keyboard("友好度を入力してください。");
			keyboard.IsHexadecimal(false);
			int yukodo = keyboard.Open(yuko);
			if (yukodo >= 0)
				Process::WriteFloat(0x8436988, yuko);
		}
		if (result == 4)
		{
			Keyboard keyboard("背景を透明にしますか？", {"はい",
														 "いいえ"});
			int choice = keyboard.Open();
			if (choice == 0)
				Process::Write8(0x84369CA, 0x5E);
		}
		if (result == 5)
		{
			Keyboard keyboard("ポーズをTポーズにしますか？", {"はい",
															  "いいえ"});
			int choice = keyboard.Open();
			if (choice == 0)
				Process::Write8(0x84369CB, 0x16);
		}
		if (result == 6)
		{
			Keyboard keyboard("グループを選んでください。", {"村",
															 "集会所",
															 "闘技大会",
															 "全てカンスト"});
			int gurupu = keyboard.Open();
			if (gurupu == 0)
			{
				Keyboard keyboard("武器種を選んでください。", {"大剣",
															   "太刀",
															   "片手剣",
															   "双剣",
															   "ハンマー",
															   "狩猟笛",
															   "ランス",
															   "ガンランス",
															   "スラッシュアックス",
															   "チャージアックス",
															   "操虫棍",
															   "ライトボウガン",
															   "ヘビィボウガン",
															   "弓",
															   "ニャンター"});
				int choice = keyboard.Open();
				if (choice == 0)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369D4, kaisu);
				}
				if (choice == 1)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369E0, kaisu);
				}
				if (choice == 2)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369D6, kaisu);
				}
				if (choice == 3)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369E8, kaisu);
				}
				if (choice == 4)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369D8, kaisu);
				}
				if (choice == 5)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369EA, kaisu);
				}
				if (choice == 6)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369DA, kaisu);
				}
				if (choice == 7)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369E4, kaisu);
				}
				if (choice == 8)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369E2, kaisu);
				}
				if (choice == 9)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369EE, kaisu);
				}
				if (choice == 10)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369EC, kaisu);
				}
				if (choice == 11)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369DE, kaisu);
				}
				if (choice == 12)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369DC, kaisu);
				}
				if (choice == 13)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369E6, kaisu);
				}
				if (choice == 14)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369F0, kaisu);
				}
			}
			if (gurupu == 1)
			{
				Keyboard keyboard("武器種を選んでください。", {"大剣",
															   "太刀",
															   "片手剣",
															   "双剣",
															   "ハンマー",
															   "狩猟笛",
															   "ランス",
															   "ガンランス",
															   "スラッシュアックス",
															   "チャージアックス",
															   "操虫棍",
															   "ライトボウガン",
															   "ヘビィボウガン",
															   "弓",
															   "ニャンター"});
				int choice = keyboard.Open();
				if (choice == 0)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369F2, kaisu);
				}
				if (choice == 1)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369FE, kaisu);
				}
				if (choice == 2)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369F4, kaisu);
				}
				if (choice == 3)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A06, kaisu);
				}
				if (choice == 4)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369F6, kaisu);
				}
				if (choice == 5)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A08, kaisu);
				}
				if (choice == 6)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369F8, kaisu);
				}
				if (choice == 7)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A02, kaisu);
				}
				if (choice == 8)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A00, kaisu);
				}
				if (choice == 9)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A0C, kaisu);
				}
				if (choice == 10)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A0A, kaisu);
				}
				if (choice == 11)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369FC, kaisu);
				}
				if (choice == 12)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x84369FA, kaisu);
				}
				if (choice == 13)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A04, kaisu);
				}
				if (choice == 14)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A0E, kaisu);
				}
			}
			if (gurupu == 2)
			{
				Keyboard keyboard("武器種を選んでください。", {"大剣",
															   "太刀",
															   "片手剣",
															   "双剣",
															   "ハンマー",
															   "狩猟笛",
															   "ランス",
															   "ガンランス",
															   "スラッシュアックス",
															   "チャージアックス",
															   "操虫棍",
															   "ライトボウガン",
															   "ヘビィボウガン",
															   "弓",
															   "ニャンター"});
				int choice = keyboard.Open();
				if (choice == 0)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A10, kaisu);
				}
				if (choice == 1)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A1C, kaisu);
				}
				if (choice == 2)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A12, kaisu);
				}
				if (choice == 3)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A24, kaisu);
				}
				if (choice == 4)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A14, kaisu);
				}
				if (choice == 5)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A26, kaisu);
				}
				if (choice == 6)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A16, kaisu);
				}
				if (choice == 7)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A20, kaisu);
				}
				if (choice == 8)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A1E, kaisu);
				}
				if (choice == 9)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A2A, kaisu);
				}
				if (choice == 10)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A28, kaisu);
				}
				if (choice == 11)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A1A, kaisu);
				}
				if (choice == 12)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A18, kaisu);
				}
				if (choice == 13)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A22, kaisu);
				}
				if (choice == 14)
				{
					Keyboard keyboard("武器使用回数を入力してください。");
					keyboard.IsHexadecimal(false);
					if (keyboard.Open(kaisu) != -1)
						Process::Write16(0x8436A2C, kaisu);
				}
			}
			if (gurupu == 3)
			{
				Keyboard keyboard("全ての武器使用回数を9999にしますか？", {"はい",
																		   "いいえ"});
				int choice = keyboard.Open();
				if (choice == 0)
					for (int i = 0; i < 45; i++)
						Process::Write16(i * 0x2 + 0x84369D4, 0x270F);
			}
		}
		if (result == 7)
		{
			u32 byo, hun, jikan, time;
			Keyboard byokey("プレイ時間(秒)を入力してください。");
			byokey.IsHexadecimal(false);
			if (byokey.Open(byo) != -1)
				;
			Keyboard hunkey("プレイ時間(分)を入力してください。");
			hunkey.IsHexadecimal(false);
			if (hunkey.Open(hun) != 1)
				;
			Keyboard jikey("プレイ時間(時)を入力してください。");
			jikey.IsHexadecimal(false);
			if (jikey.Open(jikan) != -1)
				;
			hun = hun * 60;
			jikan = jikan * 3600;
			time = byo + hun + jikan;
			Process::Write32(0x831B1CC, time);
		}
		if (result == 8)
		{
			Keyboard keyboard("グループを選んでください。", {"狩猟数",
															 "捕獲数",
															 "どちらもカンスト"});
			int choice = keyboard.Open();
			if (choice == 0)
			{
				Keyboard keyboard("ページを選んでください。\n(ギルドカードの並びです)", {"1ページ目",
																						 "2ページ目",
																						 "3ページ目",
																						 "4ページ目",
																						 "5ページ目",
																						 "6ページ目",
																						 "7ページ目",
																						 "8ページ目",
																						 "小型モンスター"});
				int syuryoup = keyboard.Open();
				if (syuryoup == 0)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ドスマッカォ",
																	   "ドスランポス",
																	   "ドスファンゴ",
																	   "アルセルタス",
																	   "アオアシラ",
																	   "紅兜アオアシラ",
																	   "ドスゲネポス",
																	   "ドスガレオス",
																	   "イャンクック"});
					int monp1 = keyboard.Open();
					if (monp1 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DF8, kaisu);
					}
					if (monp1 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D82, kaisu);
					}
					if (monp1 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DA0, kaisu);
					}
					if (monp1 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DE6, kaisu);
					}
					if (monp1 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DCA, kaisu);
					}
					if (monp1 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DCC, kaisu);
					}
					if (monp1 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D84, kaisu);
					}
					if (monp1 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D88, kaisu);
					}
					if (monp1 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D7A, kaisu);
					}
				}
				if (syuryoup == 1)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ドスイーオス",
																	   "ケチャワチャ",
																	   "ウルクスス",
																	   "大雪主ウルクスス",
																	   "ゲリョス",
																	   "テツカブラ",
																	   "岩穿テツカブラ",
																	   "ダイミョウザザミ",
																	   "矛砕ダイミョウザザミ"});
					int monp2 = keyboard.Open();
					if (monp2 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D86, kaisu);
					}
					if (monp2 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DD6, kaisu);
					}
					if (monp2 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DCE, kaisu);
					}
					if (monp2 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DD0, kaisu);
					}
					if (monp2 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D7C, kaisu);
					}
					if (monp2 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DD8, kaisu);
					}
					if (monp2 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DDA, kaisu);
					}
					if (monp2 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D8E, kaisu);
					}
					if (monp2 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D90, kaisu);
					}
				}
				if (syuryoup == 2)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ラングロトラ",
																	   "ロアルドロス",
																	   "ホロロホルル",
																	   "ザボアザギル",
																	   "フルフル",
																	   "リオレイア",
																	   "リオレイア希少種",
																	   "紫毒姫リオレイア",
																	   "ハプルボッカ"});
					int monp3 = keyboard.Open();
					if (monp3 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DD2, kaisu);
					}
					if (monp3 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DBA, kaisu);
					}
					if (monp3 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DEA, kaisu);
					}
					if (monp3 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DDC, kaisu);
					}
					if (monp3 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D78, kaisu);
					}
					if (monp3 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D6C, kaisu);
					}
					if (monp3 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D70, kaisu);
					}
					if (monp3 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D6E, kaisu);
					}
					if (monp3 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DC2, kaisu);
					}
				}
				if (syuryoup == 3)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ガノトトス",
																	   "ドドブランゴ",
																	   "ヴォルガノス",
																	   "ショウグンギザミ",
																	   "ガララアジャラ",
																	   "ナルガクルガ",
																	   "白疾風ナルガクルガ",
																	   "イャンガルルガ",
																	   "隻眼イャンガルルガ"});
					int monp4 = keyboard.Open();
					if (monp4 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D7E, kaisu);
					}
					if (monp4 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D94, kaisu);
					}
					if (monp4 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DA8, kaisu);
					}
					if (monp4 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D92, kaisu);
					}
					if (monp4 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DDE, kaisu);
					}
					if (monp4 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DAA, kaisu);
					}
					if (monp4 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DAC, kaisu);
					}
					if (monp4 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D8A, kaisu);
					}
					if (monp4 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D8C, kaisu);
					}
				}
				if (syuryoup == 4)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ウラガンキン",
																	   "宝纏ウラガンキン",
																	   "ゲネル・セルタス",
																	   "リオレウス",
																	   "リオレウス希少種",
																	   "黒炎王リオレウス",
																	   "ラギアクルス",
																	   "ジンオウガ",
																	   "金雷公ジンオウガ"});
					int monp5 = keyboard.Open();
					if (monp5 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DB4, kaisu);
					}
					if (monp5 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DB6, kaisu);
					}
					if (monp5 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DE0, kaisu);
					}
					if (monp5 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D72, kaisu);
					}
					if (monp5 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D74, kaisu);
					}
					if (monp5 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D76, kaisu);
					}
					if (monp5 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DB8, kaisu);
					}
					if (monp5 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DC4, kaisu);
					}
					if (monp5 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DC6, kaisu);
					}
				}
				if (syuryoup == 5)
				{
					Keyboard keyboard("モンスターを選んでください。", {"タマミツネ",
																	   "ライゼクス",
																	   "ガムート",
																	   "ディノバルド",
																	   "燼滅刃ディノバルド",
																	   "アグナコトル",
																	   "ゴア・マガラ",
																	   "セルレギオス",
																	   "ドボルベルク"});
					int monp6 = keyboard.Open();
					if (monp6 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DF2, kaisu);
					}
					if (monp6 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DF0, kaisu);
					}
					if (monp6 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DF4, kaisu);
					}
					if (monp6 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DEC, kaisu);
					}
					if (monp6 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DEE, kaisu);
					}
					if (monp6 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DBC, kaisu);
					}
					if (monp6 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DE2, kaisu);
					}
					if (monp6 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DE8, kaisu);
					}
					if (monp6 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DC0, kaisu);
					}
				}
				if (syuryoup == 6)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ティガレックス",
																	   "荒鉤爪ティガレックス",
																	   "キリン",
																	   "ブラキディオス",
																	   "シャガルマガラ",
																	   "ラージャン",
																	   "激昂したラージャン",
																	   "イビルジョー",
																	   "怒り喰らうイビルジョー",
																	   "クシャルダオラ",
																	   "オオナズチ"});
					int monp7 = keyboard.Open();
					if (monp7 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DA2, kaisu);
					}
					if (monp7 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DA4, kaisu);
					}
					if (monp7 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D80, kaisu);
					}
					if (monp7 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DD4, kaisu);
					}
					if (monp7 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DE4, kaisu);
					}
					if (monp7 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D96, kaisu);
					}
					if (monp7 == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D98, kaisu);
					}
					if (monp7 == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DB0, kaisu);
					}
					if (monp7 == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DB2, kaisu);
					}
					if (monp7 == 9)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D9A, kaisu);
					}
					if (monp7 == 10)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D9C, kaisu);
					}
				}
				if (syuryoup == 7)
				{
					Keyboard keyboard("モンスターを選んでください。", {"テオ・テスカトル",
																	   "アカムトルム",
																	   "ウカムルバス",
																	   "アマツマガツチ",
																	   "オストガロア",
																	   "アルバトリオン"});
					int monp8 = keyboard.Open();
					if (monp8 == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3D9E, kaisu);
					}
					if (monp8 == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DA6, kaisu);
					}
					if (monp8 == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DAE, kaisu);
					}
					if (monp8 == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DC8, kaisu);
					}
					if (monp8 == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DF6, kaisu);
					}
					if (monp8 == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DBE, kaisu);
					}
				}
				if (syuryoup == 8)
				{
					Keyboard keyboard("小型モンスターを選んでください。", {"アイルー",
																		   "メラルー",
																		   "カンタロス",
																		   "ランゴスタ",
																		   "ブナハブラ",
																		   "オルタロス",
																		   "クンチュウ",
																		   "ガレオス",
																		   "アプトノス",
																		   "アプケロス",
																		   "ケルビ",
																		   "モス",
																		   "ポポ",
																		   "ガウシカ",
																		   "リノプロス",
																		   "ズワロポス",
																		   "リモセトス",
																		   "ムーファ",
																		   "ガーグァ",
																		   "ジャギィ",
																		   "ジャギィノス",
																		   "ギアノス",
																		   "ランポス",
																		   "ゲネポス",
																		   "イーオス",
																		   "マッカォ",
																		   "ブルファンゴ",
																		   "ブランゴ",
																		   "スクアギル",
																		   "ヤオザミ",
																		   "ガミザミ",
																		   "ルドロス",
																		   "ウロコトル",
																		   "ガブラス"});
					keyboard.IsHexadecimal(false);
					int kogata = keyboard.Open();
					if (kogata == 0)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E06, kaisu);
					}
					if (kogata == 1)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E08, kaisu);
					}
					if (kogata == 2)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E04, kaisu);
					}
					if (kogata == 3)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E02, kaisu);
					}
					if (kogata == 4)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E24, kaisu);
					}
					if (kogata == 5)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E26, kaisu);
					}
					if (kogata == 6)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E36, kaisu);
					}
					if (kogata == 7)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E10, kaisu);
					}
					if (kogata == 8)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DFA, kaisu);
					}
					if (kogata == 9)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DFC, kaisu);
					}
					if (kogata == 10)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3DFE, kaisu);
					}
					if (kogata == 11)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E00, kaisu);
					}
					if (kogata == 12)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E14, kaisu);
					}
					if (kogata == 13)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E18, kaisu);
					}
					if (kogata == 14)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E22, kaisu);
					}
					if (kogata == 15)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E30, kaisu);
					}
					if (kogata == 16)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E3A, kaisu);
					}
					if (kogata == 17)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E3C, kaisu);
					}
					if (kogata == 18)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E32, kaisu);
					}
					if (kogata == 19)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E28, kaisu);
					}
					if (kogata == 20)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E2A, kaisu);
					}
					if (kogata == 21)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E16, kaisu);
					}
					if (kogata == 22)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E0A, kaisu);
					}
					if (kogata == 23)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E0C, kaisu);
					}
					if (kogata == 24)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E0E, kaisu);
					}
					if (kogata == 25)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E38, kaisu);
					}
					if (kogata == 26)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E12, kaisu);
					}
					if (kogata == 27)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E20, kaisu);
					}
					if (kogata == 28)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E34, kaisu);
					}
					if (kogata == 29)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E1C, kaisu);
					}
					if (kogata == 30)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E1E, kaisu);
					}
					if (kogata == 31)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E2C, kaisu);
					}
					if (kogata == 32)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E2E, kaisu);
					}
					if (kogata == 33)
					{
						Keyboard keyboard("討伐数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E1A, kaisu);
					}
				}
			}
			if (choice == 1)
			{
				Keyboard keyboard("ページを選んでください。\n(ギルドカードの並びです)", {"1ページ目",
																						 "2ページ目",
																						 "3ページ目",
																						 "4ページ目",
																						 "5ページ目",
																						 "6ページ目",
																						 "7ページ目",
																						 "8ページ目"});
				int hokakup = keyboard.Open();
				if (hokakup == 0)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ドスマッカォ",
																	   "ドスランポス",
																	   "ドスファンゴ",
																	   "アルセルタス",
																	   "アオアシラ",
																	   "紅兜アオアシラ",
																	   "ドスゲネポス",
																	   "ドスガレオス",
																	   "イャンクック"});
					int monp1 = keyboard.Open();
					if (monp1 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ED8, kaisu);
					}
					if (monp1 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E62, kaisu);
					}
					if (monp1 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E80, kaisu);
					}
					if (monp1 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EC6, kaisu);
					}
					if (monp1 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EAA, kaisu);
					}
					if (monp1 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EAC, kaisu);
					}
					if (monp1 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E64, kaisu);
					}
					if (monp1 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E68, kaisu);
					}
					if (monp1 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E5A, kaisu);
					}
				}
				if (hokakup == 1)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ドスイーオス",
																	   "ケチャワチャ",
																	   "ウルクスス",
																	   "大雪主ウルクスス",
																	   "ゲリョス",
																	   "テツカブラ",
																	   "岩穿テツカブラ",
																	   "ダイミョウザザミ",
																	   "矛砕ダイミョウザザミ"});
					int monp2 = keyboard.Open();
					if (monp2 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E66, kaisu);
					}
					if (monp2 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EB6, kaisu);
					}
					if (monp2 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EAE, kaisu);
					}
					if (monp2 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EB0, kaisu);
					}
					if (monp2 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E5C, kaisu);
					}
					if (monp2 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EB8, kaisu);
					}
					if (monp2 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EBA, kaisu);
					}
					if (monp2 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E6E, kaisu);
					}
					if (monp2 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E70, kaisu);
					}
				}
				if (hokakup == 2)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ラングロトラ",
																	   "ロアルドロス",
																	   "ホロロホルル",
																	   "ザボアザギル",
																	   "フルフル",
																	   "リオレイア",
																	   "リオレイア希少種",
																	   "紫毒姫リオレイア",
																	   "ハプルボッカ"});
					int monp3 = keyboard.Open();
					if (monp3 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EB2, kaisu);
					}
					if (monp3 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E9A, kaisu);
					}
					if (monp3 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ECA, kaisu);
					}
					if (monp3 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EBC, kaisu);
					}
					if (monp3 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E58, kaisu);
					}
					if (monp3 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E4C, kaisu);
					}
					if (monp3 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E4E, kaisu);
					}
					if (monp3 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E50, kaisu);
					}
					if (monp3 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EA2, kaisu);
					}
				}
				if (hokakup == 3)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ガノトトス",
																	   "ドドブランゴ",
																	   "ヴォルガノス",
																	   "ショウグンギザミ",
																	   "ガララアジャラ",
																	   "ナルガクルガ",
																	   "白疾風ナルガクルガ",
																	   "イャンガルルガ",
																	   "隻眼イャンガルルガ"});
					int monp4 = keyboard.Open();
					if (monp4 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E5E, kaisu);
					}
					if (monp4 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E74, kaisu);
					}
					if (monp4 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E88, kaisu);
					}
					if (monp4 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E72, kaisu);
					}
					if (monp4 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EBE, kaisu);
					}
					if (monp4 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E8A, kaisu);
					}
					if (monp4 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E8C, kaisu);
					}
					if (monp4 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E6A, kaisu);
					}
					if (monp4 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E6C, kaisu);
					}
				}
				if (hokakup == 4)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ウラガンキン",
																	   "宝纏ウラガンキン",
																	   "ゲネル・セルタス",
																	   "リオレウス",
																	   "リオレウス希少種",
																	   "黒炎王リオレウス",
																	   "ラギアクルス",
																	   "ジンオウガ",
																	   "金雷公ジンオウガ"});
					int monp5 = keyboard.Open();
					if (monp5 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E94, kaisu);
					}
					if (monp5 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E96, kaisu);
					}
					if (monp5 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EC0, kaisu);
					}
					if (monp5 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E52, kaisu);
					}
					if (monp5 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E54, kaisu);
					}
					if (monp5 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E56, kaisu);
					}
					if (monp5 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E98, kaisu);
					}
					if (monp5 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EA4, kaisu);
					}
					if (monp5 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EA6, kaisu);
					}
				}
				if (hokakup == 5)
				{
					Keyboard keyboard("モンスターを選んでください。", {"タマミツネ",
																	   "ライゼクス",
																	   "ガムート",
																	   "ディノバルド",
																	   "燼滅刃ディノバルド",
																	   "アグナコトル",
																	   "ゴア・マガラ",
																	   "セルレギオス",
																	   "ドボルベルク"});
					int monp6 = keyboard.Open();
					if (monp6 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ED2, kaisu);
					}
					if (monp6 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ED0, kaisu);
					}
					if (monp6 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ED4, kaisu);
					}
					if (monp6 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ECC, kaisu);
					}
					if (monp6 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ECE, kaisu);
					}
					if (monp6 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E9C, kaisu);
					}
					if (monp6 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EC2, kaisu);
					}
					if (monp6 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EC8, kaisu);
					}
					if (monp6 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EA0, kaisu);
					}
				}
				if (hokakup == 6)
				{
					Keyboard keyboard("モンスターを選んでください。", {"ティガレックス",
																	   "荒鉤爪ティガレックス",
																	   "キリン",
																	   "ブラキディオス",
																	   "シャガルマガラ",
																	   "ラージャン",
																	   "激昂したラージャン",
																	   "イビルジョー",
																	   "怒り喰らうイビルジョー",
																	   "クシャルダオラ",
																	   "オオナズチ"});
					int monp7 = keyboard.Open();
					if (monp7 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E82, kaisu);
					}
					if (monp7 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E84, kaisu);
					}
					if (monp7 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E60, kaisu);
					}
					if (monp7 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EB4, kaisu);
					}
					if (monp7 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EC4, kaisu);
					}
					if (monp7 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E76, kaisu);
					}
					if (monp7 == 6)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E78, kaisu);
					}
					if (monp7 == 7)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E90, kaisu);
					}
					if (monp7 == 8)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E92, kaisu);
					}
					if (monp7 == 9)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E7A, kaisu);
					}
					if (monp7 == 10)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E7C, kaisu);
					}
				}
				if (hokakup == 7)
				{
					Keyboard keyboard("モンスターを選んでください。", {"テオ・テスカトル",
																	   "アカムトルム",
																	   "ウカムルバス",
																	   "アマツマガツチ",
																	   "オストガロア",
																	   "アルバトリオン"});
					int monp8 = keyboard.Open();
					if (monp8 == 0)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E7E, kaisu);
					}
					if (monp8 == 1)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E86, kaisu);
					}
					if (monp8 == 2)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E8E, kaisu);
					}
					if (monp8 == 3)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3EA8, kaisu);
					}
					if (monp8 == 4)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3ED6, kaisu);
					}
					if (monp8 == 5)
					{
						Keyboard keyboard("捕獲数を入力してください。");
						keyboard.IsHexadecimal(false);
						keyboard.Open(kaisu);
						if (kaisu > 9999)
							kaisu = 9999;
						if (kaisu >= 0)
							Process::Write16(0x83B3E9E, kaisu);
					}
				}
			}
			if (choice == 2)
			{
				Keyboard keyboard("全ての狩猟数と捕獲数を9999にしますか？", {"はい",
																			 "いいえ"});
				int syuho = keyboard.Open();
				if (syuho == 0)
				{
					for (int i = 0; i < 67; i++)
						Process::Write16(i * 2 + 0x83B3D6C, 0x270F);
					for (int i = 0; i < 47; i++)
						Process::Write16(i * 2 + 0x83B3E4C, 0x270F);
				}
			}
		}
	}

	//セーブ画面選択肢固定設定
	static u8 savekotei;
	void saveyesno(MenuEntry *entry)
	{
		Keyboard keyboard("セーブ画面をどちらで固定しますか？", {"はい",
																 "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			savekotei = 0x0;
		if (choice == 1)
			savekotei = 0x1;
	}

	//セーブ画面選択肢固定
	void savegamenkotei(MenuEntry *entry)
	{
		if (Controller::IsKeysDown(R))
			Process::Write8(0x306E29A0, savekotei);
	}

	//アイテムボックス編集
	void itemboxedit(MenuEntry *entry)
	{
		Keyboard keyboard("アイテムボックスをどう編集しますか？", {"アイテムを入れる[1400種]",
																   "アイテムを入れる[548種]",
																   "全アイテム99個",
																   "全アイテム消去"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write16(0x8372562, 0x1);
			for (int i = 0; i < 1400; i++)
			{
				Process::Read16(i * 4 + 0x8372562, data16);
				Process::Write16(i * 4 + 0x8372566, data16 + 1);
			}
		}
		if (choice == 1)
		{
			Process::Write16(0x8372562, 0x578);
			for (int i = 0; i < 548; i++)
			{
				Process::Read16(i * 4 + 0x8372562, data16);
				Process::Write16(i * 4 + 0x8372566, data16 + 1);
			}
			for (int i = 0; i < 851; i++)
				Process::Write32(i * 4 + 0x8372DF6, 0x0);
		}
		if (choice == 2)
			for (int i = 0; i < 1400; i++)
				Process::Write16(i * 4 + 0x8372564, 0x63);
		if (choice == 3)
		{
			if (MessageBox("確認です", "全て削除してもいいですか？", DialogType::DialogYesNo)())
				for (int i = 0; i < 1400; i++)
					Process::Write32(i * 4 + 0x8372562, 0x0);
		}
	}

	//アイテムポーチ消去
	void porchclear(MenuEntry *entry)
	{
		if (MessageBox("確認です", "全て削除してもいいですか？", DialogType::DialogYesNo)())
			for (int i = 0; i < 32; i++)
				Process::Write32(i * 4 + 0x8372392, 0x0);
	}

	//トリプルアップ
	void tripleup(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::WriteFloat(offset + 0x1FF8, 3600);
		Process::WriteFloat(offset + 0x1FFC, 3600);
		Process::WriteFloat(offset + 0x2000, 3600);
	}

	//猟虫スタミナ無限
	void infmusistamina(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write16(offset + 0x2010, 0x82);
	}

	//溜め段階固定設定
	static float tame = 0;
	void tamedankai(MenuEntry *entry)
	{
		static int dankai = 0;
		Keyboard keyboard(Utils::Format("溜め段階を選んでください。\n現在[%u段階目]", dankai), {"0段階目",
																								"1段階目",
																								"2段階目",
																								"3段階目",
																								"4段階目"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			tame = 0;
			dankai = 0;
		}
		if (choice == 1)
		{
			tame = 40;
			dankai = 1;
		}
		if (choice == 2)
		{
			tame = 80;
			dankai = 2;
		}
		if (choice == 3)
		{
			tame = 120;
			dankai = 3;
		}
		if (choice == 4)
		{
			tame = 144;
			dankai = 4;
		}
	}

	//溜め段階固定
	void tamekotei(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::WriteFloat(offset + 0x1914, tame);
	}

	//武器ゲージ
	void bukigage(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write16(offset + 0x1598, 0x64);
	}

	//チャアクビン
	void tyaakubin(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write8(offset + 0x1922, 0x5);
	}

	//笛全効果付与
	void huegodmode(MenuEntry *entry)
	{
		u32 queframe;
		Process::Read32(0x8363ED4, queframe);
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		if (queframe != 0)
			for (int i = 0; i < 32; i++)
				Process::WriteFloat(offset + i * 4 + 0x17D0, 10);
	}

	//弾数
	void tamakazu(MenuEntry *entry)
	{
		u8 tama;
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Read8(offset + 0x1924, tama);
		Process::Write8(offset + 0x1922, tama);
	}

	//しゃがみ
	void syagami(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write8(offset + 0x1FF6, 0x7F);
	}

	//1番目のモンスターサイズ表示
	void mon1size(MenuEntry *entry)
	{
		static float mon1size;
		static int adrs_on = 0;
		adrs_on = true;
		Process::Read32(0x8325244, offset);
		Process::ReadFloat(offset + 0x1168, mon1size);

		if (offset != 0)
		{
			adrs_on = true;
			OSD::Run([](const Screen &screen) {
				if (!screen.IsTop)
					return (false);
				if (adrs_on == true)
				{
					screen.Draw(Utils::Format("Mon1SZ %.2f", mon1size), 10, 120, Color::Yellow);
					adrs_on = false;
				}
				return (true);
			});
		}
		else
			adrs_on = false;
	}

	//2番目のモンスターサイズ表示
	void mon2size(MenuEntry *entry)
	{
		static float mon2size;
		static int adrs_on = 0;
		adrs_on = true;
		Process::Read32(0x8325248, offset);
		Process::ReadFloat(offset + 0x1168, mon2size);

		if (offset != 0)
		{
			adrs_on = true;
			OSD::Run([](const Screen &screen) {
				if (!screen.IsTop)
					return (false);
				if (adrs_on == true)
				{
					screen.Draw(Utils::Format("Mon2SZ %.2f", mon2size), 10, 130, Color::Yellow);
					adrs_on = false;
				}
				return (true);
			});
		}
		else
			adrs_on = false;
	}

	//モンスターリピート設定
	static int mon1act, mon2act;
	void monrepeatop(MenuEntry *entry)
	{
		Keyboard keyboard("挙動を選んでください。", {"固まる",
													 "なめらか"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			mon1act = true;
			mon2act = true;
		}
		if (choice == 1)
		{
			mon1act = false;
			mon2act = false;
		}
	}

	//モンスターリピート
	void monrepeat(MenuEntry *entry)
	{
		u32 mon1, mon2;
		u8 erea1, erea2;
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Process::Read8(mon1 + 0xD, erea1);
		Process::Read8(mon2 + 0xD, erea2);
		if (Controller::IsKeysDown(X + DR))
		{
			if (Controller::IsKeysDown(R))
			{
				if (erea1 == 0x4C)
				{
					if (mon1act == true)
						Process::Write16(mon1 + 0x1158, 0x0);
					if (mon1act == false)
						Process::Write8(mon1 + 0x1159, 0x0);
				}
			}
			if (Controller::IsKeysDown(L))
			{
				if (erea2 == 0x4C)
				{
					if (mon2act == true)
						Process::Write16(mon1 + 0x1158, 0x0);
					if (mon2act == false)
						Process::Write8(mon1 + 0x1159, 0x0);
				}
			}
		}
	}

	//1番目と2番目のモンスター停止
	void mon12stop(MenuEntry *entry)
	{
		u32 mon1, mon2;
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Process::Write16(mon1 + 0x1158, 0x0);
		Process::Write16(mon2 + 0x1158, 0x0);
	}

	//1番目のモンスター速度変更設定
	static float mon1sp = 1;
	static float mon2sp = 1;
	void mon1speedop(MenuEntry *entry)
	{
		Keyboard keyboard(Utils::Format("速度倍率を入力してください。\n現在[%.2f]", mon1sp));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(mon1sp) != -1)
			;
	}

	//2番目のモンスター速度変更設定
	void mon2speedop(MenuEntry *entry)
	{
		Keyboard keyboard(Utils::Format("速度倍率を入力してください。\n現在[%.2f]", mon2sp));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(mon2sp) != -1)
			;
	}

	//1番目のモンスター速度変更
	void mon1speed(MenuEntry *entry)
	{
		u32 mon1;
		Process::Read32(0x8325244, mon1);
		Process::WriteFloat(mon1 + 0x2A4, mon1sp);
	}

	//2番目のモンスター速度変更
	void mon2speed(MenuEntry *entry)
	{
		u32 mon2;
		Process::Read32(0x8325248, mon2);
		Process::WriteFloat(mon2 + 0x2A4, mon2sp);
	}

	//1番目と2番目のモンスター透明
	void montoumei(MenuEntry *entry)
	{
		u32 mon1, mon2;
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Keyboard keyboard("透明にしますか？", {"はい",
											   "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write8(mon1 + 0x115C, 0x0);
			Process::Write8(mon2 + 0x115C, 0x0);
		}
		if (choice == 1)
		{
			Process::Write8(mon1 + 0x115C, 0x1);
			Process::Write8(mon2 + 0x115C, 0x1);
		}
	}

	//1番目と2番目のモンスター毒
	void mondoku(MenuEntry *entry)
	{
		u32 mon1, mon2;
		u16 doku1max, doku2max;
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Process::Read16(mon1 + 0x6820, doku1max);
		Process::Read16(mon2 + 0x6820, doku2max);
		Process::Write16(mon1 + 0x6814, doku1max);
		Process::Write16(mon2 + 0x6814, doku2max);
	}

	//1番目と2番目のモンスター麻痺
	void monmahi(MenuEntry *entry)
	{
		u32 mon1, mon2;
		u16 mahi1max, mahi2max;
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Process::Read16(mon1 + 0x682C, mahi1max);
		Process::Read16(mon2 + 0x682C, mahi2max);
		Process::Write16(mon1 + 0x682E, mahi1max);
		Process::Write16(mon2 + 0x682E, mahi2max);
	}

	//1番目と2番目のモンスター睡眠
	void monsuimin(MenuEntry *entry)
	{
		u32 mon1, mon2;
		u16 suimin1max, suimin2max;
		Process::Read32(0x8325244, mon1);
		Process::Read32(0x8325248, mon2);
		Process::Read16(mon1 + 0x6816, suimin1max);
		Process::Read16(mon2 + 0x6816, suimin2max);
		Process::Write16(mon1 + 0x6818, suimin1max);
		Process::Write16(mon2 + 0x6816, suimin2max);
	}

	//1番目のモンスターサイズ変更設定
	static float mon1sizech = 1;
	static float mon2sizech = 1;
	void mon1sizechangeop(MenuEntry *entry)
	{
		u32 mon1;
		Process::Read32(0x8325244, mon1);
		Process::ReadFloat(mon1 + 0x1168, mon1sizech);
		Keyboard keyboard(Utils::Format("サイズ倍率を入力してください。\n現在[%.2f]", mon1sizech));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(mon1sizech) != -1)
			;
	}

	//1番目のモンスターサイズ変更
	void mon1sizechange(MenuEntry *entry)
	{
		u32 mon1;
		Process::Read32(0x8325244, mon1);
		Process::WriteFloat(mon1 + 0x1168, mon1sizech);
	}

	//2番目のモンスターサイズ変更設定
	void mon2sizechangeop(MenuEntry *entry)
	{
		u32 mon2;
		Process::Read32(0x8325248, mon2);
		Process::WriteFloat(mon2 + 0x1168, mon2sizech);
		Keyboard keyboard(Utils::Format("サイズ倍率を入力してください。\n現在[%.2f]", mon2sizech));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(mon2sizech) != -1)
			;
	}

	//1番目のモンスターサイズ変更
	void mon2sizechange(MenuEntry *entry)
	{
		u32 mon2;
		Process::Read32(0x8325248, mon2);
		Process::WriteFloat(mon2 + 0x1168, mon2sizech);
	}

	//クエスト最大ダウン回数設定
	static u8 quedownmax, quedownnow;
	void questdownsaidaiop(MenuEntry *entry)
	{
		Process::Read8(0x8365440, quedownmax);
		Keyboard keyboard(Utils::Format("最大ダウン回数を入力してください。\n現在[%u]", quedownmax));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(quedownmax) != -1)
			;
	}

	//クエスト最大ダウン回数
	void questdownsaidai(MenuEntry *entry)
	{
		Process::Write8(0x8365440, quedownmax);
	}

	//クエスト現在ダウン回数設定
	void questdownimaop(MenuEntry *entry)
	{
		Process::Read8(0x8365440, quedownnow);
		Keyboard keyboard(Utils::Format("現在のダウン回数を入力してください。\n現在[%u]", quedownnow));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(quedownnow) != -1)
			;
	}

	//クエスト現在ダウン回数
	void questdownima(MenuEntry *entry)
	{
		Process::Write8(0x8365440, quedownnow);
	}

	//クエスト残り時間表示
	void questtime(MenuEntry *entry)
	{
		static u32 queframe, queframea, quebyouall, quebyou, quebyoua;
		static u32 quehunall, quehun, quehuna, quejikan, quejikana;
		static int adrs_on = 0;
		adrs_on = true;
		Process::Read32(0x8363ED4, queframe);
		queframea = queframe % 60;

		quejikana = queframe / 216000;
		quehunall = quejikana * 60;
		quehuna = queframe / 3600 - quehunall;
		quebyouall = quehuna * 60;
		quebyoua = queframe / 60 - quejikana * 3600 - quebyouall;

		if (queframe != 0)
		{
			adrs_on = true;
			OSD::Run([](const Screen &screen) {
				if (!screen.IsTop)
					return (false);
				if (adrs_on == true)
				{
					if (queframe <= 3600)
					{
						screen.Draw(Utils::Format("QT %d:%02d:%02d:%02d", quejikana, quehuna, quebyoua, queframea), 10, 180, Color::Red);
						adrs_on = false;
					}
					else
					{
						screen.Draw(Utils::Format("QT %d:%02d:%02d:%02d", quejikana, quehuna, quebyoua, queframea), 10, 180, Color::Yellow);
						adrs_on = false;
					}
				}
				return (true);
			});
		}
		else
			adrs_on = false;
	}

	//ハンターランクポイント変更
	void hrpchange(MenuEntry *entry)
	{
		u32 hrp;
		Process::Read32(0x83B3814, hrp);
		Keyboard keyboard(Utils::Format("HRPを入力してください。\n現在[%d]", hrp));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(hrp) != -1)
			Process::Write32(0x83B3814, hrp);
	}

	//全クエストクリア未クリア
	void allquest(MenuEntry *entry)
	{
		Keyboard keyboard("クエスト全クリアか、未クリアか選んでください。", {"クエスト全クリア",
																			 "クエスト全未クリア"});
		int choice = keyboard.Open();
		if (choice == 0)
			for (int i = 0; i < 0x1C; i++)
				Process::Write32(i * 0x4 + 0x83B3A6C, 0xFFFFFFFF);
		if (choice == 1)
			for (int i = 0; i < 0x1C; i++)
				Process::Write32(i * 0x4 + 0x83B3A6C, 0x0);
	}

	//フェニープーギーの名前変更
	void fenypugyname(MenuEntry *entry)
	{
		std::string name;
		Process::ReadString(0x83AE380, name, 0x1E, StringFormat::Utf8);
		Keyboard keyboard("グループを選んでください。", {"ベルナ村",
														 "ココット村",
														 "ポッケ村",
														 "ユクモ村"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::WriteString(0x83B3648, name, StringFormat::Utf8);
		if (choice == 1)
			Process::WriteString(0x83B3668, name, StringFormat::Utf8);
		if (choice == 2)
			Process::WriteString(0x83B3688, name, StringFormat::Utf8);
		if (choice == 3)
			Process::WriteString(0x83B36A8, name, StringFormat::Utf8);
	}

	//フェニープーギーの服変更
	void fenypugyhuku(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("グループを選んでください。", {"ベルナ村",
														 "ココット村",
														 "ポッケ村",
														 "ユクモ村"});
		int mura = keyboard.Open();
		if (mura == 0)
		{
			Keyboard keyboard("ベルナ村のフェニーの服を選んでください。", {"ルンルンベル",
																		   "召しませ姫林檎",
																		   "愛しのマドモワゼル",
																		   "常夏リゾート"});
			int choice = keyboard.Open();
			if (choice == 0)
				a = 0x0;
			if (choice == 1)
				a = 0x2;
			if (choice == 2)
				a = 0x1;
			if (choice == 3)
				a = 0x3;
			Process::Write8(0x83B36C8, a);
		}
		if (mura == 1)
		{
			Keyboard keyboard("ページを選んでください", {"1ページ目",
														 "2ページ目",
														 "3ページ目",
														 "4ページ目"});
			int choice = keyboard.Open();
			if (choice == 0)
			{
				Keyboard keyboard("ココット村のプーギーの服を選んでください。", {"思い出ストライプ",
																				 "マフモフウォーマー",
																				 "さすらい道中",
																				 "魅惑のピンク",
																				 "はだかの王様",
																				 "モスのきもち",
																				 "チューボー見習い",
																				 "夢追いアミーゴ"});
				int p1 = keyboard.Open();
				if (p1 == 0)
					a = 0x4;
				if (p1 == 1)
					a = 0x11;
				if (p1 == 2)
					a = 0x15;
				if (p1 == 3)
					a = 0x7;
				if (p1 == 4)
					a = 0x6;
				if (p1 == 5)
					a = 0x1B;
				if (p1 == 6)
					a = 0x16;
				if (p1 == 7)
					a = 0x5;
				Process::Write8(0x83B36C9, a);
			}
			if (choice == 1)
			{
				Keyboard keyboard("ココット村のプーギーの服を選んでください。", {"カエルのマーチ",
																				 "ドリームスター",
																				 "緑と黒の衝撃",
																				 "ブンブンビー",
																				 "ひよっこアフロ",
																				 "ブラックハニー",
																				 "ルドロスウォーマー",
																				 "ファンキーアフロ"});
				int p2 = keyboard.Open();
				if (p2 == 0)
					a = 0xC;
				if (p2 == 1)
					a = 0xA;
				if (p2 == 2)
					a = 0x8;
				if (p2 == 3)
					a = 0x12;
				if (p2 == 4)
					a = 0xD;
				if (p2 == 5)
					a = 0xE;
				if (p2 == 6)
					a = 0x1C;
				if (p2 == 7)
					a = 0x13;
				Process::Write8(0x83B36C9, a);
			}
			if (choice == 2)
			{
				Keyboard keyboard("ココット村のプーギーの服を選んでください。", {"天使のレオタード",
																				 "眠りを誘う白",
																				 "純真クレナイ",
																				 "あまくちピンク",
																				 "なき虫ベイビー",
																				 "おシノビ裝束",
																				 "いやされムーチョ",
																				 "イビルのきもち"});
				int p3 = keyboard.Open();
				if (p3 == 0)
					a = 0xB;
				if (p3 == 1)
					a = 0x9;
				if (p3 == 2)
					a = 0xF;
				if (p3 == 3)
					a = 0x18;
				if (p3 == 4)
					a = 0x19;
				if (p3 == 5)
					a = 0x10;
				if (p3 == 6)
					a = 0x14;
				if (p3 == 7)
					a = 0x1E;
				Process::Write8(0x83B36C9, a);
			}
			if (choice == 3)
			{
				Keyboard keyboard("ココット村のプーギーの服を選んでください。", {"ウーパールンバ",
																				 "ハートの女王様",
																				 "ドスのきもち",
																				 "なついろ恋浴衣",
																				 "パンプキンナイト",
																				 "キラキラ★ナイト"});
				int p4 = keyboard.Open();
				if (p4 == 0)
					a = 0x1D;
				if (p4 == 1)
					a = 0x20;
				if (p4 == 2)
					a = 0x1F;
				if (p4 == 3)
					a = 0x1A;
				if (p4 == 4)
					a = 0x21;
				if (p4 == 5)
					a = 0x22;
				Process::Write8(0x83B36C9, a);
			}
		}
		if (mura == 2)
		{
			Keyboard keyboard("ページを選んでください", {"1ページ目",
														 "2ページ目",
														 "3ページ目",
														 "4ページ目"});
			int choice = keyboard.Open();
			if (choice == 0)
			{
				Keyboard keyboard("ポッケ村のプーギーの服を選んでください。", {"思い出ストライプ",
																			   "マフモフウォーマー",
																			   "さすらい道中",
																			   "魅惑のピンク",
																			   "はだかの王様",
																			   "モスのきもち",
																			   "チューボー見習い",
																			   "夢追いアミーゴ"});
				int p1 = keyboard.Open();
				if (p1 == 0)
					a = 0x4;
				if (p1 == 1)
					a = 0x11;
				if (p1 == 2)
					a = 0x15;
				if (p1 == 3)
					a = 0x7;
				if (p1 == 4)
					a = 0x6;
				if (p1 == 5)
					a = 0x1B;
				if (p1 == 6)
					a = 0x16;
				if (p1 == 7)
					a = 0x5;
				Process::Write8(0x83B36CA, a);
			}
			if (choice == 1)
			{
				Keyboard keyboard("ポッケ村のプーギーの服を選んでください。", {"カエルのマーチ",
																			   "ドリームスター",
																			   "緑と黒の衝撃",
																			   "ブンブンビー",
																			   "ひよっこアフロ",
																			   "ブラックハニー",
																			   "ルドロスウォーマー",
																			   "ファンキーアフロ"});
				int p2 = keyboard.Open();
				if (p2 == 0)
					a = 0xC;
				if (p2 == 1)
					a = 0xA;
				if (p2 == 2)
					a = 0x8;
				if (p2 == 3)
					a = 0x12;
				if (p2 == 4)
					a = 0xD;
				if (p2 == 5)
					a = 0xE;
				if (p2 == 6)
					a = 0x1C;
				if (p2 == 7)
					a = 0x13;
				Process::Write8(0x83B36CA, a);
			}
			if (choice == 2)
			{
				Keyboard keyboard("ポッケ村のプーギーの服を選んでください。", {"天使のレオタード",
																			   "眠りを誘う白",
																			   "純真クレナイ",
																			   "あまくちピンク",
																			   "なき虫ベイビー",
																			   "おシノビ裝束",
																			   "いやされムーチョ",
																			   "イビルのきもち"});
				int p3 = keyboard.Open();
				if (p3 == 0)
					a = 0xB;
				if (p3 == 1)
					a = 0x9;
				if (p3 == 2)
					a = 0xF;
				if (p3 == 3)
					a = 0x18;
				if (p3 == 4)
					a = 0x19;
				if (p3 == 5)
					a = 0x10;
				if (p3 == 6)
					a = 0x14;
				if (p3 == 7)
					a = 0x1E;
				Process::Write8(0x83B36CA, a);
			}
			if (choice == 3)
			{
				Keyboard keyboard("ポッケ村のプーギーの服を選んでください。", {"ウーパールンバ",
																			   "ハートの女王様",
																			   "ドスのきもち",
																			   "なついろ恋浴衣",
																			   "パンプキンナイト",
																			   "キラキラ★ナイト"});
				int p4 = keyboard.Open();
				if (p4 == 0)
					a = 0x1D;
				if (p4 == 1)
					a = 0x20;
				if (p4 == 2)
					a = 0x1F;
				if (p4 == 3)
					a = 0x1A;
				if (p4 == 4)
					a = 0x21;
				if (p4 == 5)
					a = 0x22;
				Process::Write8(0x83B36CA, a);
			}
		}
		if (mura == 3)
		{
			Keyboard keyboard("ページを選んでください", {"1ページ目",
														 "2ページ目",
														 "3ページ目",
														 "4ページ目"});
			int choice = keyboard.Open();
			if (choice == 0)
			{
				Keyboard keyboard("ユクモ村のプーギーの服を選んでください。", {"思い出ストライプ",
																			   "マフモフウォーマー",
																			   "さすらい道中",
																			   "魅惑のピンク",
																			   "はだかの王様",
																			   "モスのきもち",
																			   "チューボー見習い",
																			   "夢追いアミーゴ"});
				int p1 = keyboard.Open();
				if (p1 == 0)
					a = 0x4;
				if (p1 == 1)
					a = 0x11;
				if (p1 == 2)
					a = 0x15;
				if (p1 == 3)
					a = 0x7;
				if (p1 == 4)
					a = 0x6;
				if (p1 == 5)
					a = 0x1B;
				if (p1 == 6)
					a = 0x16;
				if (p1 == 7)
					a = 0x5;
				Process::Write8(0x83B36CB, a);
			}
			if (choice == 1)
			{
				Keyboard keyboard("ユクモ村のプーギーの服を選んでください。", {"カエルのマーチ",
																			   "ドリームスター",
																			   "緑と黒の衝撃",
																			   "ブンブンビー",
																			   "ひよっこアフロ",
																			   "ブラックハニー",
																			   "ルドロスウォーマー",
																			   "ファンキーアフロ"});
				int p2 = keyboard.Open();
				if (p2 == 0)
					a = 0xC;
				if (p2 == 1)
					a = 0xA;
				if (p2 == 2)
					a = 0x8;
				if (p2 == 3)
					a = 0x12;
				if (p2 == 4)
					a = 0xD;
				if (p2 == 5)
					a = 0xE;
				if (p2 == 6)
					a = 0x1C;
				if (p2 == 7)
					a = 0x13;
				Process::Write8(0x83B36CB, a);
			}
			if (choice == 2)
			{
				Keyboard keyboard("ユクモ村のプーギーの服を選んでください。", {"天使のレオタード",
																			   "眠りを誘う白",
																			   "純真クレナイ",
																			   "あまくちピンク",
																			   "なき虫ベイビー",
																			   "おシノビ裝束",
																			   "いやされムーチョ",
																			   "イビルのきもち"});
				int p3 = keyboard.Open();
				if (p3 == 0)
					a = 0xB;
				if (p3 == 1)
					a = 0x9;
				if (p3 == 2)
					a = 0xF;
				if (p3 == 3)
					a = 0x18;
				if (p3 == 4)
					a = 0x19;
				if (p3 == 5)
					a = 0x10;
				if (p3 == 6)
					a = 0x14;
				if (p3 == 7)
					a = 0x1E;
				Process::Write8(0x83B36CB, a);
			}
			if (choice == 3)
			{
				Keyboard keyboard("ユクモ村のプーギーの服を選んでください。", {"ウーパールンバ",
																			   "ハートの女王様",
																			   "ドスのきもち",
																			   "なついろ恋浴衣",
																			   "パンプキンナイト",
																			   "キラキラ★ナイト"});
				int p4 = keyboard.Open();
				if (p4 == 0)
					a = 0x1D;
				if (p4 == 1)
					a = 0x20;
				if (p4 == 2)
					a = 0x1F;
				if (p4 == 3)
					a = 0x1A;
				if (p4 == 4)
					a = 0x21;
				if (p4 == 5)
					a = 0x22;
				Process::Write8(0x83B36CB, a);
			}
		}
	}

	//酔っぱらい設定
	static u8 yopparaia;
	void yopparaiop(MenuEntry *entry)
	{
		Keyboard keyboard("酔っぱらいになりますか？", {"はい",
													   "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			yopparaia = 0x02;
		if (choice == 1)
			yopparaia = 0x00;
	}

	//酔っぱらい
	void yopparai(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write8(offset + 0x1510, yopparaia);
	}

	//1回飲んだら酔っぱらい
	void yopparaikaisu(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::Write8(offset + 0x1538, 0xA);
	}

	//乗りゲージ
	void norigage(MenuEntry *entry)
	{
		Process::Read32(0x8195350, offset);
		Process::WriteFloat(offset + 0x2C18, 2000);
		Process::WriteFloat(offset + 0x2C1C, 1);
	}

	//腹減り無効
	void haraherimukou(MenuEntry *entry)
	{
		Process::Read32(0x8360F24, offset);
		Process::Read32(offset + 0xB4, offset);
		Process::WriteFloat(offset + 0x2DC, 1);
	}

	void kontorasuto(MenuEntry *entry)
	{
		float konto;
		Process::ReadFloat(0x81387A4, konto);
		Keyboard keyboard(Utils::Format("コントラストを入力してください\n現在[%.2f]", konto));
		keyboard.IsHexadecimal(false);
		keyboard.Open(konto);
		Process::WriteFloat(0x81387A4, konto);
	}

	void musisyurui(MenuEntry *entry)
	{
		Keyboard keyboard("虫の種類を選んでください。", {"なし",
														 "クルドローン",
														 "アルマスタッグ",
														 "ガシルドーレ",
														 "カゼキリバネ",
														 "モナークブルスタッグ",
														 "レジナヴォランテ",
														 "ドゥンクラーブ",
														 "ウカドゥーレ",
														 "オオシナト",
														 "シナトモドキ",
														 "エルドラーン",
														 "マルドローン",
														 "ザミールビートル",
														 "ハルキータ",
														 "ガルーヘル",
														 "ケーニヒゴアビートル",
														 "フィルカーノ",
														 "ドルンキータ",
														 "アルジョアーニャ",
														 "メイヴァーチル",
														 "ヴァンリエール",
														 "アルジャーロン",
														 "光のルフ",
														 "バレットホーク",
														 "とら",
														 "表示無し"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x8386C68, choice);
	}

	void musilevel(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫のレベルを入力してください。");
		keyboard.IsHexadecimal(false);
		keyboard.Open(a);
		Process::Write8(0x8386C69, a);
	}

	void musipower(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫のパワー補正を0~15で入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C6A, a);
	}

	void musiweight(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫のウェイト補正を0~15で入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C6B, a);
	}

	void musistamina(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫のスタミナ補正を0~15で入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C6C, a);
	}

	void musihi(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫の火属性を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C6D, a);
	}

	void musimizu(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫の水属性を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C6E, a);
	}

	void musikaminari(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫の雷属性を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C6F, a);
	}

	void musikori(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫の氷属性を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C70, a);
	}

	void musiryu(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("虫の龍属性を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8386C71, a);
	}

	void syukaitukurutarget(MenuEntry *entry)
	{
		Keyboard keyboard("ターゲットを？？？？？にしますか？", {"はい",
																 "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write8(0x8487CF3, 0x4C);
	}

	void syukaitukuruquekeisiki(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("クエスト形式コードを入力してください。\n20から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CF2, a);
	}

	void syukaitukuruhrkagen(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("募集HRの下限を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x8487CEE, a);
	}

	void syukaitukuruhrjougen(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("募集HRの上限を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x8487CF0, a);
	}

	void syukaitukuruninzuu(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("入室人数コードを入力してください。\n3から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CE9, a);
	}

	void syukaitukuruseigen(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("入室制限コードを入力してください。\n2から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CE8, a);
	}

	void syukaitukurupassumu(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("パスワード有無コードを入力してください。\n3から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CEC, a);
	}

	void syukaitukurubosyu1(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("募集文①コードを入力してください。\n33から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CF4, a);
	}

	void syukaitukurubosyu2(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("募集文②コードを入力してください。\n33から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CF5, a);
	}

	void syukaitukurubosyu3(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("募集文③コードを入力してください。\n33から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CF6, a);
	}

	void syukaitukurubosyu4(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("募集文④コードを入力してください。\n33から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487CF7, a);
	}

	void syukaisagasutarget(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("ターゲットコードを入力してください。\n75から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487D05, a);
	}

	void syukaisagasuquekeisiki(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("クエスト形式コードを入力してください。\n20から改造です。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487D04, a);
	}

	void syukaisagasuhrkagen(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("ホストHR下限を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x8487D00, a);
	}

	void syukaisagasuhrjougen(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("ホストHR上限を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x8487D02, a);
	}

	void syukaisagasuquenow(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("クエスト中コードを入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487D06, a);
	}

	void syukaisagasupassumu(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("パスワード有無コードを入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(0x8487D07, a);
	}

	void kariwaza1(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("狩技コードを入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x831B50C, a);
	}

	void kariwaza2(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("狩技コードを入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x831B50E, a);
	}

	void kariwaza3(MenuEntry *entry)
	{
		u16 a;
		Keyboard keyboard("狩技コードを入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write16(0x831B510, a);
	}

	void voicechange(MenuEntry *entry)
	{
		Keyboard keyboard("声を選んでください。", {"TYPE 1",
												   "TYPE 2",
												   "TYPE 3",
												   "TYPE 4",
												   "TYPE 5",
												   "TYPE 6",
												   "TYPE 7",
												   "TYPE 8",
												   "TYPE 9",
												   "TYPE 10",
												   "TYPE 11",
												   "TYPE 12",
												   "TYPE 13",
												   "TYPE 14",
												   "TYPE 15",
												   "TYPE 16",
												   "TYPE 17",
												   "TYPE 18",
												   "TYPE 19",
												   "TYPE 20"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6ED, choice);
	}

	void eyecolorchange(MenuEntry *entry)
	{
		Keyboard keyboard("目の色を選んでください。", {"茶色",
													   "赤色",
													   "青色",
													   "黄色",
													   "緑色",
													   "紫色",
													   "白色",
													   "黒色",
													   "全部白色",
													   "全部黒色"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6EE, choice);
	}

	void innerchange(MenuEntry *entry)
	{
		Keyboard keyboard("インナーを選んでください。", {"TYPE 1",
														 "TYPE 2",
														 "TYPE 3",
														 "TYPE 4",
														 "TYPE 5",
														 "TYPE 6",
														 "TYPE 7"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6EF, choice);
	}

	void seibetuchange(MenuEntry *entry)
	{
		Keyboard keyboard("性別を選んでください。", {"男",
													 "女"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6F0, choice);
	}

	void stylechange(MenuEntry *entry)
	{
		Keyboard keyboard("狩猟スタイルを選んでください。", {"ギルドスタイル",
															 "ストライカースタイル",
															 "エリアルスタイル",
															 "ブシドースタイル"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6F1, choice);
	}

	void hearchange(MenuEntry *entry)
	{
		Keyboard keyboard("髪型を選んでください。", {"TYPE 1",
													 "TYPE 2",
													 "TYPE 3",
													 "TYPE 4",
													 "TYPE 5",
													 "TYPE 6",
													 "TYPE 7",
													 "TYPE 8",
													 "TYPE 9",
													 "TYPE 10",
													 "TYPE 11",
													 "TYPE 12",
													 "TYPE 13",
													 "TYPE 14",
													 "TYPE 15",
													 "TYPE 16",
													 "TYPE 17",
													 "TYPE 18",
													 "TYPE 19",
													 "TYPE 20",
													 "TYPE 21",
													 "TYPE 22",
													 "TYPE 23",
													 "TYPE 24",
													 "TYPE 25",
													 "TYPE 26",
													 "TYPE 27",
													 "TYPE 28",
													 "TYPE 29",
													 "TYPE 30"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6F2, choice);
	}

	void kaochange(MenuEntry *entry)
	{
		Keyboard keyboard("顔を選んでください。", {"TYPE 1",
												   "TYPE 2",
												   "TYPE 3",
												   "TYPE 4",
												   "TYPE 5",
												   "TYPE 6",
												   "TYPE 7",
												   "TYPE 8",
												   "TYPE 9",
												   "TYPE 10",
												   "TYPE 11",
												   "TYPE 12",
												   "TYPE 13",
												   "TYPE 14",
												   "TYPE 15",
												   "TYPE 16",
												   "TYPE 17",
												   "TYPE 18"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6F3, choice);
	}

	void makechange(MenuEntry *entry)
	{
		Keyboard keyboard("メイクを選んでください。", {"TYPE 1",
													   "TYPE 2",
													   "TYPE 3",
													   "TYPE 4",
													   "TYPE 5",
													   "TYPE 6",
													   "TYPE 7",
													   "TYPE 8",
													   "TYPE 9",
													   "TYPE 10",
													   "TYPE 11",
													   "TYPE 12",
													   "TYPE 13",
													   "TYPE 14",
													   "メイクなし"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(0x831B6F4, choice);
	}

	static StringVector info;

	static const std::vector<Item> g_info =
		{
			{"タイトルID"},
			{"プロセスの名前"},
			{"3DSのタイプ"},
			{"Wi-Fi接続確認"}};

	void TitleID(void)
	{
		std::string tid;
		Process::GetTitleID(tid);
		MessageBox("タイトルIDは " + tid + " です。")();
	}
	void NameID(void)
	{
		std::string name;
		Process::GetName(name);
		MessageBox("プロセスの名前は " + name + " です。")();
	}

	void ConsoleType(void)
	{
		switch (System::IsNew3DS())
		{
		case 0:
			MessageBox("Old3DSです。")();
			break;
		case 1:
			MessageBox("New3DSです。")();
			break;
		}
	}

	void WiFiStatus(void)
	{
		switch (System::IsConnectedToInternet())
		{
		case 0:
			MessageBox("WiFiに接続されていません。")();
			break;
		case 1:
			MessageBox("WiFiに接続されています。")();
			break;
		}
	}

	void Information(MenuEntry *entry)
	{
		if (info.empty())
		{
			for (const Item &i : g_info)
				info.push_back(i.name);
		}
		Keyboard keyboard("確認したい情報を選んでください。", info);
		int choice = keyboard.Open();

		switch (choice)
		{
		case 0:
			TitleID();
			break;
		case 1:
			NameID();
			break;
		case 2:
			ConsoleType();
			break;
		case 3:
			WiFiStatus();
			break;
		}
	}

	void HexToDecd32(MenuEntry *entry)
	{
		u32 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応しています。\n例:FFFFFFFF = -1");
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%d"
									 " です。",
									 out))();
	}

	void HexToDecu32(MenuEntry *entry)
	{
		u32 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応していません。\n例:FFFFFFFF = 4294967295");
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%u"
									 " です。",
									 out))();
	}

	void HexToDecd16(MenuEntry *entry)
	{
		u16 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応しています。\n例:FFFF = -1");
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%d"
									 " です。",
									 out))();
	}

	void HexToDecu16(MenuEntry *entry)
	{
		u16 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応していません。\n例:FFFF = 65535");
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%u"
									 " です。",
									 out))();
	}

	void HexToDecd8(MenuEntry *entry)
	{
		u8 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応しています。\n例:FF = -1");
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%d"
									 " です。",
									 out))();
	}

	void HexToDecu8(MenuEntry *entry)
	{
		u8 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応していません。\n例:FF = 255");
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%u"
									 " です。",
									 out))();
	}

	void DecToHex(MenuEntry *entry)
	{
		u32 out;
		Keyboard keyboard("10進数を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(out) != -1)
			MessageBox(Utils::Format("結果は "
									 "%X"
									 " です。",
									 out))();
	}

	void hexcalc(MenuEntry *entry)
	{
		u32 data;
		int hex1, hex2, ans, choice;
		Keyboard keyboard("1番目の16進数を入力してください。");
		if (keyboard.Open(data) != -1)
		{
			hex1 = data;
			Keyboard keyboard("算術演算子を選んでください。", {"+", "-", "×", "÷"});
			choice = keyboard.Open();
			if (choice != -1)
			{
				Keyboard keyboard("2番目の16進数を入力してください。");
				if (keyboard.Open(data) != -1)
				{
					hex2 = data;
					if (choice == 0)
						ans = hex1 + hex2;
					if (choice == 1)
						ans = hex1 - hex2;
					if (choice == 2)
						ans = hex1 * hex2;
					if (choice == 3)
						ans = hex1 / hex2;
					MessageBox(Utils::Format("結果は %X です。", ans))();
				}
			}
		}
	}

	void deccalc(MenuEntry *entry)
	{
		u32 data;
		int dec1, dec2, ans, choice;
		Keyboard keyboard("1番目の10進数を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(data) != -1)
		{
			dec1 = data;
			Keyboard keyboard("算術演算子を選んでください。", {"+", "-", "×", "÷"});
			choice = keyboard.Open();
			if (choice != -1)
			{
				Keyboard keyboard("2番目の10進数を入力してください。");
				keyboard.IsHexadecimal(false);
				if (keyboard.Open(data) != -1)
				{
					dec2 = data;
					if (choice == 0)
						ans = dec1 + dec2;
					if (choice == 1)
						ans = dec1 - dec2;
					if (choice == 2)
						ans = dec1 * dec2;
					if (choice == 3)
						ans = dec1 / dec2;
					MessageBox(Utils::Format("結果は %d です。", ans))();
				}
			}
		}
	}

	void floatcalc(MenuEntry *entry)
	{
		int choice;
		float float1, float2, ans;
		Keyboard keyboard("1番目の浮動小数点数を入力してください。");
		if (keyboard.Open(float1) != -1)
		{
			Keyboard keyboard("算術演算子を選んでください。", {"+", "-", "×", "÷"});
			choice = keyboard.Open();
			if (choice != -1)
			{
				Keyboard keyboard("2番目の浮動小数点数を入力してください。");
				if (keyboard.Open(float2) != -1)
				{
					if (choice == 0)
						ans = float1 + float2;
					if (choice == 1)
						ans = float1 - float2;
					if (choice == 2)
						ans = float1 * float2;
					if (choice == 3)
						ans = float1 / float2;
					MessageBox(Utils::Format("結果は %f です。", ans))();
				}
			}
		}
	}

	void pointerhyoji(MenuEntry *entry)
	{
	}

	void pointermode(MenuEntry *entry)
	{
	}

	void pointer1(MenuEntry *entry)
	{
	}

	void pointer2(MenuEntry *entry)
	{
	}

	//変換候補変換
	void Chathenkan(MenuEntry *entry)
	{
		u32 a, b, c, aa, bb, cc, aaa, bbb, ccc;
		std::string moji1, moji2, moji3;
		aa = a + 0x18;
		aaa = a = 0xF8;
		bb = b + 0x18;
		bbb = b + 0xF8;
		cc = c + 0x18;
		ccc = c + 0xF8;
		Process::Read32(0x878CF80, a);
		Process::Read32(0x8790F80, b);
		Process::Read32(0x8791F80, c);
		Process::ReadString(aa, moji1, 12, StringFormat::Utf16);
		Process::ReadString(bb, moji2, 12, StringFormat::Utf16);
		Process::ReadString(cc, moji3, 12, StringFormat::Utf16);
		if (Controller::IsKeysDown(R))
		{
			if (moji1 == "るーと")
				Process::WriteString(aaa, "√", StringFormat::Utf16);
			if (moji2 == "るーと")
				Process::WriteString(bbb, "√", StringFormat::Utf16);
			if (moji3 == "るーと")
				Process::WriteString(ccc, "√", StringFormat::Utf16);
			if (moji1 == "まるいち")
				Process::WriteString(aaa, "①", StringFormat::Utf16);
			if (moji2 == "まるいち")
				Process::WriteString(bbb, "①", StringFormat::Utf16);
			if (moji3 == "まるいち")
				Process::WriteString(ccc, "①", StringFormat::Utf16);
			if (moji1 == "まるに")
				Process::WriteString(aaa, "②", StringFormat::Utf16);
			if (moji2 == "まるに")
				Process::WriteString(bbb, "②", StringFormat::Utf16);
			if (moji3 == "まるに")
				Process::WriteString(ccc, "②", StringFormat::Utf16);
			if (moji1 == "まるさん")
				Process::WriteString(aaa, "③", StringFormat::Utf16);
			if (moji2 == "まるさん")
				Process::WriteString(bbb, "③", StringFormat::Utf16);
			if (moji3 == "まるさん")
				Process::WriteString(ccc, "③", StringFormat::Utf16);
			if (moji1 == "まるよん")
				Process::WriteString(aaa, "④", StringFormat::Utf16);
			if (moji2 == "まるよん")
				Process::WriteString(bbb, "④", StringFormat::Utf16);
			if (moji3 == "まるよん")
				Process::WriteString(ccc, "④", StringFormat::Utf16);
			if (moji1 == "まるご")
				Process::WriteString(aaa, "⑤", StringFormat::Utf16);
			if (moji2 == "まるご")
				Process::WriteString(bbb, "⑤", StringFormat::Utf16);
			if (moji3 == "まるご")
				Process::WriteString(ccc, "⑤", StringFormat::Utf16);
			if (moji1 == "まるろく")
				Process::WriteString(aaa, "⑥", StringFormat::Utf16);
			if (moji2 == "まるろく")
				Process::WriteString(bbb, "⑥", StringFormat::Utf16);
			if (moji3 == "まるろく")
				Process::WriteString(ccc, "⑥", StringFormat::Utf16);
			if (moji1 == "まるなな")
				Process::WriteString(aaa, "⑦", StringFormat::Utf16);
			if (moji2 == "まるなな")
				Process::WriteString(bbb, "⑦", StringFormat::Utf16);
			if (moji3 == "まるなな")
				Process::WriteString(ccc, "⑦", StringFormat::Utf16);
			if (moji1 == "まるはち")
				Process::WriteString(aaa, "⑧", StringFormat::Utf16);
			if (moji2 == "まるはち")
				Process::WriteString(bbb, "⑧", StringFormat::Utf16);
			if (moji3 == "まるはち")
				Process::WriteString(ccc, "⑧", StringFormat::Utf16);
			if (moji1 == "まるきゅう")
				Process::WriteString(aaa, "⑨", StringFormat::Utf16);
			if (moji2 == "まるきゅう")
				Process::WriteString(bbb, "⑨", StringFormat::Utf16);
			if (moji3 == "まるきゅう")
				Process::WriteString(ccc, "⑨", StringFormat::Utf16);
			if (moji1 == "えす")
				Process::WriteString(aaa, "∫", StringFormat::Utf16);
			if (moji2 == "えす")
				Process::WriteString(bbb, "∫", StringFormat::Utf16);
			if (moji3 == "えす")
				Process::WriteString(ccc, "∫", StringFormat::Utf16);
			if (moji1 == "だぶるえす")
				Process::WriteString(aaa, "∬", StringFormat::Utf16);
			if (moji2 == "だぶるえす")
				Process::WriteString(bbb, "∬", StringFormat::Utf16);
			if (moji3 == "だぶるえす")
				Process::WriteString(ccc, "∬", StringFormat::Utf16);
			if (moji1 == "ろーまいち")
				Process::WriteString(aaa, "Ⅰ", StringFormat::Utf16);
			if (moji2 == "ろーまいち")
				Process::WriteString(bbb, "Ⅰ", StringFormat::Utf16);
			if (moji3 == "ろーまいち")
				Process::WriteString(ccc, "Ⅰ", StringFormat::Utf16);
			if (moji1 == "ろーまに")
				Process::WriteString(aaa, "Ⅱ", StringFormat::Utf16);
			if (moji2 == "ろーまに")
				Process::WriteString(bbb, "Ⅱ", StringFormat::Utf16);
			if (moji3 == "ろーまに")
				Process::WriteString(ccc, "Ⅱ", StringFormat::Utf16);
			if (moji1 == "ろーまさん")
				Process::WriteString(aaa, "Ⅲ", StringFormat::Utf16);
			if (moji2 == "ろーまさん")
				Process::WriteString(bbb, "Ⅲ", StringFormat::Utf16);
			if (moji3 == "ろーまさん")
				Process::WriteString(ccc, "Ⅲ", StringFormat::Utf16);
			if (moji1 == "ろーまよん")
				Process::WriteString(aaa, "Ⅳ", StringFormat::Utf16);
			if (moji2 == "ろーまよん")
				Process::WriteString(bbb, "Ⅳ", StringFormat::Utf16);
			if (moji3 == "ろーまよん")
				Process::WriteString(ccc, "Ⅳ", StringFormat::Utf16);
			if (moji1 == "ろーまご")
				Process::WriteString(aaa, "Ⅴ", StringFormat::Utf16);
			if (moji2 == "ろーまご")
				Process::WriteString(bbb, "Ⅴ", StringFormat::Utf16);
			if (moji3 == "ろーまご")
				Process::WriteString(ccc, "Ⅴ", StringFormat::Utf16);
			if (moji1 == "ろーまろく")
				Process::WriteString(aaa, "Ⅵ", StringFormat::Utf16);
			if (moji2 == "ろーまろく")
				Process::WriteString(bbb, "Ⅵ", StringFormat::Utf16);
			if (moji3 == "ろーまろく")
				Process::WriteString(ccc, "Ⅵ", StringFormat::Utf16);
			if (moji1 == "ろーまなな")
				Process::WriteString(aaa, "Ⅶ", StringFormat::Utf16);
			if (moji2 == "ろーまなな")
				Process::WriteString(bbb, "Ⅶ", StringFormat::Utf16);
			if (moji3 == "ろーまなな")
				Process::WriteString(ccc, "Ⅶ", StringFormat::Utf16);
			if (moji1 == "ろーまはち")
				Process::WriteString(aaa, "Ⅷ", StringFormat::Utf16);
			if (moji2 == "ろーまはち")
				Process::WriteString(bbb, "Ⅷ", StringFormat::Utf16);
			if (moji3 == "ろーまはち")
				Process::WriteString(ccc, "Ⅷ", StringFormat::Utf16);
			if (moji1 == "ろーまきゅう")
				Process::WriteString(aaa, "Ⅸ", StringFormat::Utf16);
			if (moji2 == "ろーまきゅう")
				Process::WriteString(bbb, "Ⅸ", StringFormat::Utf16);
			if (moji3 == "ろーまきゅう")
				Process::WriteString(ccc, "Ⅸ", StringFormat::Utf16);
			if (moji1 == "ろーまじゅう")
				Process::WriteString(aaa, "Ⅹ", StringFormat::Utf16);
			if (moji2 == "ろーまじゅう")
				Process::WriteString(bbb, "Ⅹ", StringFormat::Utf16);
			if (moji3 == "ろーまじゅう")
				Process::WriteString(ccc, "Ⅹ", StringFormat::Utf16);
			if (moji1 == "みり")
				Process::WriteString(aaa, "㍉", StringFormat::Utf16);
			if (moji2 == "みり")
				Process::WriteString(bbb, "㍉", StringFormat::Utf16);
			if (moji3 == "みり")
				Process::WriteString(ccc, "㍉", StringFormat::Utf16);
			if (moji1 == "きろ")
				Process::WriteString(aaa, "㌔", StringFormat::Utf16);
			if (moji2 == "きろ")
				Process::WriteString(bbb, "㌔", StringFormat::Utf16);
			if (moji3 == "きろ")
				Process::WriteString(ccc, "㌔", StringFormat::Utf16);
			if (moji1 == "せんち")
				Process::WriteString(aaa, "㌢", StringFormat::Utf16);
			if (moji2 == "せんち")
				Process::WriteString(bbb, "㌢", StringFormat::Utf16);
			if (moji3 == "せんち")
				Process::WriteString(ccc, "㌢", StringFormat::Utf16);
			if (moji1 == "めーとる")
				Process::WriteString(aaa, "㍍", StringFormat::Utf16);
			if (moji2 == "めーとる")
				Process::WriteString(bbb, "㍍", StringFormat::Utf16);
			if (moji3 == "めーとる")
				Process::WriteString(ccc, "㍍", StringFormat::Utf16);
			if (moji1 == "ぐらむ")
				Process::WriteString(aaa, "㌘", StringFormat::Utf16);
			if (moji2 == "ぐらむ")
				Process::WriteString(bbb, "㌘", StringFormat::Utf16);
			if (moji3 == "ぐらむ")
				Process::WriteString(ccc, "㌘", StringFormat::Utf16);
			if (moji1 == "とん")
				Process::WriteString(aaa, "㌧", StringFormat::Utf16);
			if (moji2 == "とん")
				Process::WriteString(bbb, "㌧", StringFormat::Utf16);
			if (moji3 == "とん")
				Process::WriteString(ccc, "㌧", StringFormat::Utf16);
			if (moji1 == "あーる")
				Process::WriteString(aaa, "㌃", StringFormat::Utf16);
			if (moji2 == "あーる")
				Process::WriteString(bbb, "㌃", StringFormat::Utf16);
			if (moji3 == "あーる")
				Process::WriteString(ccc, "㌃", StringFormat::Utf16);
			if (moji1 == "へくたーる")
				Process::WriteString(aaa, "㌶", StringFormat::Utf16);
			if (moji2 == "へくたーる")
				Process::WriteString(bbb, "㌶", StringFormat::Utf16);
			if (moji3 == "へくたーる")
				Process::WriteString(ccc, "㌶", StringFormat::Utf16);
			if (moji1 == "りっとる")
				Process::WriteString(aaa, "㍑", StringFormat::Utf16);
			if (moji2 == "りっとる")
				Process::WriteString(bbb, "㍑", StringFormat::Utf16);
			if (moji3 == "りっとる")
				Process::WriteString(ccc, "㍑", StringFormat::Utf16);
			if (moji1 == "わっと")
				Process::WriteString(aaa, "㍗", StringFormat::Utf16);
			if (moji2 == "わっと")
				Process::WriteString(bbb, "㍗", StringFormat::Utf16);
			if (moji3 == "わっと")
				Process::WriteString(ccc, "㍗", StringFormat::Utf16);
			if (moji1 == "かろりー")
				Process::WriteString(aaa, "㌍", StringFormat::Utf16);
			if (moji2 == "かろりー")
				Process::WriteString(bbb, "㌍", StringFormat::Utf16);
			if (moji3 == "かろりー")
				Process::WriteString(ccc, "㌍", StringFormat::Utf16);
			if (moji1 == "どる")
				Process::WriteString(aaa, "㌦", StringFormat::Utf16);
			if (moji2 == "どる")
				Process::WriteString(bbb, "㌦", StringFormat::Utf16);
			if (moji3 == "どる")
				Process::WriteString(ccc, "㌦", StringFormat::Utf16);
			if (moji1 == "せんと")
				Process::WriteString(aaa, "㌣", StringFormat::Utf16);
			if (moji2 == "せんと")
				Process::WriteString(bbb, "㌣", StringFormat::Utf16);
			if (moji3 == "せんと")
				Process::WriteString(ccc, "㌣", StringFormat::Utf16);
			if (moji1 == "ぱーせんと")
				Process::WriteString(aaa, "㌫", StringFormat::Utf16);
			if (moji2 == "ぱーせんと")
				Process::WriteString(bbb, "㌫", StringFormat::Utf16);
			if (moji3 == "ぱーせんと")
				Process::WriteString(ccc, "㌫", StringFormat::Utf16);
			if (moji1 == "みりばーる")
				Process::WriteString(aaa, "㍊", StringFormat::Utf16);
			if (moji2 == "みりばーる")
				Process::WriteString(bbb, "㍊", StringFormat::Utf16);
			if (moji3 == "みりばーる")
				Process::WriteString(ccc, "㍊", StringFormat::Utf16);
			if (moji1 == "ぺーじ")
				Process::WriteString(aaa, "㌻", StringFormat::Utf16);
			if (moji2 == "ぺーじ")
				Process::WriteString(bbb, "㌻", StringFormat::Utf16);
			if (moji3 == "ぺーじ")
				Process::WriteString(ccc, "㌻", StringFormat::Utf16);
			if (moji1 == "へいせい")
				Process::WriteString(aaa, "㍻", StringFormat::Utf16);
			if (moji2 == "へいせい")
				Process::WriteString(bbb, "㍻", StringFormat::Utf16);
			if (moji3 == "へいせい")
				Process::WriteString(ccc, "㍻", StringFormat::Utf16);
			if (moji1 == "しょうわ")
				Process::WriteString(aaa, "㍼", StringFormat::Utf16);
			if (moji2 == "しょうわ")
				Process::WriteString(bbb, "㍼", StringFormat::Utf16);
			if (moji3 == "しょうわ")
				Process::WriteString(ccc, "㍼", StringFormat::Utf16);
			if (moji1 == "たいしょう")
				Process::WriteString(aaa, "㍽", StringFormat::Utf16);
			if (moji2 == "たいしょう")
				Process::WriteString(bbb, "㍽", StringFormat::Utf16);
			if (moji3 == "たいしょう")
				Process::WriteString(ccc, "㍽", StringFormat::Utf16);
			if (moji1 == "めいじ")
				Process::WriteString(aaa, "㍾", StringFormat::Utf16);
			if (moji2 == "めいじ")
				Process::WriteString(bbb, "㍾", StringFormat::Utf16);
			if (moji3 == "めいじ")
				Process::WriteString(ccc, "㍾", StringFormat::Utf16);
			if (moji1 == "なんばー")
				Process::WriteString(aaa, "№", StringFormat::Utf16);
			if (moji2 == "なんばー")
				Process::WriteString(bbb, "№", StringFormat::Utf16);
			if (moji3 == "なんばー")
				Process::WriteString(ccc, "№", StringFormat::Utf16);
			if (moji1 == "けーけー")
				Process::WriteString(aaa, "㏍", StringFormat::Utf16);
			if (moji2 == "けーけー")
				Process::WriteString(bbb, "㏍", StringFormat::Utf16);
			if (moji3 == "けーけー")
				Process::WriteString(ccc, "㏍", StringFormat::Utf16);
			if (moji1 == "てる")
				Process::WriteString(aaa, "℡", StringFormat::Utf16);
			if (moji2 == "てる")
				Process::WriteString(bbb, "℡", StringFormat::Utf16);
			if (moji3 == "てる")
				Process::WriteString(ccc, "℡", StringFormat::Utf16);
			if (moji1 == "たぶ")
				Process::WriteString(aaa, "\t", StringFormat::Utf16);
			if (moji2 == "たぶ")
				Process::WriteString(bbb, "\t", StringFormat::Utf16);
			if (moji3 == "たぶ")
				Process::WriteString(ccc, "\t", StringFormat::Utf16);
			if (moji1 == "かいぎょう")
				Process::WriteString(aaa, "\n", StringFormat::Utf16);
			if (moji2 == "かいぎょう")
				Process::WriteString(bbb, "\n", StringFormat::Utf16);
			if (moji3 == "かいぎょう")
				Process::WriteString(ccc, "\n", StringFormat::Utf16);
			if (moji1 == "こう")
				Process::WriteString(aaa, "爻", StringFormat::Utf16);
			if (moji2 == "こう")
				Process::WriteString(bbb, "爻", StringFormat::Utf16);
			if (moji3 == "こう")
				Process::WriteString(ccc, "爻", StringFormat::Utf16);

			//	if(moji1 == "") Process::WriteString(aa, "", StringFormat::Utf16);
			//	if(moji2 == "") Process::WriteString(bb, "", StringFormat::Utf16);
			//	if(moji3 == "") Process::WriteString(cc, "", StringFormat::Utf16);
		}
	}

	//変換候補変換可能文字一覧
	void henkanitiran(MenuEntry *entry)
	{
		Keyboard keyboard("変換候補変換可能文字一覧です。\n"
						  "(数字)と書かれている所は、いち、に、等の数字を書いてください。\n"
						  "(単位)と書かれている所は、きろ、や、めーとる、等の単位を書いてください。\n"
						  "(元号)と書かれている所は、へいせい、や、しょうわ、等の元号を書いてください。\n"
						  "改行はキーボード上では表示されますが、チャットログだと空白が表示されます。\n"
						  "一部変換できない文字があります。",
						  {"るーと √",
						   "えす ∫",
						   "だぶるえす ∬",
						   "なんばー №",
						   "けーけー ㏍",
						   "てる ℡",
						   "こう 爻",
						   "まる(数字) ① ②",
						   "ろーま(数字) Ⅰ Ⅱ",
						   "(単位) ㌔ ㍍",
						   "(元号) ㍻ ㍼",
						   "かいぎょう",
						   "たぶ",
						   "どんどん追加してくよ！"});

		keyboard.Open();
	}

	static int otomosen;
	void otomosentaku(MenuEntry *entry)
	{
		std::string name1, name2, name3, name4, name5, name6, name7, name8, name9, name10;
		std::string name11, name12, name13, name14, name15, name16, name17, name18, name19, name20;
		std::string name21, name22, name23, name24, name25, name26, name27, name28, name29, name30;
		std::string name31, name32, name33, name34, name35, name36, name37, name38, name39, name40;
		std::string name41, name42, name43, name44, name45, name46, name47, name48, name49, name50;
		std::string name51, name52, name53, name54, name55, name56, name57, name58, name59, name60;

		Process::ReadString(0 * 0x494 + 0x8338AFE, name1, 30, StringFormat::Utf8);
		Process::ReadString(1 * 0x494 + 0x8338AFE, name2, 30, StringFormat::Utf8);
		Process::ReadString(2 * 0x494 + 0x8338AFE, name3, 30, StringFormat::Utf8);
		Process::ReadString(3 * 0x494 + 0x8338AFE, name4, 30, StringFormat::Utf8);
		Process::ReadString(4 * 0x494 + 0x8338AFE, name5, 30, StringFormat::Utf8);
		Process::ReadString(5 * 0x494 + 0x8338AFE, name6, 30, StringFormat::Utf8);
		Process::ReadString(6 * 0x494 + 0x8338AFE, name7, 30, StringFormat::Utf8);
		Process::ReadString(7 * 0x494 + 0x8338AFE, name8, 30, StringFormat::Utf8);
		Process::ReadString(8 * 0x494 + 0x8338AFE, name9, 30, StringFormat::Utf8);
		Process::ReadString(9 * 0x494 + 0x8338AFE, name10, 30, StringFormat::Utf8);
		Process::ReadString(10 * 0x494 + 0x8338AFE, name11, 30, StringFormat::Utf8);
		Process::ReadString(11 * 0x494 + 0x8338AFE, name12, 30, StringFormat::Utf8);
		Process::ReadString(12 * 0x494 + 0x8338AFE, name13, 30, StringFormat::Utf8);
		Process::ReadString(13 * 0x494 + 0x8338AFE, name14, 30, StringFormat::Utf8);
		Process::ReadString(14 * 0x494 + 0x8338AFE, name15, 30, StringFormat::Utf8);
		Process::ReadString(15 * 0x494 + 0x8338AFE, name16, 30, StringFormat::Utf8);
		Process::ReadString(16 * 0x494 + 0x8338AFE, name17, 30, StringFormat::Utf8);
		Process::ReadString(17 * 0x494 + 0x8338AFE, name18, 30, StringFormat::Utf8);
		Process::ReadString(18 * 0x494 + 0x8338AFE, name19, 30, StringFormat::Utf8);
		Process::ReadString(19 * 0x494 + 0x8338AFE, name20, 30, StringFormat::Utf8);
		Process::ReadString(20 * 0x494 + 0x8338AFE, name21, 30, StringFormat::Utf8);
		Process::ReadString(21 * 0x494 + 0x8338AFE, name22, 30, StringFormat::Utf8);
		Process::ReadString(22 * 0x494 + 0x8338AFE, name23, 30, StringFormat::Utf8);
		Process::ReadString(23 * 0x494 + 0x8338AFE, name24, 30, StringFormat::Utf8);
		Process::ReadString(24 * 0x494 + 0x8338AFE, name25, 30, StringFormat::Utf8);
		Process::ReadString(25 * 0x494 + 0x8338AFE, name26, 30, StringFormat::Utf8);
		Process::ReadString(26 * 0x494 + 0x8338AFE, name27, 30, StringFormat::Utf8);
		Process::ReadString(27 * 0x494 + 0x8338AFE, name28, 30, StringFormat::Utf8);
		Process::ReadString(28 * 0x494 + 0x8338AFE, name29, 30, StringFormat::Utf8);
		Process::ReadString(29 * 0x494 + 0x8338AFE, name30, 30, StringFormat::Utf8);
		Process::ReadString(30 * 0x494 + 0x8338AFE, name31, 30, StringFormat::Utf8);
		Process::ReadString(31 * 0x494 + 0x8338AFE, name32, 30, StringFormat::Utf8);
		Process::ReadString(32 * 0x494 + 0x8338AFE, name33, 30, StringFormat::Utf8);
		Process::ReadString(33 * 0x494 + 0x8338AFE, name34, 30, StringFormat::Utf8);
		Process::ReadString(34 * 0x494 + 0x8338AFE, name35, 30, StringFormat::Utf8);
		Process::ReadString(35 * 0x494 + 0x8338AFE, name36, 30, StringFormat::Utf8);
		Process::ReadString(36 * 0x494 + 0x8338AFE, name37, 30, StringFormat::Utf8);
		Process::ReadString(37 * 0x494 + 0x8338AFE, name38, 30, StringFormat::Utf8);
		Process::ReadString(38 * 0x494 + 0x8338AFE, name39, 30, StringFormat::Utf8);
		Process::ReadString(39 * 0x494 + 0x8338AFE, name40, 30, StringFormat::Utf8);
		Process::ReadString(40 * 0x494 + 0x8338AFE, name41, 30, StringFormat::Utf8);
		Process::ReadString(41 * 0x494 + 0x8338AFE, name42, 30, StringFormat::Utf8);
		Process::ReadString(42 * 0x494 + 0x8338AFE, name43, 30, StringFormat::Utf8);
		Process::ReadString(43 * 0x494 + 0x8338AFE, name44, 30, StringFormat::Utf8);
		Process::ReadString(44 * 0x494 + 0x8338AFE, name45, 30, StringFormat::Utf8);
		Process::ReadString(45 * 0x494 + 0x8338AFE, name46, 30, StringFormat::Utf8);
		Process::ReadString(46 * 0x494 + 0x8338AFE, name47, 30, StringFormat::Utf8);
		Process::ReadString(47 * 0x494 + 0x8338AFE, name48, 30, StringFormat::Utf8);
		Process::ReadString(48 * 0x494 + 0x8338AFE, name49, 30, StringFormat::Utf8);
		Process::ReadString(49 * 0x494 + 0x8338AFE, name50, 30, StringFormat::Utf8);
		Process::ReadString(50 * 0x494 + 0x8338AFE, name51, 30, StringFormat::Utf8);
		Process::ReadString(51 * 0x494 + 0x8338AFE, name52, 30, StringFormat::Utf8);
		Process::ReadString(52 * 0x494 + 0x8338AFE, name53, 30, StringFormat::Utf8);
		Process::ReadString(53 * 0x494 + 0x8338AFE, name54, 30, StringFormat::Utf8);
		Process::ReadString(54 * 0x494 + 0x8338AFE, name55, 30, StringFormat::Utf8);
		Process::ReadString(55 * 0x494 + 0x8338AFE, name56, 30, StringFormat::Utf8);
		Process::ReadString(56 * 0x494 + 0x8338AFE, name57, 30, StringFormat::Utf8);
		Process::ReadString(57 * 0x494 + 0x8338AFE, name58, 30, StringFormat::Utf8);
		Process::ReadString(58 * 0x494 + 0x8338AFE, name59, 30, StringFormat::Utf8);
		Process::ReadString(59 * 0x494 + 0x8338AFE, name60, 30, StringFormat::Utf8);
		Keyboard keyboard("ねこを選択してください。",
						  {name1, name2, name3, name4, name5,
						   name6, name7, name8, name9, name10,
						   name11, name12, name13, name14, name15,
						   name16, name17, name18, name19, name20,
						   name21, name22, name23, name24, name25,
						   name26, name27, name28, name29, name30,
						   name31, name32, name33, name34, name35,
						   name36, name37, name38, name39, name40,
						   name41, name42, name43, name44, name45,
						   name46, name47, name48, name49, name50,
						   name51, name52, name53, name54, name55,
						   name56, name57, name58, name59, name60});
		if (keyboard.Open() != -1)
			otomosen = keyboard.Open();
	}

	void otomoexp(MenuEntry *entry)
	{
		u32 exp;
		Process::Read32(otomosen * 0x494 + 0x83388E0, exp);
		Keyboard keyboard(Utils::Format("経験値を入力してください。\n現在[%d]", exp));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(exp) != -1)
			Process::Write32(otomosen * 0x494 + 0x83388E0, exp);
	}

	void otomolv(MenuEntry *entry)
	{
		u8 lv, lvhyouji;
		Process::Read8(otomosen * 0x494 + 0x83388E4, lv);
		lvhyouji = lv + 1;
		Keyboard keyboard(Utils::Format("レベルを入力してください。\n50までで設定してください。\n現在[%d]", lvhyouji));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(lv) != -1)
			Process::Write8(otomosen * 0x494 * 0x83388E4, lv);
	}

	void otomosupport(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388E5, sup);
		if (sup == 0x0)
			su = "カリスマ";
		if (sup == 0x1)
			su = "ファイト";
		if (sup == 0x2)
			su = "ガード";
		if (sup == 0x3)
			su = "アシスト";
		if (sup == 0x4)
			su = "回復";
		if (sup == 0x5)
			su = "ボマー";
		if (sup == 0x6)
			su = "コレクト";
		if (sup >= 0x7)
			su = "？？？";
		Keyboard keyboard("サポート傾向を選んでください。\n現在[" + su + "]", {"カリスマ",
																			   "ファイト",
																			   "ガード",
																			   "アシスト",
																			   "回復",
																			   "ボマー",
																			   "コレクト"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388E5, choice);
	}

	void otomosinmitudo(MenuEntry *entry)
	{
		u8 sinmitu;
		Process::Read8(otomosen * 0x494 + 0x83388E6, sinmitu);
		Keyboard keyboard(Utils::Format("親密度を入力してください。\n現在[%d]", sinmitu));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(sinmitu) != -1)
			Process::Write8(otomosen * 0x494 + 0x83388E6, sinmitu);
	}

	void otomotarget(MenuEntry *entry)
	{
		u8 tar;
		std::string ta;
		Process::Read8(otomosen * 0x494 + 0x83388E7, tar);
		if (tar == 0x0)
			ta = "指定なし";
		if (tar == 0x1)
			ta = "小型一筋";
		if (tar == 0x2)
			ta = "小型優先";
		if (tar == 0x3)
			ta = "バランス";
		if (tar == 0x4)
			ta = "大型優先";
		if (tar == 0x5)
			ta = "大型一筋";
		Keyboard keyboard("ターゲットを選んでください。\n現在[" + ta + "]", {"指定なし",
																			 "小型一筋",
																			 "小型優先",
																			 "バランス",
																			 "大型優先",
																			 "大型一筋"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388E7, tar);
	}

	void otomokome(MenuEntry *entry)
	{
		u8 kome;
		std::string ko;
		Process::Read8(otomosen * 0x494 + 0x83389A0, kome);
		if (kome < 0x80)
			ko = "可能";
		if (kome >= 0x80)
			ko = "不可能";
		Keyboard keyboard("オトモコメントを編集可能にしますか？。\n現在[オトモコメント編集" + ko + "]", {"はい",
																										 "いいえ"});
		if (int choice = keyboard.Open() != -1)
		{
			if (choice == 0)
				Process::Write8(otomosen * 0x494 + 0x83389A0, 0x20);
			if (choice == 1)
				Process::Write8(otomosen * 0x494 + 0x83389A0, 0xA0);
		}
	}

	void otomotokubetu(MenuEntry *entry)
	{
		u8 toku;
		std::string to;
		Process::Read8(otomosen * 0x494 + 0x83389A1, toku);
		if (toku == 0)
			to = "特別配信表示じゃない";
		if (toku == 1)
			to = "特別配信表示";
		Keyboard keyboard("特別配信表示にしますか？\n現在[" + to + "]", {"はい",
																		 "いいえ"});
		if (int choice = keyboard.Open() != -1)
		{
			if (choice == 0)
				Process::Write8(otomosen * 0x494 + 0x83389A1, 0x1);
			if (choice == 1)
				Process::Write8(otomosen * 0x494 + 0x83389A1, 0x0);
		}
	}

	void otomosoubisup1(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388E8, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("1番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388E8, choice);
	}

	void otomosoubisup2(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388E9, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("2番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388E9, choice);
	}

	void otomosoubisup3(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388EA, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("3番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388EA, choice);
	}

	void otomosoubisup4(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388EB, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("4番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388EB, choice);
	}

	void otomosoubisup5(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388EC, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("5番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388EC, choice);
	}

	void otomosoubisup6(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388ED, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("6番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388ED, choice);
	}

	void otomosoubisup7(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388EE, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("7番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388EE, choice);
	}

	void otomosoubisup8(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388EF, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("8番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388EF, choice);
	}

	void otomosoubiski1(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F0, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("1番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F0, choice);
	}

	void otomosoubiski2(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F1, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("2番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F1, choice);
	}

	void otomosoubiski3(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F2, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("3番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F2, choice);
	}

	void otomosoubiski4(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F3, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("4番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F3, choice);
	}

	void otomosoubiski5(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F4, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("5番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F4, choice);
	}

	void otomosoubiski6(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F5, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("6番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F5, choice);
	}

	void otomosoubiski7(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F6, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("7番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F6, choice);
	}

	void otomosoubiski8(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x83388F7, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("8番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術"
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F7, choice);
	}

	void otomosyutokusup1(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388F8, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("1番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F8, choice);
	}

	void otomosyutokusup2(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388F9, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("2番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388F9, choice);
	}

	void otomosyutokusup3(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388FA, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("3番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388FA, choice);
	}

	void otomosyutokusup4(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388FB, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("4番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388FB, choice);
	}

	void otomosyutokusup5(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388FC, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("5番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388FC, choice);
	}

	void otomosyutokusup6(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388FD, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("6番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388FD, choice);
	}

	void otomosyutokusup7(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388FE, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("7番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388FE, choice);
	}

	void otomosyutokusup8(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x83388FF, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("8番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x83388FF, choice);
	}

	void otomosyutokusup9(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338900, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("9番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					  "薬草笛の技",
																					  "回復笛の技",
																					  "真・回復笛の技",
																					  "解毒・消臭笛の技",
																					  "応援笛の技",
																					  "鬼人笛の技",
																					  "硬化笛の技",
																					  "超音波笛の技",
																					  "プチタル爆弾の技",
																					  "小タル爆弾の技",
																					  "大タル爆弾の技",
																					  "大タル爆弾Gの技",
																					  "特大タル爆弾の技",
																					  "打ち上げタル爆弾の技",
																					  "閃光爆弾の技",
																					  "設置型爆弾の技",
																					  "設置型爆弾Gの技",
																					  "落とし穴の技",
																					  "シビレ罠の技",
																					  "毒々落とし穴の技",
																					  "トランポリンの技",
																					  "ネコ式活力壺の技",
																					  "回復贈物の技",
																					  "緊急撤退の技",
																					  "巨大ブーメランの技",
																					  "貫通ブーメランの技",
																					  "隠密防御の技",
																					  "武器強化の技",
																					  "憤怒の技",
																					  "挑発の技",
																					  "オトモ鼓舞の技",
																					  "こやし玉の技",
																					  "応援ダンスの技",
																					  "治・ローリングの技",
																					  "爆・ローリングの技",
																					  "ぶんどりの技",
																					  "遠隔ぶんどりの技",
																					  "ネコまっしぐらの技",
																					  "ネコ爪乱舞の技",
																					  "しこ踏みドンの技",
																					  "イガグリ大砲の技",
																					  "電転虫発射の技",
																					  "ここ掘れニャンの技",
																					  "メガブーメランの技",
																					  "ネコ式火竜車の技",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338900, choice);
	}

	void otomosyutokusup10(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338901, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("10番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338901, choice);
	}

	void otomosyutokusup11(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338902, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("11番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338902, choice);
	}

	void otomosyutokusup12(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338903, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("12番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338903, choice);
	}

	void otomosyutokusup13(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338904, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("13番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338904, choice);
	}

	void otomosyutokusup14(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338905, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("14番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338905, choice);
	}

	void otomosyutokusup15(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338906, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("15番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338906, choice);
	}

	void otomosyutokusup16(MenuEntry *entry)
	{
		u8 sup;
		std::string su;
		Process::Read8(otomosen * 0x494 + 0x8338907, sup);
		if (sup == 0x00)
			su = "なし";
		if (sup == 0x01)
			su = "薬草笛の技";
		if (sup == 0x02)
			su = "回復笛の技";
		if (sup == 0x03)
			su = "真・回復笛の技";
		if (sup == 0x04)
			su = "解毒・消臭笛の技";
		if (sup == 0x05)
			su = "応援笛の技";
		if (sup == 0x06)
			su = "鬼人笛の技";
		if (sup == 0x07)
			su = "硬化笛の技";
		if (sup == 0x08)
			su = "超音波笛の技";
		if (sup == 0x09)
			su = "プチタル爆弾の技";
		if (sup == 0x0A)
			su = "小タル爆弾の技";
		if (sup == 0x0B)
			su = "大タル爆弾の技";
		if (sup == 0x0C)
			su = "大タル爆弾Gの技";
		if (sup == 0x0D)
			su = "特大タル爆弾の技";
		if (sup == 0x0E)
			su = "打ち上げタル爆弾の技";
		if (sup == 0x0F)
			su = "閃光爆弾の技";
		if (sup == 0x10)
			su = "設置型爆弾の技";
		if (sup == 0x11)
			su = "設置型爆弾Gの技";
		if (sup == 0x12)
			su = "落とし穴の技";
		if (sup == 0x13)
			su = "シビレ罠の技";
		if (sup == 0x14)
			su = "毒々落とし穴の技";
		if (sup == 0x15)
			su = "トランポリンの技";
		if (sup == 0x16)
			su = "ネコ式活力壺の技";
		if (sup == 0x17)
			su = "回復贈物の技";
		if (sup == 0x18)
			su = "緊急撤退の技";
		if (sup == 0x19)
			su = "巨大ブーメランの技";
		if (sup == 0x1A)
			su = "貫通ブーメランの技";
		if (sup == 0x1B)
			su = "隠密防御の技";
		if (sup == 0x1C)
			su = "武器強化の技";
		if (sup == 0x1D)
			su = "憤怒の技";
		if (sup == 0x1E)
			su = "挑発の技";
		if (sup == 0x1F)
			su = "オトモ鼓舞の技";
		if (sup == 0x20)
			su = "こやし玉の技";
		if (sup == 0x21)
			su = "応援ダンスの技";
		if (sup == 0x22)
			su = "治・ローリングの技";
		if (sup == 0x23)
			su = "爆・ローリングの技";
		if (sup == 0x24)
			su = "ぶんどりの技";
		if (sup == 0x25)
			su = "遠隔ぶんどりの技";
		if (sup == 0x26)
			su = "ネコまっしぐらの技";
		if (sup == 0x27)
			su = "ネコ爪乱舞の技";
		if (sup == 0x28)
			su = "しこ踏みドンの技";
		if (sup == 0x29)
			su = "イガグリ大砲の技";
		if (sup == 0x2A)
			su = "電転虫発射の技";
		if (sup == 0x2B)
			su = "ここ掘れニャンの技";
		if (sup == 0x2C)
			su = "メガブーメランの技";
		if (sup == 0x2D)
			su = "ネコ式火竜車の技";
		if (sup == 0x2E)
			su = "透明";
		Keyboard keyboard("16番目のサポート行動を選んでください。\n現在[" + su + "]", {"なし",
																					   "薬草笛の技",
																					   "回復笛の技",
																					   "真・回復笛の技",
																					   "解毒・消臭笛の技",
																					   "応援笛の技",
																					   "鬼人笛の技",
																					   "硬化笛の技",
																					   "超音波笛の技",
																					   "プチタル爆弾の技",
																					   "小タル爆弾の技",
																					   "大タル爆弾の技",
																					   "大タル爆弾Gの技",
																					   "特大タル爆弾の技",
																					   "打ち上げタル爆弾の技",
																					   "閃光爆弾の技",
																					   "設置型爆弾の技",
																					   "設置型爆弾Gの技",
																					   "落とし穴の技",
																					   "シビレ罠の技",
																					   "毒々落とし穴の技",
																					   "トランポリンの技",
																					   "ネコ式活力壺の技",
																					   "回復贈物の技",
																					   "緊急撤退の技",
																					   "巨大ブーメランの技",
																					   "貫通ブーメランの技",
																					   "隠密防御の技",
																					   "武器強化の技",
																					   "憤怒の技",
																					   "挑発の技",
																					   "オトモ鼓舞の技",
																					   "こやし玉の技",
																					   "応援ダンスの技",
																					   "治・ローリングの技",
																					   "爆・ローリングの技",
																					   "ぶんどりの技",
																					   "遠隔ぶんどりの技",
																					   "ネコまっしぐらの技",
																					   "ネコ爪乱舞の技",
																					   "しこ踏みドンの技",
																					   "イガグリ大砲の技",
																					   "電転虫発射の技",
																					   "ここ掘れニャンの技",
																					   "メガブーメランの技",
																					   "ネコ式火竜車の技",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338907, choice);
	}

	void otomosyutokuski1(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x8338908, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("1番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338908, choice);
	}

	void otomosyutokuski2(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x8338909, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("2番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338909, choice);
	}

	void otomosyutokuski3(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x833890A, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("3番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x833890A, choice);
	}

	void otomosyutokuski4(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x833890B, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("4番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x833890B, choice);
	}

	void otomosyutokuski5(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x833890C, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("5番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x833890C, choice);
	}

	void otomosyutokuski6(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x833890D, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("6番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x833890D, choice);
	}

	void otomosyutokuski7(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x833890E, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("7番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x833890E, choice);
	}

	void otomosyutokuski8(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x833890F, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("8番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x833890F, choice);
	}

	void otomosyutokuski9(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x8338910, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("9番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					  "体力強化の術【小】",
																					  "体力強化の術【大】",
																					  "攻撃強化の術【小】",
																					  "攻撃強化の術【大】",
																					  "防御強化の術【小】",
																					  "防御強化の術【大】",
																					  "全耐性強化の術",
																					  "会心強化の術【小】",
																					  "会心強化の術【大】",
																					  "匠の術",
																					  "爆弾強化の術",
																					  "属性攻撃強化の術",
																					  "状態異常攻撃強化の術",
																					  "KOの術",
																					  "滅気攻撃強化の術",
																					  "ガード性能の術【小】",
																					  "ガード性能の術【大】",
																					  "ガード強化の術",
																					  "サポート優先の術",
																					  "サポートプラスの術",
																					  "サポート行動追加の術",
																					  "ぶんどり強化の術",
																					  "復活上手の術",
																					  "熱・爆弾耐性の術",
																					  "毒耐性の術",
																					  "風圧無効の術",
																					  "麻痺無効の術",
																					  "気絶無効の術",
																					  "混乱無効の術",
																					  "耐震の術",
																					  "防音の術",
																					  "睡眠無効の術",
																					  "細菌学の術",
																					  "防御力DOWN無効の術",
																					  "だるま早割りの術",
																					  "七転八起の術【攻】",
																					  "七転八起の術【防】",
																					  "背水の陣の術",
																					  "怒り発動強化の術",
																					  "反撃サポート上昇の術",
																					  "モンスター探知の術",
																					  "ブーメラン上手の術",
																					  "罠設置上手の術",
																					  "採集専門の術",
																					  "サボりお仕置きの術",
																					  "体力増加演奏の術",
																					  "黄金魚狙いの術",
																					  "最高のネコよ！の術",
																					  "ハイケイデンスの術",
																					  "地上最強の術",
																					  "ゾンビーの術",
																					  "絶体絶命の術",
																					  "長飛丸の術",
																					  "ファナリスの術",
																					  "エーラの術",
																					  "遠隔攻撃強化の術",
																					  "プチタル爆弾改造の術",
																					  "着こなし上手の術",
																					  "ユニバーサルの術",
																					  "きりみ弁当の術",
																					  "ぐでぐでの術",
																					  "歌姫の術",
																					  "風のタクトの術",
																					  "ランドマスターの術",
																					  "スーパーキノコの術",
																					  "あきんどの術",
																					  "トライフォースの術",
																					  "モーフボールボムの術",
																					  "メガフレアの術",
																					  "防御優先の術",
																					  "体力強化優先の術",
																					  "火耐性強化の術",
																					  "水耐性強化の術",
																					  "雷耐性強化の術",
																					  "氷耐性強化の術",
																					  "龍耐性強化の術",
																					  "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338910, choice);
	}

	void otomosyutokuski10(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x8338911, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("10番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					   "体力強化の術【小】",
																					   "体力強化の術【大】",
																					   "攻撃強化の術【小】",
																					   "攻撃強化の術【大】",
																					   "防御強化の術【小】",
																					   "防御強化の術【大】",
																					   "全耐性強化の術",
																					   "会心強化の術【小】",
																					   "会心強化の術【大】",
																					   "匠の術",
																					   "爆弾強化の術",
																					   "属性攻撃強化の術",
																					   "状態異常攻撃強化の術",
																					   "KOの術",
																					   "滅気攻撃強化の術",
																					   "ガード性能の術【小】",
																					   "ガード性能の術【大】",
																					   "ガード強化の術",
																					   "サポート優先の術",
																					   "サポートプラスの術",
																					   "サポート行動追加の術",
																					   "ぶんどり強化の術",
																					   "復活上手の術",
																					   "熱・爆弾耐性の術",
																					   "毒耐性の術",
																					   "風圧無効の術",
																					   "麻痺無効の術",
																					   "気絶無効の術",
																					   "混乱無効の術",
																					   "耐震の術",
																					   "防音の術",
																					   "睡眠無効の術",
																					   "細菌学の術",
																					   "防御力DOWN無効の術",
																					   "だるま早割りの術",
																					   "七転八起の術【攻】",
																					   "七転八起の術【防】",
																					   "背水の陣の術",
																					   "怒り発動強化の術",
																					   "反撃サポート上昇の術",
																					   "モンスター探知の術",
																					   "ブーメラン上手の術",
																					   "罠設置上手の術",
																					   "採集専門の術",
																					   "サボりお仕置きの術",
																					   "体力増加演奏の術",
																					   "黄金魚狙いの術",
																					   "最高のネコよ！の術",
																					   "ハイケイデンスの術",
																					   "地上最強の術",
																					   "ゾンビーの術",
																					   "絶体絶命の術",
																					   "長飛丸の術",
																					   "ファナリスの術",
																					   "エーラの術",
																					   "遠隔攻撃強化の術",
																					   "プチタル爆弾改造の術",
																					   "着こなし上手の術",
																					   "ユニバーサルの術",
																					   "きりみ弁当の術",
																					   "ぐでぐでの術",
																					   "歌姫の術",
																					   "風のタクトの術",
																					   "ランドマスターの術",
																					   "スーパーキノコの術",
																					   "あきんどの術",
																					   "トライフォースの術",
																					   "モーフボールボムの術",
																					   "メガフレアの術",
																					   "防御優先の術",
																					   "体力強化優先の術",
																					   "火耐性強化の術",
																					   "水耐性強化の術",
																					   "雷耐性強化の術",
																					   "氷耐性強化の術",
																					   "龍耐性強化の術",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338911, choice);
	}

	void otomosyutokuski11(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x8338912, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("11番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					   "体力強化の術【小】",
																					   "体力強化の術【大】",
																					   "攻撃強化の術【小】",
																					   "攻撃強化の術【大】",
																					   "防御強化の術【小】",
																					   "防御強化の術【大】",
																					   "全耐性強化の術",
																					   "会心強化の術【小】",
																					   "会心強化の術【大】",
																					   "匠の術",
																					   "爆弾強化の術",
																					   "属性攻撃強化の術",
																					   "状態異常攻撃強化の術",
																					   "KOの術",
																					   "滅気攻撃強化の術",
																					   "ガード性能の術【小】",
																					   "ガード性能の術【大】",
																					   "ガード強化の術",
																					   "サポート優先の術",
																					   "サポートプラスの術",
																					   "サポート行動追加の術",
																					   "ぶんどり強化の術",
																					   "復活上手の術",
																					   "熱・爆弾耐性の術",
																					   "毒耐性の術",
																					   "風圧無効の術",
																					   "麻痺無効の術",
																					   "気絶無効の術",
																					   "混乱無効の術",
																					   "耐震の術",
																					   "防音の術",
																					   "睡眠無効の術",
																					   "細菌学の術",
																					   "防御力DOWN無効の術",
																					   "だるま早割りの術",
																					   "七転八起の術【攻】",
																					   "七転八起の術【防】",
																					   "背水の陣の術",
																					   "怒り発動強化の術",
																					   "反撃サポート上昇の術",
																					   "モンスター探知の術",
																					   "ブーメラン上手の術",
																					   "罠設置上手の術",
																					   "採集専門の術",
																					   "サボりお仕置きの術",
																					   "体力増加演奏の術",
																					   "黄金魚狙いの術",
																					   "最高のネコよ！の術",
																					   "ハイケイデンスの術",
																					   "地上最強の術",
																					   "ゾンビーの術",
																					   "絶体絶命の術",
																					   "長飛丸の術",
																					   "ファナリスの術",
																					   "エーラの術",
																					   "遠隔攻撃強化の術",
																					   "プチタル爆弾改造の術",
																					   "着こなし上手の術",
																					   "ユニバーサルの術",
																					   "きりみ弁当の術",
																					   "ぐでぐでの術",
																					   "歌姫の術",
																					   "風のタクトの術",
																					   "ランドマスターの術",
																					   "スーパーキノコの術",
																					   "あきんどの術",
																					   "トライフォースの術",
																					   "モーフボールボムの術",
																					   "メガフレアの術",
																					   "防御優先の術",
																					   "体力強化優先の術",
																					   "火耐性強化の術",
																					   "水耐性強化の術",
																					   "雷耐性強化の術",
																					   "氷耐性強化の術",
																					   "龍耐性強化の術",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338912, choice);
	}

	void otomosyutokuski12(MenuEntry *entry)
	{
		u8 ski;
		std::string sk;
		Process::Read8(otomosen * 0x494 + 0x8338913, ski);
		if (ski == 0x00)
			sk = "なし";
		if (ski == 0x01)
			sk = "体力強化の術【小】";
		if (ski == 0x02)
			sk = "体力強化の術【大】";
		if (ski == 0x03)
			sk = "攻撃強化の術【小】";
		if (ski == 0x04)
			sk = "攻撃強化の術【大】";
		if (ski == 0x05)
			sk = "防御強化の術【小】";
		if (ski == 0x06)
			sk = "防御強化の術【大】";
		if (ski == 0x07)
			sk = "全耐性強化の術";
		if (ski == 0x08)
			sk = "会心強化の術【小】";
		if (ski == 0x09)
			sk = "会心強化の術【大】";
		if (ski == 0x0A)
			sk = "匠の術";
		if (ski == 0x0B)
			sk = "爆弾強化の術";
		if (ski == 0x0C)
			sk = "属性攻撃強化の術";
		if (ski == 0x0D)
			sk = "状態異常攻撃強化の術";
		if (ski == 0x0E)
			sk = "KOの術";
		if (ski == 0x0F)
			sk = "滅気攻撃強化の術";
		if (ski == 0x10)
			sk = "ガード性能の術【小】";
		if (ski == 0x11)
			sk = "ガード性能の術【大】";
		if (ski == 0x12)
			sk = "ガード強化の術";
		if (ski == 0x13)
			sk = "サポート優先の術";
		if (ski == 0x14)
			sk = "サポートプラスの術";
		if (ski == 0x15)
			sk = "サポート行動追加の術";
		if (ski == 0x16)
			sk = "ぶんどり強化の術";
		if (ski == 0x17)
			sk = "復活上手の術";
		if (ski == 0x18)
			sk = "熱・爆弾耐性の術";
		if (ski == 0x19)
			sk = "毒耐性の術";
		if (ski == 0x1A)
			sk = "風圧無効の術";
		if (ski == 0x1B)
			sk = "麻痺無効の術";
		if (ski == 0x1C)
			sk = "気絶無効の術";
		if (ski == 0x1D)
			sk = "混乱無効の術";
		if (ski == 0x1E)
			sk = "耐震の術";
		if (ski == 0x1F)
			sk = "防音の術";
		if (ski == 0x20)
			sk = "睡眠無効の術";
		if (ski == 0x21)
			sk = "細菌学の術";
		if (ski == 0x22)
			sk = "防御力DOWN無効の術";
		if (ski == 0x23)
			sk = "だるま早割りの術";
		if (ski == 0x24)
			sk = "七転八起の術【攻】";
		if (ski == 0x25)
			sk = "七転八起の術【防】";
		if (ski == 0x26)
			sk = "背水の陣の術";
		if (ski == 0x27)
			sk = "怒り発動強化の術";
		if (ski == 0x28)
			sk = "反撃サポート上昇の術";
		if (ski == 0x29)
			sk = "モンスター探知の術";
		if (ski == 0x2A)
			sk = "ブーメラン上手の術";
		if (ski == 0x2B)
			sk = "罠設置上手の術";
		if (ski == 0x2C)
			sk = "採集専門の術";
		if (ski == 0x2D)
			sk = "サボりお仕置きの術";
		if (ski == 0x2E)
			sk = "体力増加演奏の術";
		if (ski == 0x2F)
			sk = "黄金魚狙いの術";
		if (ski == 0x30)
			sk = "最高のネコよ！の術";
		if (ski == 0x31)
			sk = "ハイケイデンスの術";
		if (ski == 0x32)
			sk = "地上最強の術";
		if (ski == 0x33)
			sk = "ゾンビーの術";
		if (ski == 0x34)
			sk = "絶体絶命の術";
		if (ski == 0x35)
			sk = "長飛丸の術";
		if (ski == 0x36)
			sk = "ファナリスの術";
		if (ski == 0x37)
			sk = "エーラの術";
		if (ski == 0x38)
			sk = "遠隔攻撃強化の術";
		if (ski == 0x39)
			sk = "プチタル爆弾改造の術";
		if (ski == 0x3A)
			sk = "着こなし上手の術";
		if (ski == 0x3B)
			sk = "ユニバーサルの術";
		if (ski == 0x3C)
			sk = "きりみ弁当の術";
		if (ski == 0x3D)
			sk = "ぐでぐでの術";
		if (ski == 0x3E)
			sk = "歌姫の術";
		if (ski == 0x3F)
			sk = "風のタクトの術";
		if (ski == 0x40)
			sk = "ランドマスターの術";
		if (ski == 0x41)
			sk = "スーパーキノコの術";
		if (ski == 0x42)
			sk = "あきんどの術";
		if (ski == 0x43)
			sk = "トライフォースの術";
		if (ski == 0x44)
			sk = "モーフボールボムの術";
		if (ski == 0x45)
			sk = "メガフレアの術";
		if (ski == 0x46)
			sk = "防御優先の術";
		if (ski == 0x47)
			sk = "体力強化優先の術";
		if (ski == 0x48)
			sk = "火耐性強化の術";
		if (ski == 0x49)
			sk = "水耐性強化の術";
		if (ski == 0x4A)
			sk = "雷耐性強化の術";
		if (ski == 0x4B)
			sk = "氷耐性強化の術";
		if (ski == 0x4C)
			sk = "龍耐性強化の術";
		if (ski == 0x4D)
			sk = "透明";
		Keyboard keyboard("12番目のオトモスキルを選んでください。\n現在[" + sk + "]", {"なし",
																					   "体力強化の術【小】",
																					   "体力強化の術【大】",
																					   "攻撃強化の術【小】",
																					   "攻撃強化の術【大】",
																					   "防御強化の術【小】",
																					   "防御強化の術【大】",
																					   "全耐性強化の術",
																					   "会心強化の術【小】",
																					   "会心強化の術【大】",
																					   "匠の術",
																					   "爆弾強化の術",
																					   "属性攻撃強化の術",
																					   "状態異常攻撃強化の術",
																					   "KOの術",
																					   "滅気攻撃強化の術",
																					   "ガード性能の術【小】",
																					   "ガード性能の術【大】",
																					   "ガード強化の術",
																					   "サポート優先の術",
																					   "サポートプラスの術",
																					   "サポート行動追加の術",
																					   "ぶんどり強化の術",
																					   "復活上手の術",
																					   "熱・爆弾耐性の術",
																					   "毒耐性の術",
																					   "風圧無効の術",
																					   "麻痺無効の術",
																					   "気絶無効の術",
																					   "混乱無効の術",
																					   "耐震の術",
																					   "防音の術",
																					   "睡眠無効の術",
																					   "細菌学の術",
																					   "防御力DOWN無効の術",
																					   "だるま早割りの術",
																					   "七転八起の術【攻】",
																					   "七転八起の術【防】",
																					   "背水の陣の術",
																					   "怒り発動強化の術",
																					   "反撃サポート上昇の術",
																					   "モンスター探知の術",
																					   "ブーメラン上手の術",
																					   "罠設置上手の術",
																					   "採集専門の術",
																					   "サボりお仕置きの術",
																					   "体力増加演奏の術",
																					   "黄金魚狙いの術",
																					   "最高のネコよ！の術",
																					   "ハイケイデンスの術",
																					   "地上最強の術",
																					   "ゾンビーの術",
																					   "絶体絶命の術",
																					   "長飛丸の術",
																					   "ファナリスの術",
																					   "エーラの術",
																					   "遠隔攻撃強化の術",
																					   "プチタル爆弾改造の術",
																					   "着こなし上手の術",
																					   "ユニバーサルの術",
																					   "きりみ弁当の術",
																					   "ぐでぐでの術",
																					   "歌姫の術",
																					   "風のタクトの術",
																					   "ランドマスターの術",
																					   "スーパーキノコの術",
																					   "あきんどの術",
																					   "トライフォースの術",
																					   "モーフボールボムの術",
																					   "メガフレアの術",
																					   "防御優先の術",
																					   "体力強化優先の術",
																					   "火耐性強化の術",
																					   "水耐性強化の術",
																					   "雷耐性強化の術",
																					   "氷耐性強化の術",
																					   "龍耐性強化の術",
																					   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338913, choice);
	}

	void otomovoice(MenuEntry *entry)
	{
		u8 voice;
		std::string vo;
		Process::Read8(otomosen * 0x494 + 0x8338AC1, voice);
		if (voice == 0)
			vo = "なし";
		if (voice == 1)
			vo = "TYPE1";
		if (voice == 2)
			vo = "TYPE2";
		if (voice == 3)
			vo = "TYPE3";
		if (voice >= 4)
			vo = "なし";
		Keyboard keyboard("声を選んでください。\n現在[" + vo + "]", {"なし",
																	 "TYPE1",
																	 "TYPE2",
																	 "TYPE3"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AC1, choice);
	}

	void otomoeye(MenuEntry *entry)
	{
		u8 eye;
		std::string ey;
		Process::Read8(otomosen * 0x494 + 0x8338AC2, eye);
		if (eye == 0)
			ey = "ふつう";
		if (eye == 1)
			ey = "ほそ目";
		if (eye == 2)
			ey = "つり目";
		if (eye == 3)
			ey = "ニヤケ目";
		if (eye == 4)
			ey = "閉じ目";
		if (eye == 5)
			ey = "キズ目";
		if (eye >= 6)
			ey = "透明";
		Keyboard keyboard("目を選んでください。\n現在[" + ey + "]", {"ふつう",
																	 "ほそ目",
																	 "つり目",
																	 "ニヤケ目",
																	 "閉じ目",
																	 "キズ目",
																	 "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AC2, choice);
	}

	void otomoinner(MenuEntry *entry)
	{
		u8 inner;
		std::string in;
		Process::Read8(otomosen * 0x494 + 0x8338AC3, inner);
		if (inner == 0)
			in = "TYPE1";
		if (inner == 1)
			in = "TYPE2";
		if (inner == 2)
			in = "ファラオ";
		if (inner == 3)
			in = "ゴア";
		if (inner == 4)
			in = "シャガル";
		if (inner >= 5)
			in = "透明";
		Keyboard keyboard("インナーを選んでください。\n現在[" + in + "]", {"TYPE1",
																		   "TYPE2",
																		   "ファラオ",
																		   "ゴア",
																		   "シャガル",
																		   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AC3, choice);
	}

	void otomokenami(MenuEntry *entry)
	{
		u8 kenami;
		std::string ke;
		Process::Read8(otomosen * 0x494 + 0x8338AC6, kenami);
		if (kenami == 0)
			ke = "アイルー";
		if (kenami == 1)
			ke = "メラルー";
		if (kenami == 2)
			ke = "アメショ";
		if (kenami == 3)
			ke = "ワントーン";
		if (kenami == 4)
			ke = "ツートーン";
		if (kenami == 5)
			ke = "ミケ";
		if (kenami == 6)
			ke = "ハンテン";
		if (kenami >= 7)
			ke = "アイルー";
		Keyboard keyboard("毛並みを選んでください。\n現在[" + ke + "]", {"アイルー",
																		 "メラルー",
																		 "アメショ",
																		 "ワントーン",
																		 "ツートーン",
																		 "ミケ",
																		 "ハンテン"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AC6, choice);
	}

	void otomomimi(MenuEntry *entry)
	{
		u8 mimi;
		std::string mi;
		Process::Read8(otomosen * 0x494 + 0x8338AC7, mimi);
		if (mimi == 0)
			mi = "ふつう";
		if (mimi == 1)
			mi = "たれ耳";
		if (mimi == 2)
			mi = "聞き耳";
		if (mimi == 3)
			mi = "立ち耳";
		if (mimi == 4)
			mi = "まる耳";
		if (mimi >= 5)
			mi = "透明";
		Keyboard keyboard("耳を選んでください。\n現在[" + mi + "]", {"ふつう",
																	 "たれ耳",
																	 "聞き耳",
																	 "立ち耳",
																	 "まる耳",
																	 "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AC7, choice);
	}

	void otomosippo(MenuEntry *entry)
	{
		u8 sippo;
		std::string si;
		Process::Read8(otomosen * 0x494 + 0x8338AC8, sippo);
		if (sippo == 0)
			si = "ふつう";
		if (sippo == 1)
			si = "ダンゴ";
		if (sippo == 2)
			si = "カギ";
		if (sippo == 3)
			si = "ふさふさ";
		if (sippo == 4)
			si = "ながまる";
		if (sippo >= 5)
			si = "透明";
		Keyboard keyboard("尻尾を選んでください。\n現在[" + si + "]", {"ふつう",
																	   "ダンゴ",
																	   "カギ",
																	   "ふさふさ",
																	   "ながまる",
																	   "透明"});
		if (int choice = keyboard.Open() != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AC8, choice);
	}

	void otomokeiror(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("赤の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338ACC, a);
	}

	void otomokeirog(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("緑の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338ACD, a);
	}

	void otomokeirob(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("青の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338ACE, a);
	}

	void otomomigimeiror(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("赤の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD0, a);
	}

	void otomomigimeirog(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("緑の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD1, a);
	}

	void otomomigimeirob(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("青の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD2, a);
	}

	void otomohidarimeiror(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("赤の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD4, a);
	}

	void otomohidarimeirog(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("緑の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD5, a);
	}

	void otomohidarimeirob(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("青の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD6, a);
	}

	void otomoinneriror(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("赤の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD8, a);
	}

	void otomoinnerirog(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("緑の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338AD9, a);
	}

	void otomoinnerirob(MenuEntry *entry)
	{
		u8 a;
		Keyboard keyboard("青の値を入力してください\n1~255の間");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(a) != -1)
			Process::Write8(otomosen * 0x494 + 0x8338ADA, a);
	}

	void otomonamech(MenuEntry *entry)
	{
		std::string nameteikei, namenow, namekbd;
		Process::ReadString(0x83AE380, nameteikei, 0x1E, StringFormat::Utf8);
		Process::ReadString(otomosen * 0x494 + 0x8338AFE, namenow, 0x1E, StringFormat::Utf8);
		Keyboard keyboard("どちらで変更しますか？\n現在の名前[" + namenow + "]", {"定型文",
																				  "キーボード"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			for (int i = 0; i < 8; i++)
				Process::Write32(i * 4 + otomosen * 0x494 + 0x8338AFE, 0);
			Process::WriteString(otomosen * 0x494 + 0x8338AFE, nameteikei, StringFormat::Utf8);
		}
		if (choice == 1)
		{
			Keyboard keyboard("名前を入力してください。");
			if (keyboard.Open(namekbd) != -1)
			{
				for (int i = 0; i < 8; i++)
					Process::Write32(i * 4 + otomosen * 0x494 + 0x8338AFE, 0);
				Process::WriteString(otomosen * 0x494 + 0x8338AFE, namekbd, StringFormat::Utf8);
			}
		}
	}

	void otomocomech(MenuEntry *entry)
	{
		std::string nameteikei, namenow, namekbd;
		Process::ReadString(0x83AE380, nameteikei, 0x1E, StringFormat::Utf8);
		Process::ReadString(otomosen * 0x494 + 0x8338920, namenow, 0x1E, StringFormat::Utf8);
		Keyboard keyboard("どちらで変更しますか？\n現在のコメント[" + namenow + "]", {"定型文",
																					  "キーボード"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			for (int i = 0; i < 15; i++)
				Process::Write32(i * 4 + otomosen * 0x494 + 0x8338920, 0);
			Process::WriteString(otomosen * 0x494 + 0x8338920, nameteikei, StringFormat::Utf8);
		}
		if (choice == 1)
		{
			Keyboard keyboard("コメントを入力してください。");
			if (keyboard.Open(namekbd) != -1)
			{
				for (int i = 0; i < 15; i++)
					Process::Write32(i * 4 + otomosen * 0x494 + 0x8338920, 0);
				Process::WriteString(otomosen * 0x494 + 0x8338920, namekbd, StringFormat::Utf8);
			}
		}
	}

	void otomonaduch(MenuEntry *entry)
	{
		std::string nameteikei, namenow, namekbd;
		Process::ReadString(0x83AE380, nameteikei, 0x1E, StringFormat::Utf8);
		Process::ReadString(otomosen * 0x494 + 0x833895C, namenow, 0x1E, StringFormat::Utf8);
		Keyboard keyboard("どちらで変更しますか？\n現在の名付け親[" + namenow + "]", {"定型文",
																					  "キーボード"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			for (int i = 0; i < 8; i++)
				Process::Write32(i * 4 + otomosen * 0x494 + 0x833895C, 0);
			Process::WriteString(otomosen * 0x494 + 0x833895C, nameteikei, StringFormat::Utf8);
		}
		if (choice == 1)
		{
			Keyboard keyboard("名付け親を入力してください。");
			if (keyboard.Open(namekbd) != -1)
			{
				for (int i = 0; i < 8; i++)
					Process::Write32(i * 4 + otomosen * 0x494 + 0x833895C, 0);
				Process::WriteString(otomosen * 0x494 + 0x833895C, namekbd, StringFormat::Utf8);
			}
		}
	}

	void otomosendaich(MenuEntry *entry)
	{
		std::string nameteikei, namenow, namekbd;
		Process::ReadString(0x83AE380, nameteikei, 0x1E, StringFormat::Utf8);
		Process::ReadString(otomosen * 0x494 + 0x833897C, namenow, 0x1E, StringFormat::Utf8);
		Keyboard keyboard("どちらで変更しますか？\n現在の先代旦那さん[" + namenow + "]", {"定型文",
																						  "キーボード"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			for (int i = 0; i < 8; i++)
				Process::Write32(i * 4 + otomosen * 0x494 + 0x833897C, 0);
			Process::WriteString(otomosen * 0x494 + 0x833897C, nameteikei, StringFormat::Utf8);
		}
		if (choice == 1)
		{
			Keyboard keyboard("先代旦那さんを入力してください。");
			if (keyboard.Open(namekbd) != -1)
			{
				for (int i = 0; i < 8; i++)
					Process::Write32(i * 4 + otomosen * 0x494 + 0x833897C, 0);
				Process::WriteString(otomosen * 0x494 + 0x833897C, namekbd, StringFormat::Utf8);
			}
		}
	}

	void otomokyusyu(MenuEntry *entry)
	{
		u32 neko1, neko2, neko3, neko4;
		u32 player;
		float playerx, playerz;
		Process::Read32(0x8327C04, neko1);
		Process::Read32(0x8327C08, neko2);
		Process::Read32(0x8327C0C, neko3);
		Process::Read32(0x8327C10, neko4);
		Process::Read32(0x8195350, player);
		Process::ReadFloat(player + 0x40, playerx);
		Process::ReadFloat(player + 0x48, playerz);

		Process::WriteFloat(neko1 + 0x40, playerx);
		Process::WriteFloat(neko1 + 0x48, playerz);
		Process::WriteFloat(neko2 + 0x40, playerx);
		Process::WriteFloat(neko2 + 0x48, playerz);
		Process::WriteFloat(neko3 + 0x40, playerx);
		Process::WriteFloat(neko3 + 0x48, playerz);
		Process::WriteFloat(neko4 + 0x40, playerx);
		Process::WriteFloat(neko4 + 0x48, playerz);
	}

	void speedhack(MenuEntry *entry)
	{
		float speed;
		Process::ReadFloat(0x317298, speed);
		Keyboard keyboard(Utils::Format("速度を何倍にしますか？\n-にすると後ろに移動します\n現在[%.2f]", speed));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(speed) != -1)
			Process::WriteFloat(0x317298, speed);
	}

	void kamerasiyahack(MenuEntry *entry)
	{
		float siya;
		Process::ReadFloat(0x9C4AD4, siya);
		Keyboard keyboard(Utils::Format("視野を何倍に拡大しますか？\n-にすると上下反対になります。\n現在[%.2f]", siya));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(siya) != -1)
			Process::WriteFloat(0x9C4AD4, siya);
	}

	void bukisizehack(MenuEntry *entry)
	{
		float size;
		Process::ReadFloat(0xA58AF0, size);
		Keyboard keyboard(Utils::Format("武器サイズを何倍にしますか？\n現在[%.2f]", size));
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(size) != -1)
			Process::WriteFloat(0xA58AF0, size);
	}

	static u16 attackv;
	static u16 defencev;
	static u16 zokuseiv;
	static u16 taiseihiv;
	static u16 taiseimizuv;
	static u16 taiseikaminariv;
	static u16 taiseikoriv;
	static u16 taiseiryuv;
	void attackv2op(MenuEntry *entry)
	{
		Keyboard keyboard("素の攻撃力を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(attackv) != -1)
			;
	}

	void attackv2(MenuEntry *entry)
	{
		Process::Write16(0x831B450, attackv);
	}

	void defencev2op(MenuEntry *entry)
	{
		Keyboard keyboard("素の防御力を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(defencev) != -1)
			;
	}

	void defencev2(MenuEntry *entry)
	{
		Process::Write16(0x831B45E, defencev);
	}

	void zokuseiv2op(MenuEntry *entry)
	{
		Keyboard keyboard("素の属性値を入力してください。");
		keyboard.IsHexadecimal(false);
		if (keyboard.Open(zokuseiv) != -1)
			;
	}

	void zokuseiv2(MenuEntry *entry)
	{
		Process::Write16(0x831B45A, zokuseiv);
	}

	void taiseiv2op(MenuEntry *entry)
	{
		Keyboard keyboard("グループを選んでください。", {"火耐性変更",
														 "水耐性変更",
														 "雷耐性変更",
														 "氷耐性変更",
														 "龍耐性変更",
														 "一括変更"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Keyboard keyboard("素の火耐性値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(taiseihiv) != -1)
				;
		}
		if (choice == 1)
		{
			Keyboard keyboard("素の水耐性値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(taiseimizuv) != -1)
				;
		}
		if (choice == 2)
		{
			Keyboard keyboard("素の雷耐性値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(taiseikaminariv) != -1)
				;
		}
		if (choice == 3)
		{
			Keyboard keyboard("素の氷耐性値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(taiseikoriv) != -1)
				;
		}
		if (choice == 4)
		{
			Keyboard keyboard("素の龍耐性値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(taiseiryuv) != -1)
				;
		}
		if (choice == 5)
		{
			u8 taisei;
			Keyboard keyboard("素の耐性値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(taisei) != -1)
				;
			taiseihiv = taisei;
			taiseimizuv = taisei;
			taiseikaminariv = taisei;
			taiseikoriv = taisei;
			taiseiryuv = taisei;
		}
	}

	void taiseiv2(MenuEntry *entry)
	{
		Process::Write16(0x831B460, taiseihiv);
		Process::Write16(0x831B462, taiseimizuv);
		Process::Write16(0x831B464, taiseikaminariv);
		Process::Write16(0x831B466, taiseikoriv);
		Process::Write16(0x831B468, taiseiryuv);
	}

	static u8 rnyu, gnyu, bnyu;
	void rnyuryoku(MenuEntry *entry)
	{
		Keyboard keyboard("入力モードを選んでください。", {"10進数",
														   "16進数"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Keyboard keyboard("R値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(rnyu) != -1)
				;
		}
		if (choice == 1)
		{
			Keyboard keyboard("R値を入力してください。");
			if (keyboard.Open(rnyu) != -1)
				;
		}
	}

	void gnyuryoku(MenuEntry *entry)
	{
		Keyboard keyboard("入力モードを選んでください。", {"10進数",
														   "16進数"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Keyboard keyboard("G値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(gnyu) != -1)
				;
		}
		if (choice == 1)
		{
			Keyboard keyboard("G値を入力してください。");
			if (keyboard.Open(gnyu) != -1)
				;
		}
	}

	void bnyuryoku(MenuEntry *entry)
	{
		Keyboard keyboard("入力モードを選んでください。", {"10進数", "16進数"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Keyboard keyboard("B値を入力してください。");
			keyboard.IsHexadecimal(false);
			if (keyboard.Open(bnyu) != -1)
				;
		}
		if (choice == 1)
		{
			Keyboard keyboard("B値を入力してください。");
			if (keyboard.Open(bnyu) != -1)
				;
		}
	}

	void rgbcheck(MenuEntry *entry)
	{
		Keyboard keyboard("グループを選んでください。", {"入力された値を確認",
														 "出力された色を確認"});
		int choice = keyboard.Open();
		if (choice == 0)
			MessageBox(Utils::Format("入力された値です。\nR[%02X]\nG[%02X]\nB[%02X]", rnyu, gnyu, bnyu))();
		if (choice == 1)
			MessageBox("出力された色です。\n"
					   << Color(rnyu, gnyu, bnyu) << "■■■■■■■■■\n■■■■■■■■■\n■■■■■■■■■")();
	}

	void HexEditor(MenuEntry *entry)
	{
		static int adrs_on = 0;
		static u32 Hex, Hex1, Hex2, Hex3, Hex4, Hex5, Hex6, Hex7, Hex8, Hex9, Hex11;
		static u32 address, address1 = 0x00100000, address2, address3, address4, address5;
		static u32 aiu, aiu1;
		static int Hex10 = 0;
		if (entry->Hotkeys[0].IsDown())
		{
			Keyboard keyboard("アドレスを入力してください。");
			if (keyboard.Open(address1, address1) != -1)
			{
				aiu = address1 / 4;
				if (aiu % 2 == 0)
				{
					Hex10 = 0;
					address1 = 4 * aiu;
				}
				else
				{
					Hex10 = 1;
					aiu1 = aiu - 1;
					address1 = 4 * aiu1;
				}
				return;
			}
		}
		if (entry->Hotkeys[1].IsDown())
		{
			Keyboard keyboard("値を入力してください。");
			if (keyboard.Open(Hex11, Hex11) != -1)
			{
				Process::Write32(address, Hex11);
				return;
			}
		}
		if (Controller::IsKeysPressed(A + DL) && Hex10 == 0)
			Hex10 = 1;
		if (Controller::IsKeysPressed(A + DR) && Hex10 == 0)
			Hex10 = 1;
		if (Controller::IsKeysPressed(A + DL) && Hex10 == 1)
			Hex10 = 0;
		if (Controller::IsKeysPressed(A + DR) && Hex10 == 1)
			Hex10 = 0;
		if (Controller::IsKeysPressed(A + DU))
			address1 -= 8;
		if (Controller::IsKeysPressed(A + DD))
			address1 += 8;
		address = address1 + (Hex10 * 4);
		address2 = address1 + 8;
		address3 = address1 + 16;
		address4 = address1 + 24;
		address5 = address1 + 32;
		Process::Read32(address1, Hex);
		Process::Read32(address1 + 4, Hex1);
		Process::Read32(address1 + 8, Hex2);
		Process::Read32(address1 + 12, Hex3);
		Process::Read32(address1 + 16, Hex4);
		Process::Read32(address1 + 20, Hex5);
		Process::Read32(address1 + 24, Hex6);
		Process::Read32(address1 + 28, Hex7);
		Process::Read32(address1 + 32, Hex8);
		Process::Read32(address1 + 36, Hex9);
		Process::Read32(address, Hex11);
		adrs_on = true;
		OSD::Run([](const Screen &screen) {
			if (!screen.IsTop)
				return (false);
			if (adrs_on == true)
			{
				screen.Draw(Utils::Format("%08X  03020100 07060504", address), 0, 0);
				screen.Draw(Utils::Format("%08X  ", address1), 0, 10);
				if (Hex10 == 0)
				{
					screen.Draw(Utils::Format("%08X ", Hex), 60, 10, Color::Yellow);
					screen.Draw(Utils::Format("%08X", Hex1), 114, 10);
				}
				if (Hex10 == 1)
				{
					screen.Draw(Utils::Format("%08X ", Hex), 60, 10);
					screen.Draw(Utils::Format("%08X", Hex1), 114, 10, Color::Yellow);
				}
				screen.Draw(Utils::Format("%08X  %08X %08X", address2, Hex2, Hex3), 0, 20);
				screen.Draw(Utils::Format("%08X  %08X %08X", address3, Hex4, Hex5), 0, 30);
				screen.Draw(Utils::Format("%08X  %08X %08X", address4, Hex6, Hex7), 0, 40);
				screen.Draw(Utils::Format("%08X  %08X %08X", address5, Hex8, Hex9), 0, 50);
				adrs_on = false;
			}
			return (true);
		});
	}

	void HexEditor2(MenuEntry *entry)
	{
		static float float1;
		static u32 hex1, hex2, hex3, hex4;
		static u32 ad1 = 0x00100000, ad2, ad3, ad4;
		static int adrs_on = 0;
		if (entry->Hotkeys[0].IsDown())
		{
			Keyboard keyboard("アドレスを入力してください。");
			if (keyboard.Open(ad1, ad1) != -1)
				;
		}
		if (entry->Hotkeys[1].IsDown())
		{
			Keyboard keyboard("値を入力してください。");
			if (keyboard.Open(hex1, hex1) != -1)
				Process::Write32(ad1, hex1);
		}
		if (Controller::IsKeysPressed(A + DU))
			ad1 -= 4;
		if (Controller::IsKeysPressed(A + DD))
			ad1 += 4;
		ad1 = ad1 + 0x0;
		ad2 = ad1 + 0x4;
		ad3 = ad1 + 0x8;
		ad4 = ad1 + 0xC;
		Process::Read32(ad1, hex1);
		Process::Read32(ad2, hex2);
		Process::Read32(ad3, hex3);
		Process::Read32(ad4, hex4);
		adrs_on = true;
		OSD::Run([](const Screen &screen) {
			if (!screen.IsTop)
				return (false);
			if (adrs_on == true)
			{
				screen.Draw(Utils::Format("%08X  03020100", ad1), 0, 0);
				screen.Draw(Utils::Format("%08X  ", ad1), 0, 10);
				screen.Draw(Utils::Format("%08X", hex1), 60, 10, Color::Yellow);
				screen.Draw(Utils::Format("%08X  %08X", ad2, hex2), 0, 20);
				screen.Draw(Utils::Format("%08X  %08X", ad3, hex3), 0, 30);
				screen.Draw(Utils::Format("%08X  %08X", ad4, hex4), 0, 40);
				adrs_on = false;
			}
			return (true);
		});
	}

	void mysetitemcopy(MenuEntry *entry)
	{
		u32 item;
		std::string myset1, myset2, myset3, myset4;
		std::string myset5, myset6, myset7, myset8;
		Process::ReadString(0x8376190, myset1, 30, StringFormat::Utf8);
		Process::ReadString(0x837623A, myset2, 30, StringFormat::Utf8);
		Process::ReadString(0x83762E4, myset3, 30, StringFormat::Utf8);
		Process::ReadString(0x837638E, myset4, 30, StringFormat::Utf8);
		Process::ReadString(0x8376438, myset5, 30, StringFormat::Utf8);
		Process::ReadString(0x83764E2, myset6, 30, StringFormat::Utf8);
		Process::ReadString(0x837658C, myset7, 30, StringFormat::Utf8);
		Process::ReadString(0x8376636, myset8, 30, StringFormat::Utf8);
		Keyboard keyboard("アイテムポーチにコピーしたいアイテムマイセットを選んでください。\n"
						  "名前の表示がおかしいのは仕様です。",
						  {myset1,
						   myset2,
						   myset3,
						   myset4,
						   myset5,
						   myset6,
						   myset7,
						   myset8});
		if (int choice = keyboard.Open() != -1)
			for (int i = 0; i < 32; i++)
			{
				Process::Read32(i * 4 + choice * 0xAA + 0x83761BA, item);
				Process::Write32(i * 4 + choice * 0xAA + 0x8372392, item);
			}
	}

	void nouhinitemcopy(MenuEntry *entry)
	{
		u16 item1, item2;
		u16 kosu1, kosu2;
		u16 itemp1, itemp2;
		Process::Read16(0x8363F98, item1);
		Process::Read16(0x8363F9C, kosu1);
		Process::Read16(0x8363FB0, item2);
		Process::Read16(0x8363FB4, kosu2);
		Process::Read16(0x8372392, itemp1);
		Process::Read16(0x8372396, itemp2);
		Keyboard keyboard("納品アイテムをアイテムポーチにコピーしますか？", {"はい",
																			 "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			if (itemp1 != 0 && itemp1 != 0)
			{
				if (MessageBox("ポーチの1番目と2番目に空きがありません。\nコピーしますか？", DialogType::DialogYesNo)())
				{
					Process::Write16(0x8372392, item1);
					Process::Write16(0x8372394, kosu1);
					Process::Write16(0x8372396, item2);
					Process::Write16(0x8372398, kosu2);
				}
			}
			else
			{
				Process::Write16(0x8372392, item1);
				Process::Write16(0x8372394, kosu1);
				Process::Write16(0x8372396, item2);
				Process::Write16(0x8372398, kosu2);
			}
		}
	}

	void nouhinitemres(MenuEntry *entry)
	{
		u16 itemp1, itemp2;
		u16 kosup1, kosup2;
		Process::Read16(0x8372392, itemp1);
		Process::Read16(0x8372394, kosup1);
		Process::Read16(0x8372396, itemp2);
		Process::Read16(0x8372398, kosup2);
		Keyboard keyboard("アイテムポーチのアイテムを納品アイテムにコピーしますか？", {"はい",
																					   "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Process::Write16(0x8363F98, itemp1);
			Process::Write16(0x8363F98, kosup1);
			Process::Write16(0x8363F98, itemp2);
			Process::Write16(0x8363F98, kosup2);
		}
	}
	void hasirustop(MenuEntry *entry)
	{
		Keyboard keyboard("走った時にムーンウォークをしますか？", {"はい",
																   "いいえ"});
		int choice = keyboard.Open();
		if (choice == 0)
			Process::Write32(0x3173C8, 0xE3A00001);
		if (choice == 1)
			Process::Write32(0x3173C8, 0xE3A00000);
	}

	void speedquebukiari(MenuEntry *entry)
	{
		float queari, quenasi;
		Keyboard keyboard("グループを選んでください。", {"クエスト中武器適応", "クエスト中武器無適応"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Keyboard keyboard("クエスト中の移動速度(武器適応)を入力してください。");
			if (keyboard.Open(queari) != -1)
				Process::WriteFloat(0x3250C8, queari);
		}
		if (choice == 1)
		{
			Keyboard keyboard("クエスト中の移動速度(武器無適応)を入力してください。");
			if (keyboard.Open(quenasi) != -1)
				Process::WriteFloat(0x338D40, quenasi);
		}
	}

	static float hunsizex = 1, hunsizey = 1, hunsizez = 1;
	void huntersizeop(MenuEntry *entry)
	{
		Process::Read32(0x8195350, offset);
		Process::ReadFloat(offset + 0x60, hunsizex);
		Process::ReadFloat(offset + 0x64, hunsizey);
		Process::ReadFloat(offset + 0x68, hunsizez);
		Keyboard keyboard("グループを選んでください。", {"X倍率", "Y倍率", "Z倍率", "一括変更"});
		int choice = keyboard.Open();
		if (choice == 0)
		{
			Keyboard keyboard(Utils::Format("X倍率を入力してください。\n現在X[%f]", hunsizex));
			if (keyboard.Open(hunsizex) != -1)
				;
		}
		if (choice == 1)
		{
			Keyboard keyboard(Utils::Format("Y倍率を入力してください。\n現在Y[%f]", hunsizey));
			if (keyboard.Open(hunsizey) != -1)
				;
		}
		if (choice == 2)
		{
			Keyboard keyboard(Utils::Format("Z倍率を入力してください。\n現在Z[%f]", hunsizez));
			if (keyboard.Open(hunsizez) != -1)
				;
		}
		if (choice == 3)
		{
			Keyboard keyboard(Utils::Format("倍率を入力してください。\n現在\nX[%f]\nY[%f]\nZ[%f]", hunsizex, hunsizey, hunsizez));
			if (keyboard.Open(hunsizex) != -1)
			{
				hunsizey = hunsizex;
				hunsizez = hunsizex;
			}
		}
	}

	void huntersize(MenuEntry *entry)
	{
		Process::Read32(0x8195350, offset);
		Process::WriteFloat(offset + 0x60, hunsizex);
		Process::WriteFloat(offset + 0x64, hunsizey);
		Process::WriteFloat(offset + 0x68, hunsizez);
	}

	void Fpschange(MenuEntry *entry){
		float fps;
		Keyboard key("最大FPSを入力してください。");
		key.Open(fps);
		Process::WriteFloat(0x87E24E0, fps);
	}

	void Syokuji_Flag_Mugen(MenuEntry *entry){
		Process::Write8(0x8480827, 0);
	}

	void Syokuji_Flag_Osyokujiken(MenuEntry *entry){
		Process::Write8(0x8480825, 2);
		Process::Write8(0x8480826, 2);
	}

	void Syokuji_Flag_Nikuirai(MenuEntry *entry){
		Process::Write8(0x8480925, 0);
	}

	void Syokuji_Status_Hp(MenuEntry *entry){
		Process::Write8(0x83A6E68, 127);
	}

	void Syokuji_Status_Stamina(MenuEntry *entry){
		Process::Write8(0x83A6E69, 127);
	}

	void Syokuji_Status_Attack(MenuEntry *entry){
		Process::Write8(0x83A6E6A, 127);
	}

	void Syokuji_Status_Defence(MenuEntry *entry){
		Process::Write8(0x83A6E6B, 127);
	}

	void Syokuji_Status_Taisei_Hi(MenuEntry *entry){
		Process::Write8(0x83A6E6C, 127);
	}

	void Syokuji_Status_Taisei_Mizu(MenuEntry *entry){
		Process::Write8(0x83A6E6D, 127);
	}

	void Syokuji_Status_Taisei_Kaminari(MenuEntry *entry){
		Process::Write8(0x83A6E6E, 127);
	}

	void Syokuji_Status_Taisei_Koori(MenuEntry *entry){
		Process::Write8(0x83A6E6F, 127);
	}

	void Syokuji_Status_Taisei_Ryu(MenuEntry *entry){
		Process::Write8(0x83A6E70, 127);
	}

	void Syokuji_Skill_1(MenuEntry *entry){
		Keyboard key("スキルを選択してください。", {"なし", "ネコの解体術【大】", "ネコの解体術【小】", "ネコの医療術", "ネコの体術", "ネコの火薬術", "ネコの特殊攻撃術", "ネコの防御術【大】", "ネコの防御術【小】", "ネコの吹奏術", "ネコの道具倹約術", "ネコのカリスマ", "ネコの調合術【大】", "ネコの調合術【小】", "ネコの採取術", "ネコの射撃術", "招きネコの激運", "招きネコの幸運", "ネコの火事場力", "ネコのはじかれ上手", "ネコの逃走術", "ネコの投擲術", "ネコの胆力", "ネコの運搬の超人", "ネコの運搬の鉄人", "ネコの弱いの来い！", "ネコの秘境探索術", "ネコの換算術", "ネコの起き上り術【大】", "ネコの起き上り術【小】", "ネコの暴れ撃ち", "ネコの蹴脚術", "ネコの拳闘術", "ネコのはりつき超人", "ネコのはりつき鉄人", "ネコの解体の鉄人", "ネコの着地術", "ネコの休憩術", "ネコのゴリ押し術", "ネコのおまけ術", "ネコのKO術", "招きネコの金運", "ネコの砲撃術", "ネコのド根性", "ネコのこやし玉達人", "ネコの毛づくろい上手", "ネコの長靴術", "ネコのすり抜け術", "ネコの千里眼の術", "ネコの研磨術", "ネコの受け身術", "ネコのかかってこい", "ネコのオトモ指導術", "ネコの短期催眠術", "ネコの手配上手", "ネコの不眠術", "ネコのふんばり術", "ネコの釣り上手", "招きネコの悪運", "ネコの乗り上手", "ネコの乗り支援術", "ネコの報酬金保険", "ネコの憎まれ上手"});
		int choice = key.Open();
		if(choice != -1)
			Process::Write8(0x83A6E71, choice);
	}

	void Syokuji_Skill_2(MenuEntry *entry){
		Keyboard key("スキルを選択してください。", {"なし", "ネコの解体術【大】", "ネコの解体術【小】", "ネコの医療術", "ネコの体術", "ネコの火薬術", "ネコの特殊攻撃術", "ネコの防御術【大】", "ネコの防御術【小】", "ネコの吹奏術", "ネコの道具倹約術", "ネコのカリスマ", "ネコの調合術【大】", "ネコの調合術【小】", "ネコの採取術", "ネコの射撃術", "招きネコの激運", "招きネコの幸運", "ネコの火事場力", "ネコのはじかれ上手", "ネコの逃走術", "ネコの投擲術", "ネコの胆力", "ネコの運搬の超人", "ネコの運搬の鉄人", "ネコの弱いの来い！", "ネコの秘境探索術", "ネコの換算術", "ネコの起き上り術【大】", "ネコの起き上り術【小】", "ネコの暴れ撃ち", "ネコの蹴脚術", "ネコの拳闘術", "ネコのはりつき超人", "ネコのはりつき鉄人", "ネコの解体の鉄人", "ネコの着地術", "ネコの休憩術", "ネコのゴリ押し術", "ネコのおまけ術", "ネコのKO術", "招きネコの金運", "ネコの砲撃術", "ネコのド根性", "ネコのこやし玉達人", "ネコの毛づくろい上手", "ネコの長靴術", "ネコのすり抜け術", "ネコの千里眼の術", "ネコの研磨術", "ネコの受け身術", "ネコのかかってこい", "ネコのオトモ指導術", "ネコの短期催眠術", "ネコの手配上手", "ネコの不眠術", "ネコのふんばり術", "ネコの釣り上手", "招きネコの悪運", "ネコの乗り上手", "ネコの乗り支援術", "ネコの報酬金保険", "ネコの憎まれ上手"});
		int choice = key.Open();
		if(choice != -1)
			Process::Write8(0x83A6E72, choice);
	}

	void Syokuji_Skill_3(MenuEntry *entry){
		Keyboard key("スキルを選択してください。", {"なし", "ネコの解体術【大】", "ネコの解体術【小】", "ネコの医療術", "ネコの体術", "ネコの火薬術", "ネコの特殊攻撃術", "ネコの防御術【大】", "ネコの防御術【小】", "ネコの吹奏術", "ネコの道具倹約術", "ネコのカリスマ", "ネコの調合術【大】", "ネコの調合術【小】", "ネコの採取術", "ネコの射撃術", "招きネコの激運", "招きネコの幸運", "ネコの火事場力", "ネコのはじかれ上手", "ネコの逃走術", "ネコの投擲術", "ネコの胆力", "ネコの運搬の超人", "ネコの運搬の鉄人", "ネコの弱いの来い！", "ネコの秘境探索術", "ネコの換算術", "ネコの起き上り術【大】", "ネコの起き上り術【小】", "ネコの暴れ撃ち", "ネコの蹴脚術", "ネコの拳闘術", "ネコのはりつき超人", "ネコのはりつき鉄人", "ネコの解体の鉄人", "ネコの着地術", "ネコの休憩術", "ネコのゴリ押し術", "ネコのおまけ術", "ネコのKO術", "招きネコの金運", "ネコの砲撃術", "ネコのド根性", "ネコのこやし玉達人", "ネコの毛づくろい上手", "ネコの長靴術", "ネコのすり抜け術", "ネコの千里眼の術", "ネコの研磨術", "ネコの受け身術", "ネコのかかってこい", "ネコのオトモ指導術", "ネコの短期催眠術", "ネコの手配上手", "ネコの不眠術", "ネコのふんばり術", "ネコの釣り上手", "招きネコの悪運", "ネコの乗り上手", "ネコの乗り支援術", "ネコの報酬金保険", "ネコの憎まれ上手"});
		int choice = key.Open();
		if(choice != -1)
			Process::Write8(0x83A6E73, choice);
	}

	void Teleport(MenuEntry *entry){
		float x, y, z;
		Process::Read32(0x8195350, offset);

		if(Controller::IsKeysDown(X + DR)){
			Process::ReadFloat(offset + 0x40, x);
			Process::ReadFloat(offset + 0x44, y);
			Process::ReadFloat(offset + 0x48, z);
		}

		if(Controller::IsKeysDown(X + DL)){
			Process::WriteFloat(offset + 0x40, x);
			Process::WriteFloat(offset + 0x44, y);
			Process::WriteFloat(offset + 0x48, z);
		}
	}
}