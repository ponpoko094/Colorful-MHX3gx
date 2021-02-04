#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include <common.hpp>

namespace CTRPluginFramework
{
    class KBD
    {
    public:
        static bool Set(const std::string message, bool hexadecimal, const int length, u32 output, u32 define);
        static bool Set(const std::string message, bool hexadecimal, const int length, u16 output, u16 define);
        static bool Set(const std::string message, bool hexadecimal, const int length, u8 output, u8 define);
        static void Toggle32(const std::string message, u32 offset, u32 enable, u32 disable);
        static void Toggle16(const std::string message, u32 offset, u16 enable, u16 disable);
        static void Toggle8(const std::string message, u32 offset, u8 enable, u8 disable);

        // @param message Set keyboard message
        // @param value [offset][enabled][disabled]
        static void SToggle32(const std::string message, std::vector<std::vector<u32>> value);

        // Delete keyboard object
        static void Clean();
    };
} // namespace CTRPluginFramework

#endif