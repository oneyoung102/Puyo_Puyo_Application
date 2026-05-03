#pragma once

enum class puyoType
{
    blank = -1,
    red,
    green,
    blue,
    yellow,
    pupple,
    obstruct,
    tiny_bomb,
    mid_bomb,
    big_bomb,
    danger_bomb,
};

inline constexpr bool is_colored(puyoType type)
{
    return puyoType::red <= type && type <= puyoType::pupple;
}