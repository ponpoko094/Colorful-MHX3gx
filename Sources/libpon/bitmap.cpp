#include "libpon/bitmap.hpp"

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {

void Bitmap::Draw() {
  File bmp;
  File::Open(bmp, "*.bmp", File::READ);
  static bool is_draw = true;
  OSD::Run([](const Screen& screen) {
    if (!screen.IsTop) {
      return (false);
    }
    if (is_draw == true) {
      // for (int i = 0; i <) screen.DrawPixel(0, 0, );
      is_draw = false;
    }
    return (true);
  });
}

Bitmap::Bitmap() {}

Bitmap::~Bitmap() {}

}  // namespace CTRPluginFramework