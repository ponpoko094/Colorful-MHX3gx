#ifndef STDAFX_HPP
#define STDAFX_HPP

#include <3ds.h>

#include <CTRPluginFramework.hpp>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <istream>
#include <iterator>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Helpers.hpp"
#include "csvc.h"
#include "json.hpp"
#include "libpon.hpp"
#include "types.h"

namespace CTRPluginFramework {
using CallbackPointer = void (*)(void);
using StringVector = std::vector<std::string>;
}  // namespace CTRPluginFramework

#endif  // STDAFX_HPP