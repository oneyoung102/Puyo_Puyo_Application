#pragma once
#include <optional>

enum class Page
{
    opening,
    menu,
    option,
    game,
    ending
};
enum class Play_mode
{
    solo,
    dual,
    bot
};

struct puyoPageSignal
{
    std::optional<Page> next_page;

    std::optional<Play_mode> play_mode;
    std::optional<int> condition;
    std::optional<int> gravity;
    std::optional<int> stay;
    std::optional<int> colors;

    std::optional<int> win_player_num;

    std::optional<bool> request_capture;

    puyoPageSignal& operator=(const puyoPageSignal& other)
    {
        if(this == &other)
            return *this;
        this->next_page = other.next_page;
        if(this->next_page)//값이 존재해야 함. 즉 페이지 전환이 이루어져야
        {
            if(other.play_mode)
                this->play_mode = *other.play_mode;
            if(other.condition)
                this->condition = *other.condition;
            if(other.gravity)
                this->gravity = *other.gravity;
            if(other.stay)
                this->stay = *other.stay;
            if(other.colors)
                this->colors = *other.colors;
            if(other.win_player_num)
                this->win_player_num = *other.win_player_num;
            if(other.request_capture)
                this->request_capture = *other.request_capture;
        }
        return *this;
    }
};