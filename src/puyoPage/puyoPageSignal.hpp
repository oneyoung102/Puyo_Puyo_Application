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
enum Play_mode
{
    solo,
    dual,
    bot
};

struct puyoPageSignal
{
    Page next_page = Page::none;

    std::optional<Play_mode> play_mode;
    std::optional<int> gravity;
    std::optional<int> colors;

    std::optional<int> win_player_num;

    std::optional<bool> request_capture;
};