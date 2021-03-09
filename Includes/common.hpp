#ifndef COMMON_HPP
#define COMMON_HPP

#include <3ds.h>
#include <CTRPluginFramework.hpp>
#include "csvc.h"
#include "cheats.hpp"
#include "patch.hpp"
#include "keyboard.hpp"
#include "Helpers.hpp"
#include "Unicode.h"
#include <string>
#include <vector>
#include <ctime>

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