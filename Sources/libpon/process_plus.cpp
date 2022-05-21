#include "libpon/process_plus.hpp"

namespace CTRPluginFramework {

void ProcessPlus::GetLengthAddress(u32 base_address, int length,
                                   std::vector<u32> address) {
  for (int i = 0; i < length; i++) {
    address.push_back(base_address + i * 0x4);
  }
}

void ProcessPlus::Write8(u32 address, u8 value) {
  Process::Write8(address, value);
}

void ProcessPlus::Write8(const std::vector<u32> &address, u8 value) {
  for (unsigned int addr : address) {
    Process::Write8(addr, value);
  }
}

void ProcessPlus::Write8(std::vector<u32> address, std::vector<u8> value) {
  for (int i = 0; i < address.size(); i++) {
    Process::Write8(address[i], value[i]);
  }
}

void ProcessPlus::Write8(u32 pointer, u32 offset, u8 value) {
  u32 address;
  Process::Read32(pointer, address);
  Process::Write8(address + offset, value);
}

void ProcessPlus::Write8(const std::vector<u32> &pointer, u32 offset,
                         u8 value) {
  u32 address;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address);
    Process::Write8(address + offset, value);
  }
}

void ProcessPlus::Write8(std::vector<u32> pointer, u32 offset,
                         std::vector<u8> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write8(address + offset, value[i]);
  }
}

void ProcessPlus::Write8(std::vector<u32> pointer, std::vector<u32> offset,
                         u8 value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write8(address + offset[i], value);
  }
}

void ProcessPlus::Write8(std::vector<u32> pointer, std::vector<u32> offset,
                         std::vector<u8> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write8(address + offset[i], value[i]);
  }
}

void ProcessPlus::Write8(u32 pointer, u32 offset_1, u32 offset_2, u8 value) {
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  Process::Read32(address_1 + offset_1, address_2);
  Process::Write8(address_2 + offset_2, value);
}

void ProcessPlus::Write8(const std::vector<u32> &pointer, u32 offset_1,
                         u32 offset_2, u8 value) {
  u32 address_1;
  u32 address_2;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address_1);
    Process::Read32(address_1 + offset_1, address_2);
    Process::Write8(address_2 + offset_2, value);
  }
}

void ProcessPlus::Write16(u32 address, u16 value) {
  Process::Write16(address, value);
}

void ProcessPlus::Write16(const std::vector<u32> &address, u16 value) {
  for (unsigned int addr : address) {
    Process::Write16(addr, value);
  }
}

void ProcessPlus::Write16(std::vector<u32> address, std::vector<u16> value) {
  for (int i = 0; i < address.size(); i++) {
    Process::Write16(address[i], value[i]);
  }
}

void ProcessPlus::Write16(u32 pointer, u32 offset, u16 value) {
  u32 address;
  Process::Read32(pointer, address);
  Process::Write16(address + offset, value);
}

void ProcessPlus::Write16(const std::vector<u32> &pointer, u32 offset,
                          u16 value) {
  u32 address;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address);
    Process::Write16(address + offset, value);
  }
}

void ProcessPlus::Write16(std::vector<u32> pointer, u32 offset,
                          std::vector<u16> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write16(address + offset, value[i]);
  }
}

void ProcessPlus::Write16(std::vector<u32> pointer, std::vector<u32> offset,
                          u16 value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write16(address + offset[i], value);
  }
}

void ProcessPlus::Write16(std::vector<u32> pointer, std::vector<u32> offset,
                          std::vector<u16> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write16(address + offset[i], value[i]);
  }
}

void ProcessPlus::Write16(u32 pointer, u32 offset_1, u32 offset_2, u16 value) {
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  Process::Read32(address_1 + offset_1, address_2);
  Process::Write16(address_2 + offset_2, value);
}

void ProcessPlus::Write16(const std::vector<u32> &pointer, u32 offset_1,
                          u32 offset_2, u16 value) {
  u32 address_1;
  u32 address_2;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address_1);
    Process::Read32(address_1 + offset_1, address_2);
    Process::Write16(address_2 + offset_2, value);
  }
}

void ProcessPlus::Write32(u32 address, u32 value) {
  Process::Write32(address, value);
}

void ProcessPlus::Write32(const std::vector<u32> &address, u32 value) {
  for (unsigned int addr : address) {
    Process::Write32(addr, value);
  }
}

void ProcessPlus::Write32(std::vector<u32> address, std::vector<u32> value) {
  for (int i = 0; i < address.size(); i++) {
    Process::Write32(address[i], value[i]);
  }
}

void ProcessPlus::Write32(u32 pointer, u32 offset, u32 value) {
  u32 address;
  Process::Read32(pointer, address);
  Process::Write32(address + offset, value);
}

void ProcessPlus::Write32(const std::vector<u32> &pointer, u32 offset,
                          u32 value) {
  u32 address;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address);
    Process::Write32(address + offset, value);
  }
}

void ProcessPlus::Write32(std::vector<u32> pointer, u32 offset,
                          std::vector<u32> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write32(address + offset, value[i]);
  }
}

void ProcessPlus::Write32(std::vector<u32> pointer, std::vector<u32> offset,
                          u32 value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write32(address + offset[i], value);
  }
}

void ProcessPlus::Write32(std::vector<u32> pointer, std::vector<u32> offset,
                          std::vector<u32> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write32(address + offset[i], value[i]);
  }
}

void ProcessPlus::Write32(u32 pointer, u32 offset_1, u32 offset_2, u32 value) {
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  Process::Read32(address_1 + offset_1, address_2);
  Process::Write32(address_2 + offset_2, value);
}

void ProcessPlus::Write32(const std::vector<u32> &pointer, u32 offset_1,
                          u32 offset_2, u32 value) {
  u32 address_1;
  u32 address_2;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address_1);
    Process::Read32(address_1 + offset_1, address_2);
    Process::Write32(address_2 + offset_2, value);
  }
}

void ProcessPlus::Write64(u32 address, u64 value) {
  Process::Write64(address, value);
}

void ProcessPlus::Write64(const std::vector<u32> &address, u64 value) {
  for (unsigned int addr : address) {
    Process::Write64(addr, value);
  }
}

void ProcessPlus::Write64(std::vector<u32> address, std::vector<u64> value) {
  for (int i = 0; i < address.size(); i++) {
    Process::Write64(address[i], value[i]);
  }
}

void ProcessPlus::Write64(u32 pointer, u32 offset, u64 value) {
  u32 address;
  Process::Read32(pointer, address);
  Process::Write64(address + offset, value);
}

void ProcessPlus::Write64(const std::vector<u32> &pointer, u32 offset,
                          u64 value) {
  u32 address;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address);
    Process::Write64(address + offset, value);
  }
}

void ProcessPlus::Write64(std::vector<u32> pointer, u32 offset,
                          std::vector<u64> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write64(address + offset, value[i]);
  }
}

void ProcessPlus::Write64(std::vector<u32> pointer, std::vector<u32> offset,
                          u64 value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write64(address + offset[i], value);
  }
}

void ProcessPlus::Write64(std::vector<u32> pointer, std::vector<u32> offset,
                          std::vector<u64> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::Write64(address + offset[i], value[i]);
  }
}

void ProcessPlus::Write64(u32 pointer, u32 offset_1, u32 offset_2, u64 value) {
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  Process::Read32(address_1 + offset_1, address_2);
  Process::Write64(address_2 + offset_2, value);
}

void ProcessPlus::Write64(const std::vector<u32> &pointer, u32 offset_1,
                          u32 offset_2, u64 value) {
  u32 address_1;
  u32 address_2;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address_1);
    Process::Read32(address_1 + offset_1, address_2);
    Process::Write64(address_2 + offset_2, value);
  }
}

void ProcessPlus::WriteFloat(u32 address, float value) {
  Process::WriteFloat(address, value);
}

void ProcessPlus::WriteFloat(const std::vector<u32> &address, float value) {
  for (unsigned int addr : address) {
    Process::WriteFloat(addr, value);
  }
}

void ProcessPlus::WriteFloat(std::vector<u32> address,
                             std::vector<float> value) {
  for (int i = 0; i < address.size(); i++) {
    Process::WriteFloat(address[i], value[i]);
  }
}

void ProcessPlus::WriteFloat(u32 pointer, u32 offset, float value) {
  u32 address;
  Process::Read32(pointer, address);
  Process::WriteFloat(address + offset, value);
}

void ProcessPlus::WriteFloat(const std::vector<u32> &pointer, u32 offset,
                             float value) {
  u32 address;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address);
    Process::WriteFloat(address + offset, value);
  }
}

void ProcessPlus::WriteFloat(std::vector<u32> pointer, u32 offset,
                             std::vector<float> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::WriteFloat(address + offset, value[i]);
  }
}

void ProcessPlus::WriteFloat(std::vector<u32> pointer, std::vector<u32> offset,
                             float value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::WriteFloat(address + offset[i], value);
  }
}

void ProcessPlus::WriteFloat(std::vector<u32> pointer, std::vector<u32> offset,
                             std::vector<float> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::WriteFloat(address + offset[i], value[i]);
  }
}

void ProcessPlus::WriteFloat(u32 pointer, u32 offset_1, u32 offset_2,
                             float value) {
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  Process::Read32(address_1 + offset_1, address_2);
  Process::WriteFloat(address_2 + offset_2, value);
}

void ProcessPlus::WriteFloat(const std::vector<u32> &pointer, u32 offset_1,
                             u32 offset_2, float value) {
  u32 address_1;
  u32 address_2;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address_1);
    Process::Read32(address_1 + offset_1, address_2);
    Process::WriteFloat(address_2 + offset_2, value);
  }
}

void ProcessPlus::WriteDouble(u32 address, double value) {
  Process::WriteDouble(address, value);
}

void ProcessPlus::WriteDouble(const std::vector<u32> &address, double value) {
  for (unsigned int addr : address) {
    Process::WriteDouble(addr, value);
  }
}

void ProcessPlus::WriteDouble(std::vector<u32> address,
                              std::vector<double> value) {
  for (int i = 0; i < address.size(); i++) {
    Process::WriteDouble(address[i], value[i]);
  }
}

void ProcessPlus::WriteDouble(u32 pointer, u32 offset, double value) {
  u32 address;
  Process::Read32(pointer, address);
  Process::WriteDouble(address + offset, value);
}

void ProcessPlus::WriteDouble(const std::vector<u32> &pointer, u32 offset,
                              double value) {
  u32 address;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address);
    Process::WriteDouble(address + offset, value);
  }
}

void ProcessPlus::WriteDouble(std::vector<u32> pointer, u32 offset,
                              std::vector<double> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::WriteDouble(address + offset, value[i]);
  }
}

void ProcessPlus::WriteDouble(std::vector<u32> pointer, std::vector<u32> offset,
                              double value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::WriteDouble(address + offset[i], value);
  }
}

void ProcessPlus::WriteDouble(std::vector<u32> pointer, std::vector<u32> offset,
                              std::vector<double> value) {
  u32 address;
  for (int i = 0; i < pointer.size(); i++) {
    Process::Read32(pointer[i], address);
    Process::WriteDouble(address + offset[i], value[i]);
  }
}

void ProcessPlus::WriteDouble(u32 pointer, u32 offset_1, u32 offset_2,
                              double value) {
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  Process::Read32(address_1 + offset_1, address_2);
  Process::WriteDouble(address_2 + offset_2, value);
}

void ProcessPlus::WriteDouble(const std::vector<u32> &pointer, u32 offset_1,
                              u32 offset_2, double value) {
  u32 address_1;
  u32 address_2;
  for (unsigned int addr : pointer) {
    Process::Read32(addr, address_1);
    Process::Read32(address_1 + offset_1, address_2);
    Process::WriteDouble(address_2 + offset_2, value);
  }
}

u8 ProcessPlus::Read8(u32 address) {
  u8 value;
  Process::Read8(address, value);
  return value;
}

u8 ProcessPlus::Read8(u32 pointer, u32 offset) {
  u32 address;
  u8 value;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read8(address + offset, value);
    return value;
  }
  return 0;
}

u8 ProcessPlus::Read8(u32 pointer, u32 offset_1, u32 offset_2) {
  u32 address_1;
  u32 address_2;
  u8 value;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read8(address_2 + offset_2, value);
      return value;
    }
  }
  return 0;
}

u16 ProcessPlus::Read16(u32 address) {
  u16 value;
  Process::Read16(address, value);
  return value;
}

u16 ProcessPlus::Read16(u32 pointer, u32 offset) {
  u32 address;
  u16 value;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read16(address + offset, value);
    return value;
  }
  return 0;
}

u16 ProcessPlus::Read16(u32 pointer, u32 offset_1, u32 offset_2) {
  u32 address_1;
  u32 address_2;
  u16 value;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read16(address_2 + offset_2, value);
      return value;
    }
  }
  return 0;
}

u32 ProcessPlus::Read32(u32 address) {
  u32 value;
  Process::Read32(address, value);
  return value;
}

u32 ProcessPlus::Read32(u32 pointer, u32 offset) {
  u32 address;
  u32 value;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read32(address + offset, value);
    return value;
  }
  return 0;
}

u32 ProcessPlus::Read32(u32 pointer, u32 offset_1, u32 offset_2) {
  u32 address_1;
  u32 address_2;
  u32 value;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read32(address_2 + offset_2, value);
      return value;
    }
  }
  return 0;
}

u64 ProcessPlus::Read64(u32 address) {
  u64 value;
  Process::Read64(address, value);
  return value;
}

u64 ProcessPlus::Read64(u32 pointer, u32 offset) {
  u32 address;
  u64 value;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read64(address + offset, value);
    return value;
  }
  return 0;
}

u64 ProcessPlus::Read64(u32 pointer, u32 offset_1, u32 offset_2) {
  u32 address_1;
  u32 address_2;
  u64 value;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read64(address_2 + offset_2, value);
      return value;
    }
  }
  return 0;
}

float ProcessPlus::ReadFloat(u32 address) {
  float value;
  Process::ReadFloat(address, value);
  return value;
}

float ProcessPlus::ReadFloat(u32 pointer, u32 offset) {
  u32 address;
  float value;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::ReadFloat(address + offset, value);
    return value;
  }
  return 0;
}

float ProcessPlus::ReadFloat(u32 pointer, u32 offset_1, u32 offset_2) {
  u32 address_1;
  u32 address_2;
  float value;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::ReadFloat(address_2 + offset_2, value);
      return value;
    }
  }
  return 0;
}

double ProcessPlus::ReadDouble(u32 address) {
  double value;
  Process::ReadDouble(address, value);
  return value;
}

double ProcessPlus::ReadDouble(u32 pointer, u32 offset) {
  u32 address;
  double value;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::ReadDouble(address + offset, value);
    return value;
  }
  return 0;
}

double ProcessPlus::ReadDouble(u32 pointer, u32 offset_1, u32 offset_2) {
  u32 address_1;
  u32 address_2;
  double value;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::ReadDouble(address_2 + offset_2, value);
      return value;
    }
  }
  return 0;
}

void ProcessPlus::Add8(u32 address, u8 increase_value) {
  u8 data;
  Process::Read8(address, data);
  Process::Write8(address, data + increase_value);
}

void ProcessPlus::Add8(u32 pointer, u32 offset, u8 increase_value) {
  u8 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read8(address + offset, data);
    Process::Write8(address + offset, data + increase_value);
  }
}

void ProcessPlus::Add8(u32 pointer, u32 offset_1, u32 offset_2,
                       u8 increase_value) {
  u8 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read8(address_2 + offset_2, data);
      Process::Write8(address_2 + offset_2, data + increase_value);
    }
  }
}

void ProcessPlus::Add16(u32 address, u16 increase_value) {
  u16 data;
  Process::Read16(address, data);
  Process::Write16(address, data + increase_value);
}

void ProcessPlus::Add16(u32 pointer, u32 offset, u16 increase_value) {
  u16 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read16(address + offset, data);
    Process::Write16(address + offset, data + increase_value);
  }
}

void ProcessPlus::Add16(u32 pointer, u32 offset_1, u32 offset_2,
                        u16 increase_value) {
  u16 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read16(address_2 + offset_2, data);
      Process::Write16(address_2 + offset_2, data + increase_value);
    }
  }
}

void ProcessPlus::Add32(u32 address, u32 increase_value) {
  u32 data;
  Process::Read32(address, data);
  Process::Write32(address, data + increase_value);
}

void ProcessPlus::Add32(u32 pointer, u32 offset, u32 increase_value) {
  u32 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read32(address + offset, data);
    Process::Write32(address + offset, data + increase_value);
  }
}

void ProcessPlus::Add32(u32 pointer, u32 offset_1, u32 offset_2,
                        u32 increase_value) {
  u32 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read32(address_2 + offset_2, data);
      Process::Write32(address_2 + offset_2, data + increase_value);
    }
  }
}

void ProcessPlus::Add64(u32 address, u64 increase_value) {
  u64 data;
  Process::Read64(address, data);
  Process::Write64(address, data + increase_value);
}

void ProcessPlus::Add64(u32 pointer, u32 offset, u64 increase_value) {
  u64 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read64(address + offset, data);
    Process::Write64(address + offset, data + increase_value);
  }
}

void ProcessPlus::Add64(u32 pointer, u32 offset_1, u32 offset_2,
                        u64 increase_value) {
  u64 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read64(address_2 + offset_2, data);
      Process::Write64(address_2 + offset_2, data + increase_value);
    }
  }
}

void ProcessPlus::AddFloat(u32 address, float increase_value) {
  float data;
  Process::ReadFloat(address, data);
  Process::WriteFloat(address, data + increase_value);
}

void ProcessPlus::AddFloat(u32 pointer, u32 offset, float increase_value) {
  float data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::ReadFloat(address + offset, data);
    Process::WriteFloat(address + offset, data + increase_value);
  }
}

void ProcessPlus::AddFloat(u32 pointer, u32 offset_1, u32 offset_2,
                           float increase_value) {
  float data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::ReadFloat(address_2 + offset_2, data);
      Process::WriteFloat(address_2 + offset_2, data + increase_value);
    }
  }
}

void ProcessPlus::AddDouble(u32 address, double increase_value) {
  double data;
  Process::ReadDouble(address, data);
  Process::WriteDouble(address, data + increase_value);
}

void ProcessPlus::AddDouble(u32 pointer, u32 offset, double increase_value) {
  double data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::ReadDouble(address + offset, data);
    Process::WriteDouble(address + offset, data + increase_value);
  }
}

void ProcessPlus::AddDouble(u32 pointer, u32 offset_1, u32 offset_2,
                            double increase_value) {
  double data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::ReadDouble(address_2 + offset_2, data);
      Process::WriteDouble(address_2 + offset_2, data + increase_value);
    }
  }
}

void ProcessPlus::Sub8(u32 address, u8 decrease_value) {
  u8 data;
  Process::Read8(address, data);
  Process::Write8(address, data - decrease_value);
}

void ProcessPlus::Sub8(u32 pointer, u32 offset, u8 decrease_value) {
  u8 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read8(address + offset, data);
    Process::Write8(address + offset, data - decrease_value);
  }
}

void ProcessPlus::Sub8(u32 pointer, u32 offset_1, u32 offset_2,
                       u8 decrease_value) {
  u8 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read8(address_2 + offset_2, data);
      Process::Write8(address_2 + offset_2, data - decrease_value);
    }
  }
}

void ProcessPlus::Sub16(u32 address, u16 decrease_value) {
  u16 data;
  Process::Read16(address, data);
  Process::Write16(address, data - decrease_value);
}

void ProcessPlus::Sub16(u32 pointer, u32 offset, u16 decrease_value) {
  u16 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read16(address + offset, data);
    Process::Write16(address + offset, data - decrease_value);
  }
}

void ProcessPlus::Sub16(u32 pointer, u32 offset_1, u32 offset_2,
                        u16 decrease_value) {
  u16 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read16(address_2 + offset_2, data);
      Process::Write16(address_2 + offset_2, data - decrease_value);
    }
  }
}

void ProcessPlus::Sub32(u32 address, u32 decrease_value) {
  u32 data;
  Process::Read32(address, data);
  Process::Write32(address, data - decrease_value);
}

void ProcessPlus::Sub32(u32 pointer, u32 offset, u32 decrease_value) {
  u32 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read32(address + offset, data);
    Process::Write32(address + offset, data - decrease_value);
  }
}

void ProcessPlus::Sub32(u32 pointer, u32 offset_1, u32 offset_2,
                        u32 decrease_value) {
  u32 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read32(address_2 + offset_2, data);
      Process::Write32(address_2 + offset_2, data - decrease_value);
    }
  }
}

void ProcessPlus::Sub64(u32 address, u64 decrease_value) {
  u64 data;
  Process::Read64(address, data);
  Process::Write64(address, data - decrease_value);
}

void ProcessPlus::Sub64(u32 pointer, u32 offset, u64 decrease_value) {
  u64 data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::Read64(address + offset, data);
    Process::Write64(address + offset, data - decrease_value);
  }
}

void ProcessPlus::Sub64(u32 pointer, u32 offset_1, u32 offset_2,
                        u64 decrease_value) {
  u64 data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::Read64(address_2 + offset_2, data);
      Process::Write64(address_2 + offset_2, data - decrease_value);
    }
  }
}

void ProcessPlus::SubFloat(u32 address, float decrease_value) {
  float data;
  Process::ReadFloat(address, data);
  Process::WriteFloat(address, data - decrease_value);
}

void ProcessPlus::SubFloat(u32 pointer, u32 offset, float decrease_value) {
  float data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::ReadFloat(address + offset, data);
    Process::WriteFloat(address + offset, data - decrease_value);
  }
}

void ProcessPlus::SubFloat(u32 pointer, u32 offset_1, u32 offset_2,
                           float decrease_value) {
  float data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::ReadFloat(address_2 + offset_2, data);
      Process::WriteFloat(address_2 + offset_2, data - decrease_value);
    }
  }
}

void ProcessPlus::SubDouble(u32 address, double decrease_value) {
  double data;
  Process::ReadDouble(address, data);
  Process::WriteDouble(address, data - decrease_value);
}

void ProcessPlus::SubDouble(u32 pointer, u32 offset, double decrease_value) {
  double data;
  u32 address;
  Process::Read32(pointer, address);
  if (address != 0) {
    Process::ReadDouble(address + offset, data);
    Process::WriteDouble(address + offset, data - decrease_value);
  }
}

void ProcessPlus::SubDouble(u32 pointer, u32 offset_1, u32 offset_2,
                            double decrease_value) {
  double data;
  u32 address_1;
  u32 address_2;
  Process::Read32(pointer, address_1);
  if (address_1 != 0) {
    Process::Read32(address_1 + offset_1, address_2);
    if (address_2 != 0) {
      Process::ReadDouble(address_2 + offset_2, data);
      Process::WriteDouble(address_2 + offset_2, data - decrease_value);
    }
  }
}

}  // namespace CTRPluginFramework