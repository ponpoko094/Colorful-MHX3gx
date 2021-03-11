#pragma once
#include <string>

#include <CTRPluginFramework.hpp>
namespace CTRPluginFramework
{
    FwkSettings set;
    std::string patchProcessColorEditorTitle = "16êiêîÇ≈ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB[RGBa]";

    // Ui Color
    static u32 colorUiMainText = 0xF08080FF;
    static u32 colorUiWindowTitle = 0xF08080FF;
    static u32 colorUiMenuSelectedItem = 0xF08080FF;
    static u32 colorUiMenuUnselectedItem = 0xF08080FF;
    static u32 colorUiBackgroundMain = 0x000000FF;
    static u32 colorUiBackgroundSecondary = 0x000000FF;
    static u32 colorUiBackgroundBorder = 0xF08080FF;

    // Keyboard Color
    static u32 colorKeyboardBackground = 0xF08080FF;
    static u32 colorKeyboardKeyBackground = 0xF08080FF;
    static u32 colorKeyboardKeyBackgroundPressed = 0xF08080FF;
    static u32 colorKeyboardKeyText = 0xF08080FF;
    static u32 colorKeyboardKeyTextPressed = 0xF08080FF;
    static u32 colorKeyboardCursor = 0xF08080FF;
    static u32 colorKeyboardInput = 0xF08080FF;

    // Custom Keyboard Color
    static u32 colorCustomKeyboardBackgroundMain = 0xF08080FF;
    static u32 colorCustomKeyboardBackgroundSecondary = 0xF08080FF;
    static u32 colorCustomKeyboardBackgroundBorder = 0xF08080FF;
    static u32 colorCustomKeyboardKeyBackground = 0xF08080FF;
    static u32 colorCustomKeyboardKeyBackgroundPressed = 0xF08080FF;
    static u32 colorCustomKeyboardKeyText = 0xF08080FF;
    static u32 colorCustomKeyboardKeyTextPressed = 0xF08080FF;
    static u32 colorCustomKeyboardScrollBarBackground = 0xF08080FF;
    static u32 colorCustomKeyboardScrollBarThumb = 0xF08080FF;

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
    void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(MenuEntry* entry);
    void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry* entry);
    void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry* entry);
    void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(MenuEntry* entry);
    void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry* entry);

    void PatchProcessDefaultTheme(MenuEntry* entry);
} // namespace CTRPluginFramework