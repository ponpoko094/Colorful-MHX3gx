namespace CTRPluginFramework{
	//変換候補変換
	void	Chathenkan(MenuEntry *entry){
		u32 a, b, c, aa, bb, cc, aaa, bbb, ccc;
		std::string moji1, moji2, moji3;
		aa = a + 0x18; aaa = a = 0xF8;
		bb = b + 0x18; bbb = b + 0xF8;
		cc = c + 0x18; ccc = c + 0xF8;
		Process::Read32(0x878CF80, a);
		Process::Read32(0x8790F80, b);
		Process::Read32(0x8791F80, c);
		Process::ReadString(aa, moji1, 12, StringFormat::Utf16);
		Process::ReadString(bb, moji2, 12, StringFormat::Utf16);
		Process::ReadString(cc, moji3, 12, StringFormat::Utf16);
		if (Controller::IsKeysDown(R)){
			if(moji1 == "るーと") 	Process::WriteString(aaa, "√", StringFormat::Utf16);
			if(moji2 == "るーと") 	Process::WriteString(bbb, "√", StringFormat::Utf16);
			if(moji3 == "るーと") 	Process::WriteString(ccc, "√", StringFormat::Utf16);
			if(moji1 == "まるいち") Process::WriteString(aaa, "①", StringFormat::Utf16);
			if(moji2 == "まるいち") Process::WriteString(bbb, "①", StringFormat::Utf16);
			if(moji3 == "まるいち") Process::WriteString(ccc, "①", StringFormat::Utf16);
			if(moji1 == "まるに") Process::WriteString(aaa, "②", StringFormat::Utf16);
			if(moji2 == "まるに") Process::WriteString(bbb, "②", StringFormat::Utf16);
			if(moji3 == "まるに") Process::WriteString(ccc, "②", StringFormat::Utf16);
			if(moji1 == "まるさん") Process::WriteString(aaa, "③", StringFormat::Utf16);
			if(moji2 == "まるさん") Process::WriteString(bbb, "③", StringFormat::Utf16);
			if(moji3 == "まるさん") Process::WriteString(ccc, "③", StringFormat::Utf16);
			if(moji1 == "まるよん") Process::WriteString(aaa, "④", StringFormat::Utf16);
			if(moji2 == "まるよん") Process::WriteString(bbb, "④", StringFormat::Utf16);
			if(moji3 == "まるよん") Process::WriteString(ccc, "④", StringFormat::Utf16);
			if(moji1 == "まるご") Process::WriteString(aaa, "⑤", StringFormat::Utf16);
			if(moji2 == "まるご") Process::WriteString(bbb, "⑤", StringFormat::Utf16);
			if(moji3 == "まるご") Process::WriteString(ccc, "⑤", StringFormat::Utf16);
			if(moji1 == "まるろく") Process::WriteString(aaa, "⑥", StringFormat::Utf16);
			if(moji2 == "まるろく") Process::WriteString(bbb, "⑥", StringFormat::Utf16);
			if(moji3 == "まるろく") Process::WriteString(ccc, "⑥", StringFormat::Utf16);
			if(moji1 == "まるなな") Process::WriteString(aaa, "⑦", StringFormat::Utf16);
			if(moji2 == "まるなな") Process::WriteString(bbb, "⑦", StringFormat::Utf16);
			if(moji3 == "まるなな") Process::WriteString(ccc, "⑦", StringFormat::Utf16);
			if(moji1 == "まるはち") Process::WriteString(aaa, "⑧", StringFormat::Utf16);
			if(moji2 == "まるはち") Process::WriteString(bbb, "⑧", StringFormat::Utf16);
			if(moji3 == "まるはち")	Process::WriteString(ccc, "⑧", StringFormat::Utf16);
			if(moji1 == "まるきゅう") Process::WriteString(aaa, "⑨", StringFormat::Utf16);
			if(moji2 == "まるきゅう") Process::WriteString(bbb, "⑨", StringFormat::Utf16);
			if(moji3 == "まるきゅう") Process::WriteString(ccc, "⑨", StringFormat::Utf16);
			if(moji1 == "えす") Process::WriteString(aaa, "∫", StringFormat::Utf16);
			if(moji2 == "えす") Process::WriteString(bbb, "∫", StringFormat::Utf16);
			if(moji3 == "えす") Process::WriteString(ccc, "∫", StringFormat::Utf16);
			if(moji1 == "だぶるえす") Process::WriteString(aaa, "∬", StringFormat::Utf16);
			if(moji2 == "だぶるえす") Process::WriteString(bbb, "∬", StringFormat::Utf16);
			if(moji3 == "だぶるえす") Process::WriteString(ccc, "∬", StringFormat::Utf16);
			if(moji1 == "ろーまいち") Process::WriteString(aaa, "Ⅰ", StringFormat::Utf16);
			if(moji2 == "ろーまいち") Process::WriteString(bbb, "Ⅰ", StringFormat::Utf16);
			if(moji3 == "ろーまいち") Process::WriteString(ccc, "Ⅰ", StringFormat::Utf16);
			if(moji1 == "ろーまに") Process::WriteString(aaa, "Ⅱ", StringFormat::Utf16);
			if(moji2 == "ろーまに") Process::WriteString(bbb, "Ⅱ", StringFormat::Utf16);
			if(moji3 == "ろーまに") Process::WriteString(ccc, "Ⅱ", StringFormat::Utf16);
			if(moji1 == "ろーまさん") Process::WriteString(aaa, "Ⅲ", StringFormat::Utf16);
			if(moji2 == "ろーまさん") Process::WriteString(bbb, "Ⅲ", StringFormat::Utf16);
			if(moji3 == "ろーまさん") Process::WriteString(ccc, "Ⅲ", StringFormat::Utf16);
			if(moji1 == "ろーまよん") Process::WriteString(aaa, "Ⅳ", StringFormat::Utf16);
			if(moji2 == "ろーまよん") Process::WriteString(bbb, "Ⅳ", StringFormat::Utf16);
			if(moji3 == "ろーまよん") Process::WriteString(ccc, "Ⅳ", StringFormat::Utf16);
			if(moji1 == "ろーまご") Process::WriteString(aaa, "Ⅴ", StringFormat::Utf16);
			if(moji2 == "ろーまご") Process::WriteString(bbb, "Ⅴ", StringFormat::Utf16);
			if(moji3 == "ろーまご") Process::WriteString(ccc, "Ⅴ", StringFormat::Utf16);
			if(moji1 == "ろーまろく") Process::WriteString(aaa, "Ⅵ", StringFormat::Utf16);
			if(moji2 == "ろーまろく") Process::WriteString(bbb, "Ⅵ", StringFormat::Utf16);
			if(moji3 == "ろーまろく") Process::WriteString(ccc, "Ⅵ", StringFormat::Utf16);
			if(moji1 == "ろーまなな") Process::WriteString(aaa, "Ⅶ", StringFormat::Utf16);
			if(moji2 == "ろーまなな") Process::WriteString(bbb, "Ⅶ", StringFormat::Utf16);
			if(moji3 == "ろーまなな") Process::WriteString(ccc, "Ⅶ", StringFormat::Utf16);
			if(moji1 == "ろーまはち") Process::WriteString(aaa, "Ⅷ", StringFormat::Utf16);
			if(moji2 == "ろーまはち") Process::WriteString(bbb, "Ⅷ", StringFormat::Utf16);
			if(moji3 == "ろーまはち") Process::WriteString(ccc, "Ⅷ", StringFormat::Utf16);
			if(moji1 == "ろーまきゅう") Process::WriteString(aaa, "Ⅸ", StringFormat::Utf16);
			if(moji2 == "ろーまきゅう") Process::WriteString(bbb, "Ⅸ", StringFormat::Utf16);
			if(moji3 == "ろーまきゅう") Process::WriteString(ccc, "Ⅸ", StringFormat::Utf16);
			if(moji1 == "ろーまじゅう") Process::WriteString(aaa, "Ⅹ", StringFormat::Utf16);
			if(moji2 == "ろーまじゅう") Process::WriteString(bbb, "Ⅹ", StringFormat::Utf16);
			if(moji3 == "ろーまじゅう") Process::WriteString(ccc, "Ⅹ", StringFormat::Utf16);
			if(moji1 == "みり") Process::WriteString(aaa, "㍉", StringFormat::Utf16);
			if(moji2 == "みり") Process::WriteString(bbb, "㍉", StringFormat::Utf16);
			if(moji3 == "みり") Process::WriteString(ccc, "㍉", StringFormat::Utf16);
			if(moji1 == "きろ") Process::WriteString(aaa, "㌔", StringFormat::Utf16);
			if(moji2 == "きろ") Process::WriteString(bbb, "㌔", StringFormat::Utf16);
			if(moji3 == "きろ") Process::WriteString(ccc, "㌔", StringFormat::Utf16);
			if(moji1 == "せんち") Process::WriteString(aaa, "㌢", StringFormat::Utf16);
			if(moji2 == "せんち") Process::WriteString(bbb, "㌢", StringFormat::Utf16);
			if(moji3 == "せんち") Process::WriteString(ccc, "㌢", StringFormat::Utf16);
			if(moji1 == "めーとる") Process::WriteString(aaa, "㍍", StringFormat::Utf16);
			if(moji2 == "めーとる") Process::WriteString(bbb, "㍍", StringFormat::Utf16);
			if(moji3 == "めーとる") Process::WriteString(ccc, "㍍", StringFormat::Utf16);
			if(moji1 == "ぐらむ") Process::WriteString(aaa, "㌘", StringFormat::Utf16);
			if(moji2 == "ぐらむ") Process::WriteString(bbb, "㌘", StringFormat::Utf16);
			if(moji3 == "ぐらむ") Process::WriteString(ccc, "㌘", StringFormat::Utf16);
			if(moji1 == "とん") Process::WriteString(aaa, "㌧", StringFormat::Utf16);
			if(moji2 == "とん") Process::WriteString(bbb, "㌧", StringFormat::Utf16);
			if(moji3 == "とん") Process::WriteString(ccc, "㌧", StringFormat::Utf16);
			if(moji1 == "あーる") Process::WriteString(aaa, "㌃", StringFormat::Utf16);
			if(moji2 == "あーる") Process::WriteString(bbb, "㌃", StringFormat::Utf16);
			if(moji3 == "あーる") Process::WriteString(ccc, "㌃", StringFormat::Utf16);
			if(moji1 == "へくたーる") Process::WriteString(aaa, "㌶", StringFormat::Utf16);
			if(moji2 == "へくたーる") Process::WriteString(bbb, "㌶", StringFormat::Utf16);
			if(moji3 == "へくたーる") Process::WriteString(ccc, "㌶", StringFormat::Utf16);
			if(moji1 == "りっとる") Process::WriteString(aaa, "㍑", StringFormat::Utf16);
			if(moji2 == "りっとる") Process::WriteString(bbb, "㍑", StringFormat::Utf16);
			if(moji3 == "りっとる") Process::WriteString(ccc, "㍑", StringFormat::Utf16);
			if(moji1 == "わっと") Process::WriteString(aaa, "㍗", StringFormat::Utf16);
			if(moji2 == "わっと") Process::WriteString(bbb, "㍗", StringFormat::Utf16);
			if(moji3 == "わっと") Process::WriteString(ccc, "㍗", StringFormat::Utf16);
			if(moji1 == "かろりー") Process::WriteString(aaa, "㌍", StringFormat::Utf16);
			if(moji2 == "かろりー") Process::WriteString(bbb, "㌍", StringFormat::Utf16);
			if(moji3 == "かろりー") Process::WriteString(ccc, "㌍", StringFormat::Utf16);
			if(moji1 == "どる") Process::WriteString(aaa, "㌦", StringFormat::Utf16);
			if(moji2 == "どる") Process::WriteString(bbb, "㌦", StringFormat::Utf16);
			if(moji3 == "どる") Process::WriteString(ccc, "㌦", StringFormat::Utf16);
			if(moji1 == "せんと") Process::WriteString(aaa, "㌣", StringFormat::Utf16);
			if(moji2 == "せんと") Process::WriteString(bbb, "㌣", StringFormat::Utf16);
			if(moji3 == "せんと") Process::WriteString(ccc, "㌣", StringFormat::Utf16);
			if(moji1 == "ぱーせんと") Process::WriteString(aaa, "㌫", StringFormat::Utf16);
			if(moji2 == "ぱーせんと") Process::WriteString(bbb, "㌫", StringFormat::Utf16);
			if(moji3 == "ぱーせんと") Process::WriteString(ccc, "㌫", StringFormat::Utf16);
			if(moji1 == "みりばーる") Process::WriteString(aaa, "㍊", StringFormat::Utf16);
			if(moji2 == "みりばーる") Process::WriteString(bbb, "㍊", StringFormat::Utf16);
			if(moji3 == "みりばーる") Process::WriteString(ccc, "㍊", StringFormat::Utf16);
			if(moji1 == "ぺーじ") Process::WriteString(aaa, "㌻", StringFormat::Utf16);
			if(moji2 == "ぺーじ") Process::WriteString(bbb, "㌻", StringFormat::Utf16);
			if(moji3 == "ぺーじ") Process::WriteString(ccc, "㌻", StringFormat::Utf16);
			if(moji1 == "へいせい") Process::WriteString(aaa, "㍻", StringFormat::Utf16);
			if(moji2 == "へいせい") Process::WriteString(bbb, "㍻", StringFormat::Utf16);
			if(moji3 == "へいせい") Process::WriteString(ccc, "㍻", StringFormat::Utf16);
			if(moji1 == "しょうわ") Process::WriteString(aaa, "㍼", StringFormat::Utf16);
			if(moji2 == "しょうわ") Process::WriteString(bbb, "㍼", StringFormat::Utf16);
			if(moji3 == "しょうわ") Process::WriteString(ccc, "㍼", StringFormat::Utf16);
			if(moji1 == "たいしょう") Process::WriteString(aaa, "㍽", StringFormat::Utf16);
			if(moji2 == "たいしょう") Process::WriteString(bbb, "㍽", StringFormat::Utf16);
			if(moji3 == "たいしょう") Process::WriteString(ccc, "㍽", StringFormat::Utf16);
			if(moji1 == "めいじ") Process::WriteString(aaa, "㍾", StringFormat::Utf16);
			if(moji2 == "めいじ") Process::WriteString(bbb, "㍾", StringFormat::Utf16);
			if(moji3 == "めいじ") Process::WriteString(ccc, "㍾", StringFormat::Utf16);
			if(moji1 == "なんばー") Process::WriteString(aaa, "№", StringFormat::Utf16);
			if(moji2 == "なんばー") Process::WriteString(bbb, "№", StringFormat::Utf16);
			if(moji3 == "なんばー") Process::WriteString(ccc, "№", StringFormat::Utf16);
			if(moji1 == "けーけー") Process::WriteString(aaa, "㏍", StringFormat::Utf16);
			if(moji2 == "けーけー") Process::WriteString(bbb, "㏍", StringFormat::Utf16);
			if(moji3 == "けーけー") Process::WriteString(ccc, "㏍", StringFormat::Utf16);
			if(moji1 == "てる") Process::WriteString(aaa, "℡", StringFormat::Utf16);
			if(moji2 == "てる") Process::WriteString(bbb, "℡", StringFormat::Utf16);
			if(moji3 == "てる") Process::WriteString(ccc, "℡", StringFormat::Utf16);
			if(moji1 == "たぶ") Process::WriteString(aaa, "\t", StringFormat::Utf16);
			if(moji2 == "たぶ") Process::WriteString(bbb, "\t", StringFormat::Utf16);
			if(moji3 == "たぶ") Process::WriteString(ccc, "\t", StringFormat::Utf16);
			if(moji1 == "かいぎょう") Process::WriteString(aaa, "\n", StringFormat::Utf16);
			if(moji2 == "かいぎょう") Process::WriteString(bbb, "\n", StringFormat::Utf16);
			if(moji3 == "かいぎょう") Process::WriteString(ccc, "\n", StringFormat::Utf16);
			if(moji1 == "こう") Process::WriteString(aaa, "爻", StringFormat::Utf16);
			if(moji2 == "こう") Process::WriteString(bbb, "爻", StringFormat::Utf16);
			if(moji3 == "こう") Process::WriteString(ccc, "爻", StringFormat::Utf16);
		}
	}

	//変換候補変換可能文字一覧
	void	henkanitiran(MenuEntry *entry){
		Keyboard keyboard("変換候補変換可能文字一覧です。\n"
		"(数字)と書かれている所は、いち、に、等の数字を書いてください。\n"
		"(単位)と書かれている所は、きろ、や、めーとる、等の単位を書いてください。\n"
		"(元号)と書かれている所は、へいせい、や、しょうわ、等の元号を書いてください。\n"
		"改行はキーボード上では表示されますが、チャットログだと空白が表示されます。\n"
		"一部変換できない文字があります。",
		{	"るーと √",
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

		int choice = keyboard.Open();
    }
/*
			if(moji1 == "") Process::WriteString(aa, "", StringFormat::Utf16);
			if(moji2 == "") Process::WriteString(bb, "", StringFormat::Utf16);
			if(moji3 == "") Process::WriteString(cc, "", StringFormat::Utf16);
*/
}