#ifndef CTRPLUGINFRAMEWORK_UTILS_STRINGEXTENSIONS_HPP
#define CTRPLUGINFRAMEWORK_UTILS_STRINGEXTENSIONS_HPP

#include "CTRPluginFramework/Graphics/Color.hpp"
#include <string>
#include <type_traits>

namespace CTRPluginFramework
{
    // Return a string with the charcter that reset the color (0x18)
    std::string     ResetColor(void);

    // Allows to use the flags from Render::FontDrawMode to draw text in different modes.
    std::string     ToggleDrawMode(u32 flags);

    // Makes the text draw function skip to the specified X pixel.
    std::string     SkipToPixel(u16 px);

    // Aligns the string to the center of the specified borders. (Default values = top window size)
    std::string     CenterAlign(const std::string& str, u16 leftBorder = 35, u16 rightBorder = 370);

    // Aligns the string to the right of the specified borders. (Default values = top window size)
    std::string     RightAlign(const std::string& str, u16 leftBorder = 35, u16 rightBorder = 370);

    std::string operator <<(const std::string &left, const char *right);
    std::string operator <<(const std::string &left, const std::string &right);

    template <typename T,
        typename std::enable_if<
        !std::is_same<T, const char *>::value
        && !std::is_same<T, Color>::value
    >::type* = nullptr>
    std::string operator <<(const std::string &left, T right)
    {
        return (left + std::to_string(right));
    }
}

#endif
