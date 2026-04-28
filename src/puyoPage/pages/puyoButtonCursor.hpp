#pragma once

#include <stdexcept>
#include <vector>
#include <queue>
#include <array>
#include <utility>
#include "puyoPage/puyoObjectSignal.hpp"
#include "puyoTool/puyoPos.hpp"
#include "puyoTool/puyoDir.hpp"

enum class puyoButtonCursorSignal
{
    select,
    cursor,
    COUNT
};

template<size_t R, size_t C, class buttonName>
class puyoButtonCursor : public puyoObjectSignal<puyoButtonCursorSignal> // buttonName에 NONE이 원소로 있어야 함
{
    private : 
        std::array<std::array<std::pair<buttonName,bool>,C>,R> selected;
        POSi cursor;


        void move_cursor(POSi amount)
        {
            selected[cursor.r][cursor.c].second = false;
            if(selected[cursor.r+amount.r][cursor.c+amount.c].first != buttonName::NONE)
                cursor += amount;
            else
            {
                std::vector<std::vector<bool>> visited(R,std::vector<bool>(C,false));
                std::queue<POSi> coords;
                auto temp_cursor = cursor;
                while(POSi() <= temp_cursor && temp_cursor < POSi(C,R))
                {
                    coords.push(temp_cursor);
                    temp_cursor += amount;
                }
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
                    for(const auto dpos : DIR)
                    {
                        const auto npos = pos+dpos;
                        if(POSi() <= npos && npos < POSi(C,R) && selected[npos.r][npos.c].first != buttonName::NONE && !visited[npos.r][npos.c])
                            coords.push(npos);
                    }
                }
            }
            selected[cursor.r][cursor.c].second = true;
            set_signal(puyoButtonCursorSignal::cursor);
        }
    public :
        puyoButtonCursor(const std::vector<std::vector<buttonName>>& allocated)
        {
            if(allocated.empty() || allocated.size() != R || allocated[0].size() != C)
                throw std::runtime_error("Button allocated vector is not matched with buttonCursor template variable");
            bool init_found = false;
            for(size_t i = 0 ; i < R ; ++i)
                for(size_t j = 0 ; j < C ; ++j)
                    if(!init_found && allocated[i][j] != buttonName::NONE)
                    {
                        selected[i][j] = std::make_pair(allocated[i][j],true);
                        cursor = POSi(j,i);
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
                move_cursor(DIR[LEFT]);
        }
        void let_choose_right()
        {
            if(cursor.c < C-1)
                move_cursor(DIR[RIGHT]);
        }
        void let_choose_up()
        {
            if(cursor.r > 0)
                move_cursor(DIR[UP]);
        }
        void let_choose_down()
        {
            if(cursor.r < R-1)
                move_cursor(DIR[DOWN]);
        }
        const bool& get_select_status(buttonName type) const
        {
            for(size_t i = 0 ; i < R ; ++i)
                for(size_t j = 0 ; j < C ; ++j)
                    if(selected[i][j].first == type)
                        return selected[i][j].second;
            throw std::runtime_error("factor of function get_select_status is not valid.");
        }
        buttonName get_selected_button(){return selected[cursor.r][cursor.c].first;}
};