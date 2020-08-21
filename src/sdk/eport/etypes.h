#include <cstdint>

using ebyte = std::uint8_t;        // 易语言字节型
using eshort = std::int16_t;       // 易语言短整数型
using eint = std::int32_t;         // 易语言整数型
using elong = std::int64_t;        // 易语言长整数型
using efloat = float;              // 易语言小数型
using edouble = double;            // 易语言双精度小数型
using edate = std::uint64_t;       // 易语言日期时间型
using ebool = std::int32_t;        // 易语言逻辑型
using etext = const char *;        // 易语言文本型(GBK)
using ebin = const std::uint8_t *; // 易语言字节集
using esubptr = std::uintptr_t;    // 易语言子程序指针