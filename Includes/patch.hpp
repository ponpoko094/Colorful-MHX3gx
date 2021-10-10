#ifndef MHX3GX_INCLUDES_PATCH_H_
#define MHX3GX_INCLUDES_PATCH_H_

#include "stdafx.hpp"

namespace CTRPluginFramework {

struct PatchColorData {
  // Ui Color
  u8 uiMainTextR = 0xFF;
  u8 uiMainTextG = 0xFF;
  u8 uiMainTextB = 0xFF;
  u8 uiWindowTitleR = 0xFF;
  u8 uiWindowTitleG = 0xFF;
  u8 uiWindowTitleB = 0xFF;
  u8 uiMenuSelectedItemR = 0xFF;
  u8 uiMenuSelectedItemG = 0xFF;
  u8 uiMenuSelectedItemB = 0xFF;
  u8 uiMenuUnselectedItemR = 0xC0;
  u8 uiMenuUnselectedItemG = 0xC0;
  u8 uiMenuUnselectedItemB = 0xC0;
  u8 uiBackgroundMainR = 0x00;
  u8 uiBackgroundMainG = 0x00;
  u8 uiBackgroundMainB = 0x00;
  u8 uiBackgroundSecondaryR = 0x15;
  u8 uiBackgroundSecondaryG = 0x15;
  u8 uiBackgroundSecondaryB = 0x15;
  u8 uiBackgroundBorderR = 0xFF;
  u8 uiBackgroundBorderG = 0xFF;
  u8 uiBackgroundBorderB = 0xFF;

  // Keyboard Color
  u8 keyboardBackgroundR = 0x00;
  u8 keyboardBackgroundG = 0x00;
  u8 keyboardBackgroundB = 0x00;
  u8 keyboardKeyBackgroundR = 0x00;
  u8 keyboardKeyBackgroundG = 0x00;
  u8 keyboardKeyBackgroundB = 0x00;
  u8 keyboardKeyBackgroundPressedR = 0xC0;
  u8 keyboardKeyBackgroundPressedG = 0xC0;
  u8 keyboardKeyBackgroundPressedB = 0xC0;
  u8 keyboardKeyTextR = 0xFF;
  u8 keyboardKeyTextG = 0xFF;
  u8 keyboardKeyTextB = 0xFF;
  u8 keyboardKeyTextPressedR = 0xFF;
  u8 keyboardKeyTextPressedG = 0xFF;
  u8 keyboardKeyTextPressedB = 0xFF;
  u8 keyboardKeyTextDisabledR = 0x69;
  u8 keyboardKeyTextDisabledG = 0x69;
  u8 keyboardKeyTextDisabledB = 0x69;
  u8 keyboardCursorR = 0xFF;
  u8 keyboardCursorG = 0xFF;
  u8 keyboardCursorB = 0xFF;
  u8 keyboardInputR = 0xFF;
  u8 keyboardInputG = 0xFF;
  u8 keyboardInputB = 0xFF;

  // Custom Keyboard Color
  u8 customKeyboardBackgroundMainR = 0x00;
  u8 customKeyboardBackgroundMainG = 0x00;
  u8 customKeyboardBackgroundMainB = 0x00;
  u8 customKeyboardBackgroundSecondaryR = 0x15;
  u8 customKeyboardBackgroundSecondaryG = 0x15;
  u8 customKeyboardBackgroundSecondaryB = 0x15;
  u8 customKeyboardBackgroundBorderR = 0xFF;
  u8 customKeyboardBackgroundBorderG = 0xFF;
  u8 customKeyboardBackgroundBorderB = 0xFF;
  u8 customKeyboardKeyBackgroundR = 0x51;
  u8 customKeyboardKeyBackgroundG = 0x51;
  u8 customKeyboardKeyBackgroundB = 0x51;
  u8 customKeyboardKeyBackgroundPressedR = 0xDC;
  u8 customKeyboardKeyBackgroundPressedG = 0xDC;
  u8 customKeyboardKeyBackgroundPressedB = 0xDC;
  u8 customKeyboardKeyTextR = 0xFF;
  u8 customKeyboardKeyTextG = 0xFF;
  u8 customKeyboardKeyTextB = 0xFF;
  u8 customKeyboardKeyTextPressedR = 0x00;
  u8 customKeyboardKeyTextPressedG = 0x00;
  u8 customKeyboardKeyTextPressedB = 0x00;
  u8 customKeyboardScrollBarBackgroundR = 0xC0;
  u8 customKeyboardScrollBarBackgroundG = 0xC0;
  u8 customKeyboardScrollBarBackgroundB = 0xC0;
  u8 customKeyboardScrollBarThumbR = 0xDC;
  u8 customKeyboardScrollBarThumbG = 0xDC;
  u8 customKeyboardScrollBarThumbB = 0xDC;
};

void CreateDefaultFile();
void CreateDefaultFile(MenuEntry* entry);
void GetPatchColorData(FwkSettings& settings);

void PatchProcessUiMainTextColorEditor(MenuEntry* entry);
void PatchProcessUiWindowTitleColorEditor(MenuEntry* entry);
void PatchProcessUiMenuSelectedItemColorEditor(MenuEntry* entry);
void PatchProcessUiMenuUnselectedItemColorEditor(MenuEntry* entry);
void PatchProcessUiBackgroundMainColorEditor(MenuEntry* entry);
void PatchProcessUiBackgroundSecondaryColorEditor(MenuEntry* entry);
void PatchProcessUiBackgroundBorderColorEditor(MenuEntry* entry);

void PatchProcessKeyboardBackgroundColorEditor(MenuEntry* entry);
void PatchProcessKeyboardKeyBackgroundColorEditor(MenuEntry* entry);
void PatchProcessKeyboardKeyBackgroundPressedColorEditor(MenuEntry* entry);
void PatchProcessKeyboardKeyTextColorEditor(MenuEntry* entry);
void PatchProcessKeyboardKeyTextPressedColorEditor(MenuEntry* entry);
void PatchProcessKeyboardCursorColorEditor(MenuEntry* entry);
void PatchProcessKeyboardInputColorEditor(MenuEntry* entry);

void PatchProcessCustomKeyboardBackgroundMainColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardBackgroundSecondaryColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardBackgroundBorderColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardKeyBackgroundColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(
    MenuEntry* entry);
void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(MenuEntry* entry);
void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry* entry);

void PatchProcessDefaultTheme(MenuEntry* entry);

}  // namespace CTRPluginFramework

#endif  // MHX3GX_INCLUDES_PATCH_H_