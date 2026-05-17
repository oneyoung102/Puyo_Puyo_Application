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
enum class Arcade
{
    NONE,
    solo,
    duel,
    bot
};
enum class Diff
{
    NONE,
    easy,
    normal,
    hard
};
enum class Mode
{
    NONE,
    basic,
    speed,
    bomb,
    frozen,
    charged,
};

class puyoPageSignal
{
    public :
        std::optional<Page> next_page;

        std::optional<Arcade> arcade;
        std::optional<Diff> diff;//난이도
        std::optional<Mode> mode;//게임 모드

        std::optional<int> win_player_num;

        std::optional<bool> request_capture;

        puyoPageSignal& operator=(const puyoPageSignal& other)
        {
            if(this == &other)
                return *this;
            this->next_page = other.next_page;
            if(this->next_page)//값이 존재해야 함. 즉 페이지 전환이 이루어져야
            {
                if(other.arcade)
                    this->arcade = *other.arcade;
                if(other.diff)
                    this->diff = *other.diff;
                if(other.mode)
                    this->mode = *other.mode;
                if(other.win_player_num)
                    this->win_player_num = *other.win_player_num;
                if(other.request_capture)
                    this->request_capture = *other.request_capture;
            }
            return *this;
        }
};