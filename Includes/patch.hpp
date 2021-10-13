#ifndef MHX3GX_INCLUDES_PATCH_HPP_
#define MHX3GX_INCLUDES_PATCH_HPP_

#include "stdafx.hpp"

namespace CTRPluginFramework {

struct PatchColorData {
  // Ui Color
  u8 ui_main_text_r = 0xFF;
  u8 ui_main_text_g = 0xFF;
  u8 ui_main_text_b = 0xFF;
  u8 ui_window_title_r = 0xFF;
  u8 ui_window_title_g = 0xFF;
  u8 ui_window_title_b = 0xFF;
  u8 ui_menu_selected_item_r = 0xFF;
  u8 ui_menu_selected_item_g = 0xFF;
  u8 ui_menu_selected_item_b = 0xFF;
  u8 ui_menu_unselected_item_r = 0xC0;
  u8 ui_menu_unselected_item_g = 0xC0;
  u8 ui_menu_unselected_item_b = 0xC0;
  u8 ui_background_main_r = 0x00;
  u8 ui_background_main_g = 0x00;
  u8 ui_background_main_b = 0x00;
  u8 ui_background_secondary_r = 0x15;
  u8 ui_background_secondary_g = 0x15;
  u8 ui_background_secondary_b = 0x15;
  u8 ui_background_border_r = 0xFF;
  u8 ui_background_border_g = 0xFF;
  u8 ui_background_border_b = 0xFF;

  // Keyboard Color
  u8 keyboard_background_r = 0x00;
  u8 keyboard_background_g = 0x00;
  u8 keyboard_background_b = 0x00;
  u8 keyboard_key_background_r = 0x00;
  u8 keyboard_key_background_g = 0x00;
  u8 keyboard_key_background_b = 0x00;
  u8 keyboard_key_background_pressed_r = 0xC0;
  u8 keyboard_key_background_pressed_g = 0xC0;
  u8 keyboard_key_background_pressed_b = 0xC0;
  u8 keyboard_key_text_r = 0xFF;
  u8 keyboard_key_text_g = 0xFF;
  u8 keyboard_key_text_b = 0xFF;
  u8 keyboard_key_text_pressed_r = 0xFF;
  u8 keyboard_key_text_pressed_g = 0xFF;
  u8 keyboard_key_text_pressed_b = 0xFF;
  u8 keyboard_key_text_disabled_r = 0x69;
  u8 keyboard_key_text_disabled_g = 0x69;
  u8 keyboard_key_text_disabled_b = 0x69;
  u8 keyboard_cursor_r = 0xFF;
  u8 keyboard_cursor_g = 0xFF;
  u8 keyboard_cursor_b = 0xFF;
  u8 keyboard_input_r = 0xFF;
  u8 keyboard_input_g = 0xFF;
  u8 keyboard_input_b = 0xFF;

  // Custom Keyboard Color
  u8 custom_keyboard_background_main_r = 0x00;
  u8 custom_keyboard_background_main_g = 0x00;
  u8 custom_keyboard_background_main_b = 0x00;
  u8 custom_keyboard_background_secondary_r = 0x15;
  u8 custom_keyboard_background_secondary_g = 0x15;
  u8 custom_keyboard_background_secondary_b = 0x15;
  u8 custom_keyboard_background_border_r = 0xFF;
  u8 custom_keyboard_background_border_g = 0xFF;
  u8 custom_keyboard_background_border_b = 0xFF;
  u8 custom_keyboard_key_background_r = 0x51;
  u8 custom_keyboard_key_background_g = 0x51;
  u8 custom_keyboard_key_background_b = 0x51;
  u8 custom_keyboard_key_background_pressed_r = 0xDC;
  u8 custom_keyboard_key_background_pressed_g = 0xDC;
  u8 custom_keyboard_key_background_pressed_b = 0xDC;
  u8 custom_keyboard_key_text_r = 0xFF;
  u8 custom_keyboard_key_text_g = 0xFF;
  u8 custom_keyboard_key_text_b = 0xFF;
  u8 custom_keyboard_key_text_pressed_r = 0x00;
  u8 custom_keyboard_key_text_pressed_g = 0x00;
  u8 custom_keyboard_key_text_pressed_b = 0x00;
  u8 custom_keyboard_scroll_bar_background_r = 0xC0;
  u8 custom_keyboard_scroll_bar_background_g = 0xC0;
  u8 custom_keyboard_scroll_bar_background_b = 0xC0;
  u8 custom_keyboard_scroll_bar_thumb_r = 0xDC;
  u8 custom_keyboard_scroll_bar_thumb_g = 0xDC;
  u8 custom_keyboard_scroll_bar_thumb_b = 0xDC;
};

std::string GetPathToBin();

void CreateDefaultFile();
void CreateDefaultFile(MenuEntry *entry);
void GetPatchColorData();

void PatchProcessUiMainTextColorEditor(MenuEntry *entry);
void PatchProcessUiWindowTitleColorEditor(MenuEntry *entry);
void PatchProcessUiMenuSelectedItemColorEditor(MenuEntry *entry);
void PatchProcessUiMenuUnselectedItemColorEditor(MenuEntry *entry);
void PatchProcessUiBackgroundMainColorEditor(MenuEntry *entry);
void PatchProcessUiBackgroundSecondaryColorEditor(MenuEntry *entry);
void PatchProcessUiBackgroundBorderColorEditor(MenuEntry *entry);

void PatchProcessKeyboardBackgroundColorEditor(MenuEntry *entry);
void PatchProcessKeyboardKeyBackgroundColorEditor(MenuEntry *entry);
void PatchProcessKeyboardKeyBackgroundPressedColorEditor(MenuEntry *entry);
void PatchProcessKeyboardKeyTextColorEditor(MenuEntry *entry);
void PatchProcessKeyboardKeyTextPressedColorEditor(MenuEntry *entry);
void PatchProcessKeyboardKeyTextDisabledColorEditor(MenuEntry *entry);
void PatchProcessKeyboardCursorColorEditor(MenuEntry *entry);
void PatchProcessKeyboardInputColorEditor(MenuEntry *entry);

void PatchProcessCustomKeyboardBackgroundMainColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardBackgroundSecondaryColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardBackgroundBorderColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardKeyBackgroundColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(
    MenuEntry *entry);
void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(MenuEntry *entry);
void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry *entry);

void PatchProcessDefaultTheme(MenuEntry *entry);

}  // namespace CTRPluginFramework

#endif  // MHX3GX_INCLUDES_PATCH_HPP_