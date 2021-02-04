#ifndef COMMON_HPP
#define COMMON_HPP

#include "3ds.h"
#include "csvc.h"
#include "CTRPluginFramework.hpp"
#include "cheats.hpp"
#include "patch.hpp"
#include "keyboard.hpp"
#include "Helpers.hpp"
#include "Unicode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstdio>
#include <ctime>
#include <string>
#include <ctime>
#include <cmath>
#include <math.h>
#include <random>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

#define DU DPadUp
#define DD DPadDown
#define DL DPadLeft
#define DR DPadRight
#define CU CPadUp
#define CD CPadDown
#define CL CPadLeft
#define CR CPadRight

namespace CTRPluginFramework
{
    using CallbackPointer = void (*)(void);
    using StringVector = std::vector<std::string>;
} // namespace CTRPluginFramework

#endif