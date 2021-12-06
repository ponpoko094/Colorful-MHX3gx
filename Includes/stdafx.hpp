#ifndef COLORFUL_MHX3GX_INCLUDES_STDAFX_HPP_
#define COLORFUL_MHX3GX_INCLUDES_STDAFX_HPP_

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
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Helpers.hpp"
#include "csvc.h"
#include "libpon.hpp"
#include "types.h"
#include "Unicode.h"

namespace CTRPluginFramework {
using CallbackPointer = void (*)();
using StringVector = std::vector<std::string>;
}  // namespace CTRPluginFramework

#endif  // COLORFUL_MHX3GX_INCLUDES_STDAFX_HPP_