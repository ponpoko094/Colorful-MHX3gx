#include "patch.hpp"

namespace CTRPluginFramework {

FwkSettings *set;
const static std::string pathToBIN = "patch.bin";

void CreateDefaultFile() {
  PatchColorData color;
  File file;
  if (File::Exists(pathToBIN)) {
    File::Remove(pathToBIN);
  }
  File::Create(pathToBIN);
  File::Open(file, pathToBIN);
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
  PatchColorData color;
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  FwkSettings::Get().MainTextColor =
      Color(color.uiMainTextR, color.uiMainTextG, color.uiMainTextB);
  FwkSettings::Get().WindowTitleColor =
      Color(color.uiWindowTitleR, color.uiWindowTitleG, color.uiWindowTitleB);
  FwkSettings::Get().MenuSelectedItemColor =
      Color(color.uiMenuSelectedItemR, color.uiMenuSelectedItemG,
            color.uiMenuSelectedItemB);
  FwkSettings::Get().MenuUnselectedItemColor =
      Color(color.uiMenuUnselectedItemR, color.uiMenuUnselectedItemG,
            color.uiMenuUnselectedItemB);
  FwkSettings::Get().BackgroundMainColor =
      Color(color.uiBackgroundMainR, color.uiBackgroundMainG,
            color.uiBackgroundMainB);
  FwkSettings::Get().BackgroundSecondaryColor =
      Color(color.uiBackgroundSecondaryR, color.uiBackgroundSecondaryG,
            color.uiBackgroundSecondaryB);
  FwkSettings::Get().BackgroundBorderColor =
      Color(color.uiBackgroundBorderR, color.uiBackgroundBorderG,
            color.uiBackgroundBorderB);
  FwkSettings::Get().Keyboard.Background =
      Color(color.keyboardBackgroundR, color.keyboardBackgroundG,
            color.keyboardBackgroundB);
  FwkSettings::Get().Keyboard.KeyBackground =
      Color(color.keyboardKeyBackgroundR, color.keyboardKeyBackgroundG,
            color.keyboardKeyBackgroundB);
  FwkSettings::Get().Keyboard.KeyBackgroundPressed = Color(
      color.keyboardKeyBackgroundPressedR, color.keyboardKeyBackgroundPressedG,
      color.keyboardKeyBackgroundPressedB);
  FwkSettings::Get().Keyboard.KeyText = Color(
      color.keyboardKeyTextR, color.keyboardKeyTextG, color.keyboardKeyTextB);
  FwkSettings::Get().Keyboard.KeyTextPressed =
      Color(color.keyboardKeyTextPressedR, color.keyboardKeyTextPressedG,
            color.keyboardKeyTextPressedB);
  FwkSettings::Get().Keyboard.KeyTextDisabled =
      Color(color.keyboardKeyTextDisabledR, color.keyboardKeyTextDisabledG,
            color.keyboardKeyTextDisabledB);
  FwkSettings::Get().Keyboard.Cursor = Color(
      color.keyboardCursorR, color.keyboardCursorG, color.keyboardCursorB);
  FwkSettings::Get().Keyboard.Input =
      Color(color.keyboardInputR, color.keyboardInputG, color.keyboardInputB);

  FwkSettings::Get().CustomKeyboard.BackgroundMain = Color(
      color.customKeyboardBackgroundMainR, color.customKeyboardBackgroundMainG,
      color.customKeyboardBackgroundMainB);
  FwkSettings::Get().CustomKeyboard.BackgroundSecondary =
      Color(color.customKeyboardBackgroundSecondaryR,
            color.customKeyboardBackgroundSecondaryG,
            color.customKeyboardBackgroundSecondaryB);
  FwkSettings::Get().CustomKeyboard.BackgroundBorder =
      Color(color.customKeyboardBackgroundBorderR,
            color.customKeyboardBackgroundBorderG,
            color.customKeyboardBackgroundBorderB);
  FwkSettings::Get().CustomKeyboard.KeyBackground = Color(
      color.customKeyboardKeyBackgroundR, color.customKeyboardKeyBackgroundG,
      color.customKeyboardKeyBackgroundB);
  FwkSettings::Get().CustomKeyboard.KeyBackgroundPressed =
      Color(color.customKeyboardKeyBackgroundPressedR,
            color.customKeyboardKeyBackgroundPressedG,
            color.customKeyboardKeyBackgroundPressedB);
  FwkSettings::Get().CustomKeyboard.KeyText =
      Color(color.customKeyboardKeyTextR, color.customKeyboardKeyTextG,
            color.customKeyboardKeyTextB);
  FwkSettings::Get().CustomKeyboard.KeyTextPressed = Color(
      color.customKeyboardKeyTextPressedR, color.customKeyboardKeyTextPressedG,
      color.customKeyboardKeyTextPressedB);
  FwkSettings::Get().CustomKeyboard.ScrollBarBackground =
      Color(color.customKeyboardScrollBarBackgroundR,
            color.customKeyboardScrollBarBackgroundG,
            color.customKeyboardScrollBarBackgroundB);
  FwkSettings::Get().CustomKeyboard.ScrollBarThumb = Color(
      color.customKeyboardScrollBarThumbR, color.customKeyboardScrollBarThumbG,
      color.customKeyboardScrollBarThumbB);
  file.Close();
}

void PatchProcessUiMainTextColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiMainTextR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiMainTextG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiMainTextB = value;
    }
  }
  FwkSettings::Get().MainTextColor =
      Color(color.uiMainTextR, color.uiMainTextG, color.uiMainTextB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiWindowTitleColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiWindowTitleR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiWindowTitleG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiWindowTitleB = value;
    }
  }
  FwkSettings::Get().WindowTitleColor =
      Color(color.uiWindowTitleR, color.uiWindowTitleG, color.uiWindowTitleB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiMenuSelectedItemColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiMenuSelectedItemR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiMenuSelectedItemG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiMenuSelectedItemB = value;
    }
  }
  FwkSettings::Get().MenuSelectedItemColor =
      Color(color.uiMenuSelectedItemR, color.uiMenuSelectedItemG,
            color.uiMenuSelectedItemB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiMenuUnselectedItemColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiMenuUnselectedItemR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiMenuUnselectedItemG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiMenuUnselectedItemB = value;
    }
  }
  FwkSettings::Get().MenuUnselectedItemColor =
      Color(color.uiMenuUnselectedItemR, color.uiMenuUnselectedItemG,
            color.uiMenuUnselectedItemB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiBackgroundMainColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiBackgroundMainR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiBackgroundMainG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiBackgroundMainB = value;
    }
  }
  FwkSettings::Get().BackgroundMainColor =
      Color(color.uiBackgroundMainR, color.uiBackgroundMainG,
            color.uiBackgroundMainB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiBackgroundSecondaryColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiBackgroundSecondaryR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiBackgroundSecondaryG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiBackgroundSecondaryB = value;
    }
  }
  FwkSettings::Get().BackgroundSecondaryColor =
      Color(color.uiBackgroundSecondaryR, color.uiBackgroundSecondaryG,
            color.uiBackgroundSecondaryB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessUiBackgroundBorderColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.uiBackgroundBorderR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.uiBackgroundBorderG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.uiBackgroundBorderB = value;
    }
  }
  FwkSettings::Get().BackgroundBorderColor =
      Color(color.uiBackgroundBorderR, color.uiBackgroundBorderG,
            color.uiBackgroundBorderB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardBackgroundColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardBackgroundR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardBackgroundG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardBackgroundB = value;
    }
  }
  FwkSettings::Get().Keyboard.Background =
      Color(color.keyboardBackgroundR, color.keyboardBackgroundG,
            color.keyboardBackgroundB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyBackgroundColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardKeyBackgroundR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardKeyBackgroundG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardKeyBackgroundB = value;
    }
  }
  FwkSettings::Get().Keyboard.KeyBackground =
      Color(color.keyboardKeyBackgroundR, color.keyboardKeyBackgroundG,
            color.keyboardKeyBackgroundB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyBackgroundPressedColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardKeyBackgroundPressedR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardKeyBackgroundPressedG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardKeyBackgroundPressedB = value;
    }
  }
  FwkSettings::Get().Keyboard.KeyBackgroundPressed = Color(
      color.keyboardKeyBackgroundPressedR, color.keyboardKeyBackgroundPressedG,
      color.keyboardKeyBackgroundPressedB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyTextColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextB = value;
    }
  }
  FwkSettings::Get().Keyboard.KeyText = Color(
      color.keyboardKeyTextR, color.keyboardKeyTextG, color.keyboardKeyTextB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyTextPressedColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextPressedR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextPressedG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextPressedB = value;
    }
  }
  FwkSettings::Get().Keyboard.KeyTextPressed =
      Color(color.keyboardKeyTextPressedR, color.keyboardKeyTextPressedG,
            color.keyboardKeyTextPressedB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardKeyTextDisabledColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextDisabledR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextDisabledG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardKeyTextDisabledB = value;
    }
  }
  FwkSettings::Get().Keyboard.KeyTextDisabled =
      Color(color.keyboardKeyTextDisabledR, color.keyboardKeyTextDisabledG,
            color.keyboardKeyTextDisabledB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardCursorColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardCursorR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardCursorG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardCursorB = value;
    }
  }
  FwkSettings::Get().Keyboard.Cursor = Color(
      color.keyboardCursorR, color.keyboardCursorG, color.keyboardCursorB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessKeyboardInputColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.keyboardInputR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.keyboardInputG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.keyboardInputB = value;
    }
  }
  FwkSettings::Get().Keyboard.Input =
      Color(color.keyboardInputR, color.keyboardInputG, color.keyboardInputB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardBackgroundMainColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundMainR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundMainG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundMainB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.BackgroundMain = Color(
      color.customKeyboardBackgroundMainR, color.customKeyboardBackgroundMainG,
      color.customKeyboardBackgroundMainB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardBackgroundSecondaryColorEditor(
    MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundSecondaryR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundSecondaryG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundSecondaryB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.BackgroundSecondary =
      Color(color.customKeyboardBackgroundSecondaryR,
            color.customKeyboardBackgroundSecondaryG,
            color.customKeyboardBackgroundSecondaryB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardBackgroundBorderColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundBorderR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundBorderG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardBackgroundBorderB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.BackgroundBorder =
      Color(color.customKeyboardBackgroundBorderR,
            color.customKeyboardBackgroundBorderG,
            color.customKeyboardBackgroundBorderB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyBackgroundColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyBackgroundR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyBackgroundG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyBackgroundB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.KeyBackground = Color(
      color.customKeyboardKeyBackgroundR, color.customKeyboardKeyBackgroundG,
      color.customKeyboardKeyBackgroundB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyBackgroundPressedColorEditor(
    MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyBackgroundPressedR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyBackgroundPressedG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyBackgroundPressedB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.KeyBackgroundPressed =
      Color(color.customKeyboardKeyBackgroundPressedR,
            color.customKeyboardKeyBackgroundPressedG,
            color.customKeyboardKeyBackgroundPressedB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyTextColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyTextR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyTextG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyTextB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.KeyText =
      Color(color.customKeyboardKeyTextR, color.customKeyboardKeyTextG,
            color.customKeyboardKeyTextB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardKeyTextPressedColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyTextPressedR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyTextPressedG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardKeyTextPressedB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.KeyTextPressed = Color(
      color.customKeyboardKeyTextPressedR, color.customKeyboardKeyTextPressedG,
      color.customKeyboardKeyTextPressedB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardScrollBarBackgroundColorEditor(
    MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardScrollBarBackgroundR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardScrollBarBackgroundG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardScrollBarBackgroundB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.ScrollBarBackground =
      Color(color.customKeyboardScrollBarBackgroundR,
            color.customKeyboardScrollBarBackgroundG,
            color.customKeyboardScrollBarBackgroundB);
  file.Rewind();
  file.Write((char *)&color, sizeof(color));
  file.Close();
}

void PatchProcessCustomKeyboardScrollBarThumbColorEditor(MenuEntry *entry) {
  File file;
  if (!File::Exists(pathToBIN)) {
    CreateDefaultFile();
  }
  PatchColorData color;
  File::Open(file, pathToBIN);
  file.Read((char *)&color, sizeof(color));
  Keyboard key("どの値を変更しますか？", {"R", "G", "B"});
  u8 value = 0;
  int choice = key.Open();
  if (choice == 0) {
    if (key.Open(value) == 0) {
      color.customKeyboardScrollBarThumbR = value;
    }
  } else if (choice == 1) {
    if (key.Open(value) == 0) {
      color.customKeyboardScrollBarThumbG = value;
    }
  } else if (choice == 2) {
    if (key.Open(value) == 0) {
      color.customKeyboardScrollBarThumbB = value;
    }
  }
  FwkSettings::Get().CustomKeyboard.ScrollBarThumb = Color(
      color.customKeyboardScrollBarThumbR, color.customKeyboardScrollBarThumbG,
      color.customKeyboardScrollBarThumbB);
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