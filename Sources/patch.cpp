#include "patch.hpp"

namespace CTRPluginFramework {

std::string GetPathToBin() {
  std::string path_to_bin = "patch.bin";
  return path_to_bin;
}

void CreateDefaultFile() {
  const std::string kPathToBin = GetPathToBin();
  PatchColorData color;
  File file;
  if (File::Exists(kPathToBin)) {
    File::Remove(kPathToBin);
  }
  File::Create(kPathToBin);
  File::Open(file, kPathToBin);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void CreateDefaultFile(MenuEntry *entry) {
  Keyboard keyboard("patch.binを初期化しますか？", {"はい", "いいえ"});
  int choice = keyboard.Open();
  if (choice == 0) {
    CreateDefaultFile();
  }
}

void GetPatchColorData() {
  const std::string kPathToBin = GetPathToBin();
  PatchColorData color;
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  FwkSettings::Get().MainTextColor =
      Color(color.ui_main_text_r, color.ui_main_text_g, color.ui_main_text_b);
  FwkSettings::Get().WindowTitleColor =
      Color(color.ui_window_title_r,
            color.ui_window_title_g,
            color.ui_window_title_b);
  FwkSettings::Get().MenuSelectedItemColor =
      Color(color.ui_menu_selected_item_r, color.ui_menu_selected_item_g,
            color.ui_menu_selected_item_b);
  FwkSettings::Get().MenuUnselectedItemColor =
      Color(color.ui_menu_unselected_item_r, color.ui_menu_unselected_item_g,
            color.ui_menu_unselected_item_b);
  FwkSettings::Get().BackgroundMainColor =
      Color(color.ui_background_main_r, color.ui_background_main_g,
            color.ui_background_main_b);
  FwkSettings::Get().BackgroundSecondaryColor =
      Color(color.ui_background_secondary_r, color.ui_background_secondary_g,
            color.ui_background_secondary_b);
  FwkSettings::Get().BackgroundBorderColor =
      Color(color.ui_background_border_r, color.ui_background_border_g,
            color.ui_background_border_b);
  FwkSettings::Get().Keyboard.Background =
      Color(color.keyboard_background_r, color.keyboard_background_g,
            color.keyboard_background_b);
  FwkSettings::Get().Keyboard.KeyBackground =
      Color(color.keyboard_key_background_r, color.keyboard_key_background_g,
            color.keyboard_key_background_b);
  FwkSettings::Get().Keyboard.KeyBackgroundPressed = Color(
      color.keyboard_key_background_pressed_r,
      color.keyboard_key_background_pressed_g,
      color.keyboard_key_background_pressed_b);
  FwkSettings::Get().Keyboard.KeyText = Color(
      color.keyboard_key_text_r,
      color.keyboard_key_text_g,
      color.keyboard_key_text_b);
  FwkSettings::Get().Keyboard.KeyTextPressed =
      Color(color.keyboard_key_text_pressed_r,
            color.keyboard_key_text_pressed_g,
            color.keyboard_key_text_pressed_b);
  FwkSettings::Get().Keyboard.KeyTextDisabled =
      Color(color.keyboard_key_text_disabled_r,
            color.keyboard_key_text_disabled_g,
            color.keyboard_key_text_disabled_b);
  FwkSettings::Get().Keyboard.Cursor = Color(
      color.keyboard_cursor_r,
      color.keyboard_cursor_g,
      color.keyboard_cursor_b);
  FwkSettings::Get().Keyboard.Input =
      Color(color.keyboard_input_r,
            color.keyboard_input_g,
            color.keyboard_input_b);

  FwkSettings::Get().CustomKeyboard.BackgroundMain = Color(
      color.custom_keyboard_background_main_r,
      color.custom_keyboard_background_main_g,
      color.custom_keyboard_background_main_b);
  FwkSettings::Get().CustomKeyboard.BackgroundSecondary =
      Color(color.custom_keyboard_background_secondary_r,
            color.custom_keyboard_background_secondary_g,
            color.custom_keyboard_background_secondary_b);
  FwkSettings::Get().CustomKeyboard.BackgroundBorder =
      Color(color.custom_keyboard_background_border_r,
            color.custom_keyboard_background_border_g,
            color.custom_keyboard_background_border_b);
  FwkSettings::Get().CustomKeyboard.KeyBackground = Color(
      color.custom_keyboard_key_background_r,
      color.custom_keyboard_key_background_g,
      color.custom_keyboard_key_background_b);
  FwkSettings::Get().CustomKeyboard.KeyBackgroundPressed =
      Color(color.custom_keyboard_key_background_pressed_r,
            color.custom_keyboard_key_background_pressed_g,
            color.custom_keyboard_key_background_pressed_b);
  FwkSettings::Get().CustomKeyboard.KeyText =
      Color(color.custom_keyboard_key_text_r, color.custom_keyboard_key_text_g,
            color.custom_keyboard_key_text_b);
  FwkSettings::Get().CustomKeyboard.KeyTextPressed = Color(
      color.custom_keyboard_key_text_pressed_r,
      color.custom_keyboard_key_text_pressed_g,
      color.custom_keyboard_key_text_pressed_b);
  FwkSettings::Get().CustomKeyboard.ScrollBarBackground =
      Color(color.custom_keyboard_scroll_bar_background_r,
            color.custom_keyboard_scroll_bar_background_g,
            color.custom_keyboard_scroll_bar_background_b);
  FwkSettings::Get().CustomKeyboard.ScrollBarThumb = Color(
      color.custom_keyboard_scroll_bar_thumb_r,
      color.custom_keyboard_scroll_bar_thumb_g,
      color.custom_keyboard_scroll_bar_thumb_b);
  file.Close();
}

void PatchProcessUiMainTextColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_main_text_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_main_text_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_main_text_b = value;
  }
  FwkSettings::Get().MainTextColor =
      Color(color.ui_main_text_r, color.ui_main_text_g, color.ui_main_text_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiWindowTitleColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_window_title_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_window_title_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_window_title_b = value;
  }
  FwkSettings::Get().WindowTitleColor =
      Color(color.ui_window_title_r,
            color.ui_window_title_g,
            color.ui_window_title_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiMenuSelectedItemColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_menu_selected_item_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_menu_selected_item_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_menu_selected_item_b = value;
  }
  FwkSettings::Get().MenuSelectedItemColor =
      Color(color.ui_menu_selected_item_r, color.ui_menu_selected_item_g,
            color.ui_menu_selected_item_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiMenuUnselectedItemColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_menu_unselected_item_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_menu_unselected_item_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_menu_unselected_item_b = value;
  }
  FwkSettings::Get().MenuUnselectedItemColor =
      Color(color.ui_menu_unselected_item_r, color.ui_menu_unselected_item_g,
            color.ui_menu_unselected_item_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiBackgroundMainColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_background_main_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_background_main_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_background_main_b = value;
  }
  FwkSettings::Get().BackgroundMainColor =
      Color(color.ui_background_main_r, color.ui_background_main_g,
            color.ui_background_main_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiBackgroundSecondaryColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_background_secondary_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_background_secondary_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_background_secondary_b = value;
  }
  FwkSettings::Get().BackgroundSecondaryColor =
      Color(color.ui_background_secondary_r, color.ui_background_secondary_g,
            color.ui_background_secondary_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiBackgroundBorderColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.ui_background_border_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.ui_background_border_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.ui_background_border_b = value;
  }
  FwkSettings::Get().BackgroundBorderColor =
      Color(color.ui_background_border_r, color.ui_background_border_g,
            color.ui_background_border_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardBackgroundColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_background_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_background_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_background_b = value;
  }
  FwkSettings::Get().Keyboard.Background =
      Color(color.keyboard_background_r, color.keyboard_background_g,
            color.keyboard_background_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyBackgroundColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_key_background_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_key_background_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_key_background_b = value;
  }
  FwkSettings::Get().Keyboard.KeyBackground =
      Color(color.keyboard_key_background_r, color.keyboard_key_background_g,
            color.keyboard_key_background_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyBackgroundPressedColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_key_background_pressed_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_key_background_pressed_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_key_background_pressed_b = value;
  }
  FwkSettings::Get().Keyboard.KeyBackgroundPressed = Color(
      color.keyboard_key_background_pressed_r,
      color.keyboard_key_background_pressed_g,
      color.keyboard_key_background_pressed_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyTextColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_key_text_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_key_text_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_key_text_b = value;
  }
  FwkSettings::Get().Keyboard.KeyText = Color(
      color.keyboard_key_text_r,
      color.keyboard_key_text_g,
      color.keyboard_key_text_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyTextPressedColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_key_text_pressed_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_key_text_pressed_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_key_text_pressed_b = value;
  }
  FwkSettings::Get().Keyboard.KeyTextPressed =
      Color(color.keyboard_key_text_pressed_r,
            color.keyboard_key_text_pressed_g,
            color.keyboard_key_text_pressed_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyTextDisabledColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_key_text_disabled_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_key_text_disabled_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_key_text_disabled_b = value;
  }
  FwkSettings::Get().Keyboard.KeyTextDisabled =
      Color(color.keyboard_key_text_disabled_r,
            color.keyboard_key_text_disabled_g,
            color.keyboard_key_text_disabled_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardCursorColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_cursor_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_cursor_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_cursor_b = value;
  }
  FwkSettings::Get().Keyboard.Cursor = Color(
      color.keyboard_cursor_r,
      color.keyboard_cursor_g,
      color.keyboard_cursor_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardInputColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.keyboard_input_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.keyboard_input_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.keyboard_input_b = value;
  }
  FwkSettings::Get().Keyboard.Input =
      Color(color.keyboard_input_r,
            color.keyboard_input_g,
            color.keyboard_input_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardBackgroundMainColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_background_main_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_background_main_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_background_main_b = value;
  }
  FwkSettings::Get().CustomKeyboard.BackgroundMain = Color(
      color.custom_keyboard_background_main_r,
      color.custom_keyboard_background_main_g,
      color.custom_keyboard_background_main_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardBackgroundSecondaryColorEditor(
    MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_background_secondary_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_background_secondary_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_background_secondary_b = value;
  }
  FwkSettings::Get().CustomKeyboard.BackgroundSecondary =
      Color(color.custom_keyboard_background_secondary_r,
            color.custom_keyboard_background_secondary_g,
            color.custom_keyboard_background_secondary_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardBackgroundBorderColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_background_border_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_background_border_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_background_border_b = value;
  }
  FwkSettings::Get().CustomKeyboard.BackgroundBorder =
      Color(color.custom_keyboard_background_border_r,
            color.custom_keyboard_background_border_g,
            color.custom_keyboard_background_border_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyBackgroundColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_key_background_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_key_background_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_key_background_b = value;
  }
  FwkSettings::Get().CustomKeyboard.KeyBackground = Color(
      color.custom_keyboard_key_background_r,
      color.custom_keyboard_key_background_g,
      color.custom_keyboard_key_background_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(
    MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_key_background_pressed_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_key_background_pressed_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_key_background_pressed_b = value;
  }
  FwkSettings::Get().CustomKeyboard.KeyBackgroundPressed =
      Color(color.custom_keyboard_key_background_pressed_r,
            color.custom_keyboard_key_background_pressed_g,
            color.custom_keyboard_key_background_pressed_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_key_text_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_key_text_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_key_text_b = value;
  }
  FwkSettings::Get().CustomKeyboard.KeyText =
      Color(color.custom_keyboard_key_text_r, color.custom_keyboard_key_text_g,
            color.custom_keyboard_key_text_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_key_text_pressed_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_key_text_pressed_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_key_text_pressed_b = value;
  }
  FwkSettings::Get().CustomKeyboard.KeyTextPressed = Color(
      color.custom_keyboard_key_text_pressed_r,
      color.custom_keyboard_key_text_pressed_g,
      color.custom_keyboard_key_text_pressed_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(
    MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_scroll_bar_background_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_scroll_bar_background_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_scroll_bar_background_b = value;
  }
  FwkSettings::Get().CustomKeyboard.ScrollBarBackground =
      Color(color.custom_keyboard_scroll_bar_background_r,
            color.custom_keyboard_scroll_bar_background_g,
            color.custom_keyboard_scroll_bar_background_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry *entry) {
  const std::string kPathToBin = GetPathToBin();
  File file;
  if (!File::Exists(kPathToBin)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, kPathToBin);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0 && key.Open(value) == 0) {
    color.custom_keyboard_scroll_bar_thumb_r = value;
  } else if (choice == 1 && key.Open(value) == 0) {
    color.custom_keyboard_scroll_bar_thumb_g = value;
  } else if (choice == 2 && key.Open(value) == 0) {
    color.custom_keyboard_scroll_bar_thumb_b = value;
  }
  FwkSettings::Get().CustomKeyboard.ScrollBarThumb = Color(
      color.custom_keyboard_scroll_bar_thumb_r,
      color.custom_keyboard_scroll_bar_thumb_g,
      color.custom_keyboard_scroll_bar_thumb_b);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessDefaultTheme(MenuEntry *entry) {
  Keyboard keyboard("CTRPFの色を元に戻しますか？", {"はい", "いいえ"});
  int choice = keyboard.Open();
  if (choice == 0) {
    FwkSettings::SetThemeDefault();
  }
}

}  // namespace CTRPluginFramework