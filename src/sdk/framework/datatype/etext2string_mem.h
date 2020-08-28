#pragma once

#include "../../encoding/encoding.h"

// 将etext赋予::std::string，constexpr产生隐式inline等
constexpr auto string_e2std = [](::std::string &member, const etext &src) {
    if (src != nullptr)
        member = e2s_s(src);
};