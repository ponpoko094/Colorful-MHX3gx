//
// Created by ponpoko on 2021/03/21.
//

#include "libpon/osd_plus.hpp"

namespace CTRPluginFramework {

namespace libpon {

u32 OsdPlus::Draw(const std::string& str, u32 pos_x, u32 pos_y,
                  const Screen& screen, const Color& foreground,
                  const Color& background) {
  screen.Draw(str, pos_x, pos_y, foreground, background);
  return pos_y + 10;
}

u32 OsdPlus::DrawSystemFont(const std::string& str, u32 pos_x, u32 pos_y,
                            const Screen& screen, const Color& foreground,
                            const Color& background) {
  float text_width = OSD::GetTextWidth(true, str);
  screen.DrawRect(pos_x, pos_y, (u32)text_width, 16, background);
  screen.DrawSysfont(str, pos_x, pos_y, foreground);
  return pos_y + 16;
}
}  // namespace libpon

}  // namespace CTRPluginFramework
