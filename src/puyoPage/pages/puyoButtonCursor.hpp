#pragma once

#include <stdexcept>
#include <vector>
#include <queue>
#include <array>
#include <utility>
#include "puyoPage/puyoObjectSignal.hpp"

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
        int cursor_r, cursor_c;

        const std::vector<std::pair<int,int>> dir = {
            {-1,0},{1,0},{0,-1},{0,1}
        };
        void move_vertical(int amount)
        {
            selected[cursor_r][cursor_c].second = false;
            if(selected[cursor_r+amount][cursor_c].first != buttonName::NONE)
                cursor_r += amount;
            else
            {
                std::vector<std::vector<bool>> visited(R,std::vector<bool>(C,false));
                std::queue<std::pair<int,int>> coords;
                coords.push(std::make_pair(cursor_r+amount,cursor_c));
                while(!coords.empty())
                {
                    const auto [r,c] = coords.front();
                    coords.pop();
                    visited[r][c] = true;
                    if(selected[r][c].first != buttonName::NONE)
                    {
                        cursor_r = r;
                        cursor_c = c;
                        break;
                    }
                    for(const auto[dr,dc] : dir)
                    {
                        const int nr = r+dr, nc = c+dc;
                        if(0 <= nr && nr < R && 0 <= nc && nc < C
                            && nc != cursor_c && selected[nr][nc].first != buttonName::NONE && !visited[nr][nc])
                            coords.push(std::make_pair(nr,nc));
                    }
                }
            }
            selected[cursor_r][cursor_c].second = true;
            set_signal(puyoButtonCursorSignal::cursor);
        }
        void move_parallel(int amount)
        {
            selected[cursor_r][cursor_c].second = false;
            if(selected[cursor_r][cursor_c+amount].first != buttonName::NONE)
                cursor_c += amount;
            else
            {
                std::vector<std::vector<bool>> visited(R,std::vector<bool>(C,false));
                std::queue<std::pair<int,int>> coords;
                coords.push(std::make_pair(cursor_r,cursor_c+amount));
                while(!coords.empty())
                {
                    const auto [r,c] = coords.front();
                    coords.pop();
                    visited[r][c] = true;
                    if(selected[r][c].first != buttonName::NONE)
                    {
                        cursor_r = r;
                        cursor_c = c;
                        break;
                    }
                    for(const auto[dr,dc] : dir)
                    {
                        const int nr = r+dr, nc = c+dc;
                        if(0 <= nr && nr < R && 0 <= nc && nc < C
                            && nr != cursor_r && selected[nr][nc].first != buttonName::NONE && !visited[nr][nc])
                            coords.push(std::make_pair(nr,nc));
                    }
                }
            }
            selected[cursor_r][cursor_c].second = true;
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
                        cursor_r = i;
                        cursor_c = j;
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
            if(cursor_c > 0)
                move_parallel(-1);
        }
        void let_choose_right()
        {
            if(cursor_c < C-1)
                move_parallel(1);
        }
        void let_choose_up()
        {
            if(cursor_r > 0)
                move_vertical(-1);
        }
        void let_choose_down()
        {
            if(cursor_r < R-1)
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
        buttonName get_selected_button(){return selected[cursor_r][cursor_c].first;}
};