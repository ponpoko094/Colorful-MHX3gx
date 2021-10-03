#ifndef MHX3GX_INCLUDES_SECURITY_H_
#define MHX3GX_INCLUDES_SECURITY_H_

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

#endif  // MHX3GX_INCLUDES_SECURITY_H_