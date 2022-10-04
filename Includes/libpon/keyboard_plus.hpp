#ifndef COLORFUL_MHX3GX_INCLUDES_LIBPON_KEYBOARD_PLUS_HPP_
#define COLORFUL_MHX3GX_INCLUDES_LIBPON_KEYBOARD_PLUS_HPP_
#include <CTRPluginFramework.hpp>
#include <string>
#include <vector>

namespace CTRPluginFramework {

using StringVector = std::vector<std::string>;

class KeyboardPlus {
 public:
  static bool Set(u32& input, const std::string& message = "",
                  bool hexadecimal = false);
  static bool Set(u16& input, const std::string& message = "",
                  bool hexadecimal = false);
  static bool Set(u8& input, const std::string& message = "",
                  bool hexadecimal = false);
  static bool Toggle32(const std::string& message, const u32& offset,
                       const u32& enable, const u32& disable);
  static bool Toggle16(const std::string& message, const u32& offset,
                       const u16& enable, const u16& disable);
  static bool Toggle8(const std::string& message, const u32& offset,
                      const u8& enable, const u8& disable);

  // KeyboardPlus::Toggle32の複数版。
  // 主にアセンブリチートの切り替えに使う。
  // \param value [offset] = [0], [enabled_value] = [1], [disable_value] = [2]
  static bool MultiToggle32(const std::string& message,
                            std::vector<std::vector<u32>> value);

  // KeyboardPlus::Toggle32ベース。アドレスが一定量増加し続き、値だけが変わる版。
  // 主にルーチンの書き込みの切り替えに使う。
  static bool LengthToggle32(const std::string& message, int length,
                             u32 base_offset, std::vector<u32> value);

  // Delete keyboard object
  KeyboardPlus() = default;
  ~KeyboardPlus();
};

}  // namespace CTRPluginFramework

#endif  // COLORFUL_MHX3GX_INCLUDES_LIBPON_KEYBOARD_PLUS_HPP_
