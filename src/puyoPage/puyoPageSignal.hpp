#pragma once
#include <optional>

enum class Page
{
    none,
    opening,
    menu,
    ready,
    game,
    ending
};

struct puyoPageSignal
{
    Page next_page = Page::none;

    std::optional<int> player_count;
    std::optional<int> gravity;
    std::optional<int> colors;

    std::optional<int> win_player_num;

    std::optional<bool> request_capture;
};