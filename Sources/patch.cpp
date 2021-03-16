#include "patch.h"

namespace CTRPluginFramework {

FwkSettings* set;

void PatchProcessUiMainTextColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiMainText) != -1) {
        set->Get().MainTextColor = Color(colorUiMainText);
    }
}

void PatchProcessUiWindowTitleColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiWindowTitle) != -1) {
        set->Get().WindowTitleColor = Color(colorUiWindowTitle);
    }
}

void PatchProcessUiMenuSelectedItemColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiMenuSelectedItem) != -1) {
        set->Get().MenuSelectedItemColor = Color(colorUiMenuSelectedItem);
    }
}

void PatchProcessUiMenuUnselectedItemColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiMenuUnselectedItem) != -1) {
        set->Get().MenuUnselectedItemColor = Color(colorUiMenuUnselectedItem);
    }
}

void PatchProcessUiBackgroundMainColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiBackgroundMain) != -1) {
        set->Get().BackgroundMainColor = Color(colorUiBackgroundMain);
    }
}

void PatchProcessUiBackgroundSecondaryColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiBackgroundSecondary) != -1) {
        set->Get().BackgroundSecondaryColor = Color(colorUiBackgroundSecondary);
    }
}

void PatchProcessUiBackgroundBorderColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorUiBackgroundBorder) != -1) {
        set->Get().BackgroundBorderColor = Color(colorUiBackgroundBorder);
    }
}

void PatchProcessKeyboardBackgroundColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardBackground) != -1) {
        set->Get().Keyboard.Background = Color(colorKeyboardBackground);
    }
}

void PatchProcessKeyboardKeyBackgroundColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardKeyBackground) != -1) {
        set->Get().Keyboard.KeyBackground = Color(colorKeyboardKeyBackground);
    }
}

void PatchProcessKeyboardKeyBackgroundPressedColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardKeyBackgroundPressed) != -1) {
        set->Get().Keyboard.KeyBackgroundPressed = Color(colorKeyboardKeyBackgroundPressed);
    }
}

void PatchProcessKeyboardKeyTextColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardKeyText) != -1) {
        set->Get().Keyboard.KeyText = Color(colorKeyboardKeyText);
    }
}

void PatchProcessKeyboardKeyTextPressedColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardKeyTextPressed) != -1) {
        set->Get().Keyboard.KeyTextPressed = Color(colorKeyboardKeyTextPressed);
    }
}

void PatchProcessKeyboardCursorColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardCursor) != -1) {
        set->Get().Keyboard.Cursor = Color(colorKeyboardCursor);
    }
}

void PatchProcessKeyboardInputColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorKeyboardInput) != -1) {
        set->Get().Keyboard.Input = Color(colorKeyboardInput);
    }
}

void PatchProcessCustomKeyboardBackgroundMainColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardBackgroundMain) != -1) {
        set->Get().CustomKeyboard.BackgroundMain = Color(colorCustomKeyboardBackgroundMain);
    }
}

void PatchProcessCustomKeyboardBackgroundSecondaryColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardBackgroundSecondary) != -1) {
        set->Get().CustomKeyboard.BackgroundSecondary = Color(colorCustomKeyboardBackgroundSecondary);
    }
}

void PatchProcessCustomKeyboardBackgroundBorderColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardBackgroundBorder) != -1) {
        set->Get().CustomKeyboard.BackgroundBorder = Color(colorCustomKeyboardBackgroundBorder);
    }
}

void PatchProcessCustomKeyboardKeyBackgroundColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardKeyBackground) != -1) {
        set->Get().CustomKeyboard.KeyBackground = Color(colorCustomKeyboardKeyBackground);
    }
}

void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardKeyBackgroundPressed) != -1) {
        set->Get().CustomKeyboard.KeyBackgroundPressed = Color(colorCustomKeyboardKeyBackgroundPressed);
    }
}

void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardKeyText) != -1) {
        set->Get().CustomKeyboard.KeyText = Color(colorCustomKeyboardKeyText);
    }
}

void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardKeyTextPressed) != -1) {
        set->Get().CustomKeyboard.KeyTextPressed = Color(colorCustomKeyboardKeyTextPressed);
    }
}

void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardScrollBarBackground) != -1) {
        set->Get().CustomKeyboard.ScrollBarBackground = Color(colorCustomKeyboardScrollBarBackground);
    }
}

void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry* entry) {
    Keyboard keyboard(patchProcessColorEditorTitle);
    if (keyboard.Open(colorCustomKeyboardScrollBarThumb) != -1) {
        set->Get().CustomKeyboard.ScrollBarThumb = Color(colorCustomKeyboardScrollBarThumb);
    }
}

void PatchProcessDefaultTheme(MenuEntry* entry) {
    Keyboard keyboard("CTRPFの色を元に戻しますか？", {"はい", "いいえ"});
    int choice = keyboard.Open();
    if (choice == 0) {
        set->SetThemeDefault();
    }
}

}  // namespace CTRPluginFramework