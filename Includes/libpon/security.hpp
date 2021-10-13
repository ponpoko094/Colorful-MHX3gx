#ifndef MHX3GX_INCLUDES_LIBPON_SECURITY_HPP_
#define MHX3GX_INCLUDES_LIBPON_SECURITY_HPP_

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

#endif  // MHX3GX_INCLUDES_LIBPON_SECURITY_HPP_