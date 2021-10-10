#ifndef MHX3GX_INCLUDES_LIBPON_OSD_PLUS_HPP_
#define MHX3GX_INCLUDES_LIBPON_OSD_PLUS_HPP_

#include <CTRPluginFramework.hpp>

#include "Helpers.hpp"

using namespace CTRPluginFramework;
namespace libpon {

class OsdPlus {
 public:
  // @return pos_y + 16
  static u32 Draw(const std::string &str, u32 pos_x, u32 pos_y, bool is_top,
                  const Color &foreground = Color::White,
                  const Color &background = Color::Black);

  // @return pos_y + 16
  static u32 DrawSystemFont(const std::string &str, u32 pos_x, u32 pos_y,
                            bool is_top, const Color &foreground = Color::White,
                            const Color &background = Color::Black);
};

}  // namespace libpon
#endif  // MHX3GX_INCLUDES_LIBPON_OSD_PLUS_HPP_
