#ifndef MHX3GX_INCLUDES_PATCH_H_
#define MHX3GX_INCLUDES_PATCH_H_

#include <CTRPluginFramework.hpp>
#include <string>

namespace CTRPluginFramework {

const static std::string patchProcessColorEditorTitle =
    "16進数で入力してください。[RGBa]";

// Ui Color
static u32 colorUiMainText = 0xFFFFFFFF;
static u32 colorUiWindowTitle = 0xFFFFFFFF;
static u32 colorUiMenuSelectedItem = 0xFFFFFFFF;
static u32 colorUiMenuUnselectedItem = 0xFFFFFFFF;
static u32 colorUiBackgroundMain = 0xFFFFFFFF;
static u32 colorUiBackgroundSecondary = 0xFFFFFFFF;
static u32 colorUiBackgroundBorder = 0xFFFFFFFF;

// Keyboard Color
static u32 colorKeyboardBackground = 0x00000000;
static u32 colorKeyboardKeyBackground = 0x00000000;
static u32 colorKeyboardKeyBackgroundPressed = 0xFFFFFFFF;
static u32 colorKeyboardKeyText = 0xFFFFFFFF;
static u32 colorKeyboardKeyTextPressed = 0x00000000;
static u32 colorKeyboardCursor = 0x00000000;
static u32 colorKeyboardInput = 0xFFFFFFFF;

// Custom Keyboard Color
static u32 colorCustomKeyboardBackgroundMain = 0x00000000;
static u32 colorCustomKeyboardBackgroundSecondary = 0x00000000;
static u32 colorCustomKeyboardBackgroundBorder = 0x00000000;
static u32 colorCustomKeyboardKeyBackground = 0x00000000;
static u32 colorCustomKeyboardKeyBackgroundPressed = 0xFFFFFFFF;
static u32 colorCustomKeyboardKeyText = 0xFFFFFFFF;
static u32 colorCustomKeyboardKeyTextPressed = 0x00000000;
static u32 colorCustomKeyboardScrollBarBackground = 0x00000000;
static u32 colorCustomKeyboardScrollBarThumb = 0xFFFFFFFF;

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