#ifndef __CPP_UTILS_HPP__
#define __CPP_UTILS_HPP__
#include <iomanip>

#define _XSTR(s) _STR(s)
#define _STR(s) #s

// simply sets the type, you need to add the 0x
#define HEX_STRING(n) std::hex << (n) << std::dec



// forces a witdth of 8 characters and sets mode to hex does not add 0x
#define HEX8_STRING(n)  std::setfill('0') << std::setw(2) << std::hex << (n) << std::dec
#define HEX16_STRING(n) std::setfill('0') << std::setw(4) << std::hex << (n) << std::dec
#define HEX32_STRING(n) std::setfill('0') << std::setw(8) << std::hex << (n) << std::dec
#define HEX64_STRING(n) std::setfill('0') << std::setw(16) << std::hex << (n) << std::dec

#endif