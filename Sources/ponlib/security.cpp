#include "ponlib/security.h"

namespace CTRPluginFramework {

u64 Security::GetFriendCodeSeed() {
  u64 friend_code_seed;
  PS_GetLocalFriendCodeSeed(&friend_code_seed);
  return friend_code_seed;
}

u64 Security::GetHashConsole() {
  u64 hash;
  CFGU_GenHashConsoleUnique(0, &hash);
  return hash;
}

}  // namespace CTRPluginFramework