//
// Created by ponpoko on 2021/03/21.
//

#include "libpon.hpp"

namespace libpon {

u32 OSDPlus::Draw(const std::string &str, u32 posX, u32 posY, bool isTop,
                  const Color &foreground, const Color &background) {
  const Screen &top_screen = OSD::GetTopScreen();
  const Screen &bottom_screen = OSD::GetBottomScreen();
  if (isTop) {
    OSDManager.Lock();
    top_screen.Draw(str, posX, posY, foreground, background);
    OSDManager.Unlock();
  } else {
    OSDManager.Lock();
    bottom_screen.Draw(str, posX, posY, foreground, background);
    OSDManager.Unlock();
  }
  return posY + 10;
}

u32 OSDPlus::DrawSystemFont(const std::string &str, u32 posX, u32 posY,
                            bool isTop, const Color &foreground,
                            const Color &background) {
  float text_width = OSD::GetTextWidth(true, str);
  const Screen &top_screen = OSD::GetTopScreen();
  const Screen &bottom_screen = OSD::GetBottomScreen();
  if (isTop) {
    OSDManager.Lock();
    top_screen.DrawRect(posX, posY, (u32)text_width, 16, background);
    top_screen.DrawSysfont(str, posX, posY, foreground);
    OSDManager.Unlock();
  } else {
    OSDManager.Lock();
    bottom_screen.DrawRect(posX, posY, (u32)text_width, 16, background);
    bottom_screen.DrawSysfont(str, posX, posY, foreground);
    OSDManager.Unlock();
  }
  return posY + 16;
}
}  // namespace libpon
