//
// Created by ponpoko on 2021/03/21.
//

#include "libpon.hpp"

namespace libpon {

u32 OsdPlus::Draw(const std::string &str, u32 pos_x, u32 pos_y, bool is_top,
                  const Color &foreground, const Color &background) {
  const Screen &top_screen = OSD::GetTopScreen();
  const Screen &bottom_screen = OSD::GetBottomScreen();
  if (is_top) {
    OSDManager.Lock();
    top_screen.Draw(str, pos_x, pos_y, foreground, background);
    OSDManager.Unlock();
  } else {
    OSDManager.Lock();
    bottom_screen.Draw(str, pos_x, pos_y, foreground, background);
    OSDManager.Unlock();
  }
  return pos_y + 10;
}

u32 OsdPlus::DrawSystemFont(const std::string &str, u32 pos_x, u32 pos_y,
                            bool is_top, const Color &foreground,
                            const Color &background) {
  float text_width = OSD::GetTextWidth(true, str);
  const Screen &top_screen = OSD::GetTopScreen();
  const Screen &bottom_screen = OSD::GetBottomScreen();
  if (is_top) {
    OSDManager.Lock();
    top_screen.DrawRect(pos_x, pos_y, (u32)text_width, 16, background);
    top_screen.DrawSysfont(str, pos_x, pos_y, foreground);
    OSDManager.Unlock();
  } else {
    OSDManager.Lock();
    bottom_screen.DrawRect(pos_x, pos_y, (u32)text_width, 16, background);
    bottom_screen.DrawSysfont(str, pos_x, pos_y, foreground);
    OSDManager.Unlock();
  }
  return pos_y + 16;
}
}  // namespace libpon
