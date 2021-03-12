#pragma once
#include <string>

#include <CTRPluginFramework.hpp>
namespace CTRPluginFramework
{
    const static std::string patchProcessColorEditorTitle = "16êiêîÇ≈ì¸óÕÇµÇƒÇ≠ÇæÇ≥Ç¢ÅB[RGBa]";

    // Ui Color
    static u32 colorUiMainText;
    static u32 colorUiWindowTitle;
    static u32 colorUiMenuSelectedItem;
    static u32 colorUiMenuUnselectedItem;
    static u32 colorUiBackgroundMain;
    static u32 colorUiBackgroundSecondary;
    static u32 colorUiBackgroundBorder;

    // Keyboard Color
    static u32 colorKeyboardBackground;
    static u32 colorKeyboardKeyBackground;
    static u32 colorKeyboardKeyBackgroundPressed;
    static u32 colorKeyboardKeyText;
    static u32 colorKeyboardKeyTextPressed;
    static u32 colorKeyboardCursor;
    static u32 colorKeyboardInput;

    // Custom Keyboard Color
    static u32 colorCustomKeyboardBackgroundMain;
    static u32 colorCustomKeyboardBackgroundSecondary;
    static u32 colorCustomKeyboardBackgroundBorder;
    static u32 colorCustomKeyboardKeyBackground;
    static u32 colorCustomKeyboardKeyBackgroundPressed;
    static u32 colorCustomKeyboardKeyText;
    static u32 colorCustomKeyboardKeyTextPressed;
    static u32 colorCustomKeyboardScrollBarBackground;
    static u32 colorCustomKeyboardScrollBarThumb;

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