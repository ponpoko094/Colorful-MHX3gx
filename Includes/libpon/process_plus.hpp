#ifndef COLORFUL_MHX3GX_INCLUDES_LIBPON_PROCESS_PLUS_HPP_
#define COLORFUL_MHX3GX_INCLUDES_LIBPON_PROCESS_PLUS_HPP_

#include <CTRPluginFramework.hpp>

namespace CTRPluginFramework {

class ProcessPlus {
 public:
  static void GetLengthAddress(u32 base_address, int length,
                               std::vector<u32> address);

  static void Write8(u32 address, u8 value);
  static void Write8(const std::vector<u32>& address, u8 value);
  static void Write8(std::vector<u32> address, std::vector<u8> value);
  static void Write8(u32 pointer, u32 offset, u8 value);
  static void Write8(const std::vector<u32>& pointer, u32 offset, u8 value);
  static void Write8(std::vector<u32> pointer, u32 offset,
                     std::vector<u8> value);
  static void Write8(std::vector<u32> pointer, std::vector<u32> offset,
                     u8 value);
  static void Write8(std::vector<u32> pointer, std::vector<u32> offset,
                     std::vector<u8> value);
  static void Write8(u32 pointer, u32 offset_1, u32 offset_2, u8 value);
  static void Write8(const std::vector<u32>& pointer, u32 offset_1,
                     u32 offset_2, u8 value);

  static void Write16(u32 address, u16 value);
  static void Write16(const std::vector<u32>& address, u16 value);
  static void Write16(std::vector<u32> address, std::vector<u16> value);
  static void Write16(u32 pointer, u32 offset, u16 value);
  static void Write16(const std::vector<u32>& pointer, u32 offset, u16 value);
  static void Write16(std::vector<u32> pointer, u32 offset,
                      std::vector<u16> value);
  static void Write16(std::vector<u32> pointer, std::vector<u32> offset,
                      u16 value);
  static void Write16(std::vector<u32> pointer, std::vector<u32> offset,
                      std::vector<u16> value);
  static void Write16(u32 pointer, u32 offset_1, u32 offset_2, u16 value);
  static void Write16(const std::vector<u32>& pointer, u32 offset_1,
                      u32 offset_2, u16 value);

  static void Write32(u32 address, u32 value);
  static void Write32(const std::vector<u32>& address, u32 value);
  static void Write32(std::vector<u32> address, std::vector<u32> value);
  static void Write32(u32 pointer, u32 offset, u32 value);
  static void Write32(const std::vector<u32>& pointer, u32 offset, u32 value);
  static void Write32(std::vector<u32> pointer, u32 offset,
                      std::vector<u32> value);
  static void Write32(std::vector<u32> pointer, std::vector<u32> offset,
                      u32 value);
  static void Write32(std::vector<u32> pointer, std::vector<u32> offset,
                      std::vector<u32> value);
  static void Write32(u32 pointer, u32 offset_1, u32 offset_2, u32 value);
  static void Write32(const std::vector<u32>& pointer, u32 offset_1,
                      u32 offset_2, u32 value);

  static void Write64(u32 address, u64 value);
  static void Write64(const std::vector<u32>& address, u64 value);
  static void Write64(std::vector<u32> address, std::vector<u64> value);
  static void Write64(u32 pointer, u32 offset, u64 value);
  static void Write64(const std::vector<u32>& pointer, u32 offset, u64 value);
  static void Write64(std::vector<u32> pointer, u32 offset,
                      std::vector<u64> value);
  static void Write64(std::vector<u32> pointer, std::vector<u32> offset,
                      u64 value);
  static void Write64(std::vector<u32> pointer, std::vector<u32> offset,
                      std::vector<u64> value);
  static void Write64(u32 pointer, u32 offset_1, u32 offset_2, u64 value);
  static void Write64(const std::vector<u32>& pointer, u32 offset_1,
                      u32 offset_2, u64 value);

  static void WriteFloat(u32 address, float value);
  static void WriteFloat(const std::vector<u32>& address, float value);
  static void WriteFloat(std::vector<u32> address, std::vector<float> value);
  static void WriteFloat(u32 pointer, u32 offset, float value);
  static void WriteFloat(const std::vector<u32>& pointer, u32 offset,
                         float value);
  static void WriteFloat(std::vector<u32> pointer, u32 offset,
                         std::vector<float> value);
  static void WriteFloat(std::vector<u32> pointer, std::vector<u32> offset,
                         float value);
  static void WriteFloat(std::vector<u32> pointer, std::vector<u32> offset,
                         std::vector<float> value);
  static void WriteFloat(u32 pointer, u32 offset_1, u32 offset_2, float value);
  static void WriteFloat(const std::vector<u32>& pointer, u32 offset_1,
                         u32 offset_2, float value);

  static void WriteDouble(u32 address, double value);
  static void WriteDouble(const std::vector<u32>& address, double value);
  static void WriteDouble(std::vector<u32> address, std::vector<double> value);
  static void WriteDouble(u32 pointer, u32 offset, double value);
  static void WriteDouble(const std::vector<u32>& pointer, u32 offset,
                          double value);
  static void WriteDouble(std::vector<u32> pointer, u32 offset,
                          std::vector<double> value);
  static void WriteDouble(std::vector<u32> pointer, std::vector<u32> offset,
                          double value);
  static void WriteDouble(std::vector<u32> pointer, std::vector<u32> offset,
                          std::vector<double> value);
  static void WriteDouble(u32 pointer, u32 offset_1, u32 offset_2,
                          double value);
  static void WriteDouble(const std::vector<u32>& pointer, u32 offset_1,
                          u32 offset_2, double value);

  static u8 Read8(u32 address);
  static u8 Read8(u32 pointer, u32 offset);
  static u8 Read8(u32 pointer, u32 offset_1, u32 offset_2);

  static u16 Read16(u32 address);
  static u16 Read16(u32 pointer, u32 offset);
  static u16 Read16(u32 pointer, u32 offset_1, u32 offset_2);

  static u32 Read32(u32 address);
  static u32 Read32(u32 pointer, u32 offset);
  static u32 Read32(u32 pointer, u32 offset_1, u32 offset_2);

  static u64 Read64(u32 address);
  static u64 Read64(u32 pointer, u32 offset);
  static u64 Read64(u32 pointer, u32 offset_1, u32 offset_2);

  static float ReadFloat(u32 address);
  static float ReadFloat(u32 pointer, u32 offset);
  static float ReadFloat(u32 pointer, u32 offset_1, u32 offset_2);

  static double ReadDouble(u32 address);
  static double ReadDouble(u32 pointer, u32 offset);
  static double ReadDouble(u32 pointer, u32 offset_1, u32 offset_2);

  static void Add8(u32 address, u8 increase_value);
  static void Add8(u32 pointer, u32 offset, u8 increase_value);
  static void Add8(u32 pointer, u32 offset_1, u32 offset_2, u8 increase_value);

  static void Add16(u32 address, u16 increase_value);
  static void Add16(u32 pointer, u32 offset, u16 increase_value);
  static void Add16(u32 pointer, u32 offset_1, u32 offset_2,
                    u16 increase_value);

  static void Add32(u32 address, u32 increase_value);
  static void Add32(u32 pointer, u32 offset, u32 increase_value);
  static void Add32(u32 pointer, u32 offset_1, u32 offset_2,
                    u32 increase_value);

  static void Add64(u32 address, u64 increase_value);
  static void Add64(u32 pointer, u32 offset, u64 increase_value);
  static void Add64(u32 pointer, u32 offset_1, u32 offset_2,
                    u64 increase_value);

  static void AddFloat(u32 address, float increase_value);
  static void AddFloat(u32 pointer, u32 offset, float increase_value);
  static void AddFloat(u32 pointer, u32 offset_1, u32 offset_2,
                       float increase_value);

  static void AddDouble(u32 address, double increase_value);
  static void AddDouble(u32 pointer, u32 offset, double increase_value);
  static void AddDouble(u32 pointer, u32 offset_1, u32 offset_2,
                        double increase_value);

  static void Sub8(u32 address, u8 decrease_value);
  static void Sub8(u32 pointer, u32 offset, u8 decrease_value);
  static void Sub8(u32 pointer, u32 offset_1, u32 offset_2, u8 decrease_value);

  static void Sub16(u32 address, u16 decrease_value);
  static void Sub16(u32 pointer, u32 offset, u16 decrease_value);
  static void Sub16(u32 pointer, u32 offset_1, u32 offset_2,
                    u16 decrease_value);

  static void Sub32(u32 address, u32 decrease_value);
  static void Sub32(u32 pointer, u32 offset, u32 decrease_value);
  static void Sub32(u32 pointer, u32 offset_1, u32 offset_2,
                    u32 decrease_value);

  static void Sub64(u32 address, u64 decrease_value);
  static void Sub64(u32 pointer, u32 offset, u64 decrease_value);
  static void Sub64(u32 pointer, u32 offset_1, u32 offset_2,
                    u64 decrease_value);

  static void SubFloat(u32 address, float decrease_value);
  static void SubFloat(u32 pointer, u32 offset, float decrease_value);
  static void SubFloat(u32 pointer, u32 offset_1, u32 offset_2,
                       float decrease_value);

  static void SubDouble(u32 address, double decrease_value);
  static void SubDouble(u32 pointer, u32 offset, double decrease_value);
  static void SubDouble(u32 pointer, u32 offset_1, u32 offset_2,
                        double decrease_value);
};

}  // namespace CTRPluginFramework
#endif  // COLORFUL_MHX3GX_INCLUDES_LIBPON_PROCESS_PLUS_HPP_
