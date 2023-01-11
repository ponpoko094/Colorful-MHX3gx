#include "libpon/keyboard_plus.hpp"

namespace CTRPluginFramework {

Keyboard* KB = new Keyboard("ダミー");
Keyboard* OptionsKB = new Keyboard("ダミー");
const StringVector kListToggle{"はい", "いいえ"};

bool KeyboardPlus::Set(u32& input, const std::string& message,
                       bool hexadecimal) {
  KB->GetMessage() = message;
  KB->IsHexadecimal(hexadecimal);
  if (KB->Open(input, input) != -1) {
    return (true);
  }
  return (false);
}

bool KeyboardPlus::Set(u16& input, const std::string& message,
                       bool hexadecimal) {
  KB->GetMessage() = message;
  KB->IsHexadecimal(hexadecimal);
  if (KB->Open(input, input) != -1) {
    return (true);
  }
  return (false);
}

bool KeyboardPlus::Set(u8& input, const std::string& message,
                       bool hexadecimal) {
  KB->GetMessage() = message;
  KB->IsHexadecimal(hexadecimal);
  if (KB->Open(input, input) != -1) {
    return (true);
  }
  return (false);
}

bool KeyboardPlus::Toggle32(const std::string& message, const u32& offset,
                            const u32& enable, const u32& disable) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(kListToggle);
  const int kChoice = OptionsKB->Open();
  switch (kChoice) {
    case 0:
      Process::Write32(offset, enable);
      break;
    case 1:
      Process::Write32(offset, disable);
      break;
    default:
      break;
  }
  return kChoice != 0;
}

bool KeyboardPlus::Toggle16(const std::string& message, const u32& offset,
                            const u16& enable, const u16& disable) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(kListToggle);
  const int kChoice = OptionsKB->Open();
  switch (kChoice) {
    case 0:
      Process::Write16(offset, enable);
      break;
    case 1:
      Process::Write16(offset, disable);
      break;
    default:
      break;
  }
  return kChoice != 0;
}

bool KeyboardPlus::Toggle8(const std::string& message, const u32& offset,
                           const u8& enable, const u8& disable) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(kListToggle);
  const int kChoice = OptionsKB->Open();
  switch (kChoice) {
    case 0:
      Process::Write8(offset, enable);
      break;
    case 1:
      Process::Write8(offset, disable);
      break;
    default:
      break;
  }
  return kChoice != 0;
}

bool KeyboardPlus::MultiToggle32(const std::string& message,
                                 std::vector<std::vector<u32>> value) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(kListToggle);
  const int kChoice = OptionsKB->Open();
  if (kChoice == -1) {
    return false;
  }
  for (auto& i : value) {
    Process::Write32(i.at(0), i.at(1 + kChoice));
  }
  return kChoice != 0;
}

bool KeyboardPlus::LengthToggle32(const std::string& message, const int length,
                                  u32 base_address, std::vector<u32> value) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(kListToggle);
  const int kChoice = OptionsKB->Open();
  switch (kChoice) {
    case 0:
      for (int i = 0; i < length; i++) {
        Process::Write32(base_address + i * 0x4, value[i]);
      }
      break;
    case 1:
      for (int i = 0; i < length; i++) {
        Process::Write32(base_address + i * 0x4, 0);
      }
    default:
      break;
  }
  return kChoice != 0;
}

KeyboardPlus::~KeyboardPlus() {
  delete KB;
  delete OptionsKB;
}

}  // namespace CTRPluginFramework
