#include "common.hpp"

namespace CTRPluginFramework{
	static StringVector info;

	static const std::vector<Item> g_info =
	{
		{"タイトルID"},
		{"3DSのタイプ"},
		{"Wi-Fi接続確認"}
	};

	void TitleID(void){
		std::string tid;
		Process::GetTitleID(tid);
		MessageBox("タイトルIDは " + tid + " です。")();
	}

	void ConsoleType(void){
		switch (System::IsNew3DS()){
			case 0:
				MessageBox("Old3DSです。")();
				break;
			case 1:
				MessageBox("New3DSです。")();
				break;
		}
	}

	void WiFiStatus(void){
		switch (System::IsConnectedToInternet()){
			case 0:
				MessageBox("WiFiに接続されていません。")();
				break;
			case 1:
				MessageBox("WiFiに接続されています。")();
				break;
		}
	}

	void Information(MenuEntry *entry){
		if(info.empty()){
			for (const Item &i : g_info)
				info.push_back(i.name);
		}
		Keyboard keyboard("確認したい情報を選んでください。", info);
		int choice = keyboard.Open();

		switch (choice){
			case 0:
				TitleID();
				break;
			case 1:
				ConsoleType();
				break;
			case 2:
				WiFiStatus();
				break;
		}
	}

	void HexToDecd32(MenuEntry *entry){
		u32 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応しています。\n例:FFFFFFFF = -1");
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%d" " です。", out))());
	}

	void HexToDecu32(MenuEntry *entry){
		u32 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応していません。\n例:FFFFFFFF = 4294967295");
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%u" " です。", out))());
	}

	void HexToDecd16(MenuEntry *entry){
		u16 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応しています。\n例:FFFF = -1");
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%d" " です。", out))());
	}

	void HexToDecu16(MenuEntry *entry){
		u16 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応していません。\n例:FFFF = 65535");
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%u" " です。", out))());
	}

	void HexToDecd8(MenuEntry *entry){
		u8 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応しています。\n例:FF = -1");
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%d" " です。", out))());
	}

	void HexToDecu8(MenuEntry *entry){
		u8 out;
		Keyboard keyboard("16進数を入力してください。\n-に対応していません。\n例:FF = 255");
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%u" " です。", out))());
	}

	void DecToHex(MenuEntry *entry){
		u32 out;
		Keyboard keyboard("10進数を入力してください。");
		keyboard.IsHexadecimal(false);
		keyboard.Open(out);
		(MessageBox(Utils::Format("結果は " "%X" " です。", out))());
	}

	void pointermode(MenuEntry *entry){

	}

	void pointer1(MenuEntry *entry){

	}

	void pointer2(MenuEntry *entry){

	}

	void pointer3(MenuEntry *entry){

	}

	void pointer4(MenuEntry *entry){

	}
}