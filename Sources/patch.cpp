#include "Patch.hpp"

namespace CTRPluginFramework
{
    void PatchProcessUiMainTextColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiMainText);
        set.Get().MainTextColor = Color(colorUiMainText);
    }

    void PatchProcessUiWindowTitleColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiWindowTitle);
        set.Get().WindowTitleColor = Color(colorUiWindowTitle);
    }

    void PatchProcessUiMenuSelectedItemColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiMenuSelectedItem);
        set.Get().MenuSelectedItemColor = Color(colorUiMenuSelectedItem);
    }

    void PatchProcessUiMenuUnselectedItemColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiMenuUnselectedItem);
        set.Get().MenuUnselectedItemColor = Color(colorUiMenuUnselectedItem);
    }

    void PatchProcessUiBackgroundMainColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiBackgroundMain);
        set.Get().BackgroundMainColor = Color(colorUiBackgroundMain);
    }

    void PatchProcessUiBackgroundSecondaryColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiBackgroundSecondary);
        set.Get().BackgroundSecondaryColor = Color(colorUiBackgroundSecondary);
    }

    void PatchProcessUiBackgroundBorderColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorUiBackgroundBorder);
        set.Get().BackgroundBorderColor = Color(colorUiBackgroundBorder);
    }

    void PatchProcessKeyboardBackgroundColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardBackground);
        set.Get().Keyboard.Background = Color(colorKeyboardBackground);
    }

    void PatchProcessKeyboardKeyBackgroundColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardKeyBackground);
        set.Get().Keyboard.KeyBackground = Color(colorKeyboardKeyBackground);
    }

    void PatchProcessKeyboardKeyBackgroundPressedColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardKeyBackgroundPressed);
        set.Get().Keyboard.KeyBackgroundPressed = Color(colorKeyboardKeyBackgroundPressed);
    }

    void PatchProcessKeyboardKeyTextColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardKeyText);
        set.Get().Keyboard.KeyText = Color(colorKeyboardKeyText);
    }

    void PatchProcessKeyboardKeyTextPressedColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardKeyTextPressed);
        set.Get().Keyboard.KeyTextPressed = Color(colorKeyboardKeyTextPressed);
    }

    void PatchProcessKeyboardCursorColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardCursor);
        set.Get().Keyboard.Cursor = Color(colorKeyboardCursor);
    }

    void PatchProcessKeyboardInputColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorKeyboardInput);
        set.Get().Keyboard.Input = Color(colorKeyboardInput);
    }

    void PatchProcessCustomKeyboardBackgroundMainColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardBackgroundMain);
        set.Get().CustomKeyboard.BackgroundMain = Color(colorCustomKeyboardBackgroundMain);
    }

    void PatchProcessCustomKeyboardBackgroundSecondaryColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardBackgroundSecondary);
        set.Get().CustomKeyboard.BackgroundSecondary = Color(colorCustomKeyboardBackgroundSecondary);
    }

    void PatchProcessCustomKeyboardBackgroundBorderColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardBackgroundBorder);
        set.Get().CustomKeyboard.BackgroundBorder = Color(colorCustomKeyboardBackgroundBorder);
    }

    void PatchProcessCustomKeyboardKeyBackgroundColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardKeyBackground);
        set.Get().CustomKeyboard.KeyBackground = Color(colorCustomKeyboardKeyBackground);
    }

    void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardKeyBackgroundPressed);
        set.Get().CustomKeyboard.KeyBackgroundPressed = Color(colorCustomKeyboardKeyBackgroundPressed);
    }

    void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardKeyText);
        set.Get().CustomKeyboard.KeyText = Color(colorCustomKeyboardKeyText);
    }

    void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardKeyTextPressed);
        set.Get().CustomKeyboard.KeyTextPressed = Color(colorCustomKeyboardKeyTextPressed);
    }

    void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardScrollBarBackground);
        set.Get().CustomKeyboard.ScrollBarBackground = Color(colorCustomKeyboardScrollBarBackground);
    }

    void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry* entry)
    {
        Keyboard keyboard(patchProcessColorEditorTitle);
        keyboard.Open(colorCustomKeyboardScrollBarThumb);
        set.Get().CustomKeyboard.ScrollBarThumb = Color(colorCustomKeyboardScrollBarThumb);
    }

    void PatchProcessDefaultTheme(MenuEntry* entry)
    {
        Keyboard keyboard("CTRPFの色を元に戻しますか？", { "はい", "いいえ" });
        int choice = keyboard.Open();
        if (choice == 0)
        {
            set.SetThemeDefault();
        }
    }
} // namespace CTRPluginFramework