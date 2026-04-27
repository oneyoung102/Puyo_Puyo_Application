#pragma once

#include <stdexcept>
#include <vector>
#include <queue>
#include <array>
#include <utility>
#include "puyoPage/puyoObjectSignal.hpp"
#include "puyoPos.hpp"

enum class puyoButtonCursorSignal
{
    select,
    cursor,
    COUNT
};

template<int R, int C, class buttonName>
class puyoButtonCursor : public puyoObjectSignal<puyoButtonCursorSignal> // buttonName에 NONE이 원소로 있어야 함
{
    private : 
        std::array<std::array<std::pair<buttonName,bool>,C>,R> selected;
        POSi cursor;

        const std::vector<POSi> dir = {
            {-1,0},{1,0},{0,-1},{0,1}
        };
        void move_vertical(int amount)
        {
            selected[cursor.r][cursor.c].second = false;
            if(selected[cursor.r+amount][cursor.c].first != buttonName::NONE)
                cursor.r += amount;
            else
            {
                std::vector<std::vector<bool>> visited(R,std::vector<bool>(C,false));
                std::queue<POSi> coords;
                coords.push(cursor+POSi(0,amount));
                while(!coords.empty())
                {
                    const auto pos = coords.front();
                    coords.pop();
                    visited[pos.r][pos.c] = true;
                    if(selected[pos.r][pos.c].first != buttonName::NONE)
                    {
                        cursor = pos;
                        break;
                    }
                    for(const auto dpos : dir)
                    {
                        const auto npos = pos+dpos;
                        if(0 <= npos.r && npos.r < R && 0 <= npos.c && npos.c < C
                            && npos.c != cursor.c && selected[npos.r][npos.c].first != buttonName::NONE && !visited[npos.r][npos.c])
                            coords.push(npos);
                    }
                }
            }
            selected[cursor.r][cursor.c].second = true;
            set_signal(puyoButtonCursorSignal::cursor);
        }
        void move_horizontal(int amount)
        {
            selected[cursor.r][cursor.c].second = false;
            if(selected[cursor.r][cursor.c+amount].first != buttonName::NONE)
                cursor.c += amount;
            else
            {
                std::vector<std::vector<bool>> visited(R,std::vector<bool>(C,false));
                std::queue<POSi> coords;
                coords.push(cursor+POSi(amount,0));
                while(!coords.empty())
                {
                    const auto pos = coords.front();
                    coords.pop();
                    visited[pos.r][pos.c] = true;
                    if(selected[pos.r][pos.c].first != buttonName::NONE)
                    {
                        cursor = pos;
                        break;
                    }
                    for(const auto dpos : dir)
                    {
                        const auto npos = pos+dpos;
                        if(0 <= npos.r && npos.r < R && 0 <= npos.c && npos.c < C
                            && npos.r != cursor.r && selected[npos.r][npos.c].first != buttonName::NONE && !visited[npos.r][npos.c])
                            coords.push(npos);
                    }
                }
            }
            selected[cursor.r][cursor.c].second = true;
            set_signal(puyoButtonCursorSignal::cursor);

        }
    public :
        puyoButtonCursor(const std::vector<std::vector<buttonName>> allocated)
        {
            if(allocated.empty() || (int)allocated.size() != R || (int)allocated[0].size() != C)
                throw std::runtime_error("Button allocated vector is not matched with buttonCursor template variable");
            bool init_found = false;
            for(int i = 0 ; i < R ; ++i)
                for(int j = 0 ; j < C ; ++j)
                    if(!init_found && allocated[i][j] != buttonName::NONE)
                    {
                        selected[i][j] = std::make_pair(allocated[i][j],true);
                        cursor = {j,i};
                        init_found = true;
                    }
                    else
                        selected[i][j] = std::make_pair(allocated[i][j],false);   
            if(!init_found)   
                throw std::runtime_error("Button allocated vector has no button.(only has NONE)");
        }
        void let_select(){set_signal(puyoButtonCursorSignal::select);}
        void let_choose_left()
        {
            if(cursor.c > 0)
                move_horizontal(-1);
        }
        void let_choose_right()
        {
            if(cursor.c < C-1)
                move_horizontal(1);
        }
        void let_choose_up()
        {
            if(cursor.r > 0)
                move_vertical(-1);
        }
        void let_choose_down()
        {
            if(cursor.r < R-1)
                move_vertical(1);
        }
        const bool& get_select_status(buttonName type)
        {
            for(int i = 0 ; i < R ; ++i)
                for(int j = 0 ; j < C ; ++j)
                    if(selected[i][j].first == type)
                        return selected[i][j].second;
            throw std::runtime_error("factor of function get_select_status is not valid.");
            return selected[0][0].second;
        }
        buttonName get_selected_button(){return selected[cursor.r][cursor.c].first;}
};