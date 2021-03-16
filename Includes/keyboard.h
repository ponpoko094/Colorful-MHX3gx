#ifndef MHX3GX_INCLUDES_KEYBOARD_H_
#define MHX3GX_INCLUDES_KEYBOARD_H_
#include <CTRPluginFramework.hpp>
#include <string>
#include <vector>

namespace CTRPluginFramework {

using StringVector = std::vector<std::string>;

class KBD {
 public:
  static bool Set(const std::string message, bool hexadecimal, const int length,
                  u32 output, u32 define);
  static bool Set(const std::string message, bool hexadecimal, const int length,
                  u16 output, u16 define);
  static bool Set(const std::string message, bool hexadecimal, const int length,
                  u8 output, u8 define);
  static void Toggle32(const std::string message, u32 offset, u32 enable,
                       u32 disable);
  static void Toggle16(const std::string message, u32 offset, u16 enable,
                       u16 disable);
  static void Toggle8(const std::string message, u32 offset, u8 enable,
                      u8 disable);

  // KBD::Toggle32の複数版。
  // 主にアセンブリチートの切り替えに使う。
  // \param value [offset] = [0], [enabled_value] = [1], [disable_value] = [2]
  static void MultiToggle32(const std::string message,
                            std::vector<std::vector<u32>> value);

  // KBD::Toggle32ベース。アドレスが一定量増加し続き、値だけが変わる版。
  // 主にルーチンの書き込みの切り替えに使う。
  static void LengthToggle32(const std::string message, const int length,
                             u32 base_offset, std::vector<u32> value);

  // Delete keyboard object
  KBD(){};
  ~KBD();

 private:
  int choice_;
};

}  // namespace CTRPluginFramework

#endif  // MHX3GX_INCLUDES_KEYBOARD_H_