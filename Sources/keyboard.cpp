#include "Keyboard.hpp"

namespace CTRPluginFramework {
Keyboard* KB = new Keyboard("ダミー");
Keyboard* OptionsKB = new Keyboard("ダミー");

bool KBD::Set(const std::string message, bool hexadecimal, const int length, u32 output, u32 define) {
    KB->GetMessage() = message;
    KB->IsHexadecimal(hexadecimal);
    KB->SetMaxLength(length);
    return KB->Open(output, define) == 0;
    KBD::Clean();
}

bool KBD::Set(const std::string message, bool hexadecimal, const int length, u16 output, u16 define) {
    KB->GetMessage() = message;
    KB->IsHexadecimal(hexadecimal);
    KB->SetMaxLength(length);
    return KB->Open(output, define) == 0;
    KBD::Clean();
}

bool KBD::Set(const std::string message, bool hexadecimal, const int length, u8 output, u8 define) {
    KB->GetMessage() = message;
    KB->IsHexadecimal(hexadecimal);
    KB->SetMaxLength(length);
    return KB->Open(output, define) == 0;
    KBD::Clean();
}

void KBD::Toggle32(const std::string message, u32 offset, u32 enable, u32 disable) {
    StringVector listToggle{"はい", "いいえ"};

    OptionsKB->GetMessage() = message;
    OptionsKB->Populate(listToggle);
    switch (OptionsKB->Open()) {
        case -1:
            break;
        case 0:
            Process::Write32(offset, enable);
            break;
        case 1:
            Process::Write32(offset, disable);
            break;
    }
    KBD::Clean();
}

void KBD::Toggle16(const std::string message, u32 offset, u16 enable, u16 disable) {
    StringVector listToggle{"はい", "いいえ"};

    OptionsKB->GetMessage() = message;
    OptionsKB->Populate(listToggle);
    switch (OptionsKB->Open()) {
        case -1:
            break;
        case 0:
            Process::Write16(offset, enable);
            break;
        case 1:
            Process::Write16(offset, disable);
            break;
    }
    KBD::Clean();
}

void KBD::Toggle8(const std::string message, u32 offset, u8 enable, u8 disable) {
    StringVector listToggle{"はい", "いいえ"};

    OptionsKB->GetMessage() = message;
    OptionsKB->Populate(listToggle);
    switch (OptionsKB->Open()) {
        case -1:
            break;
        case 0:
            Process::Write8(offset, enable);
            break;
        case 1:
            Process::Write8(offset, disable);
            break;
    }
    KBD::Clean();
}

void KBD::SToggle32(const std::string message, std::vector<std::vector<u32>> value) {
    StringVector listToggle{"はい", "いいえ"};

    OptionsKB->GetMessage() = message;
    OptionsKB->Populate(listToggle);
    switch (OptionsKB->Open()) {
        case -1:
            break;
        case 0:
            for (int i = 0; i < value.size(); i++) {
                Process::Write32(value[i][0], value[i][1]);
            }
            break;
        case 1:
            for (int i = 0; i < value.size(); i++) {
                Process::Write32(value[i][0], value[i][2]);
            }
            break;
    }
    KBD::Clean();
}

void KBD::Clean() {
    delete KB;
    delete OptionsKB;
};
}  // namespace CTRPluginFramework