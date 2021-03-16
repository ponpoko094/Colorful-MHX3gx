#include "keyboard.h"

namespace CTRPluginFramework {

Keyboard* KB = new Keyboard("ダミー");
Keyboard* OptionsKB = new Keyboard("ダミー");
const StringVector listToggle{"はい", "いいえ"};

int KBD::Set(const std::string message, bool hexadecimal, const int length,
             u32 output) {
  KB->GetMessage() = message;
  KB->IsHexadecimal(hexadecimal);
  KB->SetMaxLength(length);
  return KB->Open(output, output);
}

int KBD::Set(const std::string message, bool hexadecimal, const int length,
             u16 output) {
  KB->GetMessage() = message;
  KB->IsHexadecimal(hexadecimal);
  KB->SetMaxLength(length);
  return KB->Open(output, output);
}

int KBD::Set(const std::string message, bool hexadecimal, const int length,
             u8 output) {
  KB->GetMessage() = message;
  KB->IsHexadecimal(hexadecimal);
  KB->SetMaxLength(length);
  return KB->Open(output, output);
}

int KBD::Toggle32(const std::string message, u32 offset, u32 enable,
                  u32 disable) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(listToggle);
  int choice = OptionsKB->Open();
  switch (choice) {
    case -1:
      break;
    case 0:
      Process::Write32(offset, enable);
      break;
    case 1:
      Process::Write32(offset, disable);
      break;
  }
  return choice;
}

int KBD::Toggle16(const std::string message, u32 offset, u16 enable,
                  u16 disable) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(listToggle);
  int choice = OptionsKB->Open();
  switch (choice) {
    case -1:
      break;
    case 0:
      Process::Write16(offset, enable);
      break;
    case 1:
      Process::Write16(offset, disable);
      break;
  }
  return choice;
}

int KBD::Toggle8(const std::string message, u32 offset, u8 enable, u8 disable) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(listToggle);
  int choice = OptionsKB->Open();
  switch (choice) {
    case -1:
      break;
    case 0:
      Process::Write8(offset, enable);
      break;
    case 1:
      Process::Write8(offset, disable);
      break;
  }
  return choice;
}

int KBD::MultiToggle32(const std::string message,
                       std::vector<std::vector<u32>> value) {
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(listToggle);
  int choice = OptionsKB->Open();
  switch (choice) {
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
  return choice;
}

int KBD::LengthToggle32(const std::string message, const int length,
                        u32 base_offset, std::vector<u32> value) {
  KBD kbd;
  OptionsKB->GetMessage() = message;
  OptionsKB->Populate(listToggle);
  int choice = OptionsKB->Open();
  switch (choice) {
    case -1:
      break;
    case 0:
      for (int i = 0; i < length; i++) {
        Process::Write32(base_offset + i * 0x4, value[i]);
      }
      break;
    case 1:
      for (int i = 0; i < length; i++) {
        Process::Write32(base_offset + i * 0x4, 0);
      }
  }
  return choice;
}

KBD::~KBD() {
  delete KB;
  delete OptionsKB;
}

}  // namespace CTRPluginFramework