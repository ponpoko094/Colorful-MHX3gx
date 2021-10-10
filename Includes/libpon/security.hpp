#ifndef LIBPON_SECURITY_HPP
#define LIBPON_SECURITY_HPP

#include <3ds.h>

#include <CTRPluginFramework.hpp>
#include <string>

namespace CTRPluginFramework {
class Security {
 public:
  static u64 GetFriendCodeSeed();
  static u64 GetHashConsole();
};

}  // namespace CTRPluginFramework

#endif  // LIBPON_SECURITY_HPP