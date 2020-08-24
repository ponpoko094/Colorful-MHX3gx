#ifndef COMMON_HPP
#define COMMON_HPP

#include "3ds.h"
#include "csvc.h"
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
using StringVector = std::vector<std::string>;

struct Item
{
	const char *name;
};

void FakeError(MenuEntry *entry);
void Information(MenuEntry *entry);
void Calculator(MenuEntry *entry);
void HexToDec(MenuEntry *entry);
} // namespace CTRPluginFramework

#endif