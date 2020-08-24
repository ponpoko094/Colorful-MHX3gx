//Passwords
		static bool file = false;
		if(!file){
		    if(!File::Exists("ponpoko.bin")){
			    Keyboard    key(""<< Color::Yellow <<"Enter your password");
				std::string str;
				key.Open(str);
				if(str !="ponpoko"){
				    (MessageBox(""<< Color::Magenta <<"Error:Passwords do not match")());
					bool select = (MessageBox(""<< Color::Magenta <<"Stop the 3gx", DialogType::DialogYesNo)());;
					if(!select){
					    (MessageBox(""<< Color::Red <<"You are script kiddy.\nDon't come back.")());
					}
				    abort();
				}
				else{
				    (MessageBox(""<< Color::Green <<"Password authentication.\nReboot for settings to take effect.")());
					File::Create("ponpoko.bin");
					abort();
				}
			}
			file = true;
		}
