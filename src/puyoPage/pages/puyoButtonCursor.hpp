#pragma once

#include <array>
#include "puyoPage/puyoObjectSignal.hpp"

enum class puyoButtonCursorSignal
{
    select,
    cursor,
    COUNT
};

template<int R, int C, class buttonName>
class puyoButtonCursor : public puyoObjectSignal<puyoButtonCursorSignal>
{
    private : 
        std::array<std::array<bool,C>,R> selected;
        int cursor_r, cursor_c;

        void cursor_move(int& cursor, int amount)
        {
            selected[cursor_r][cursor_c] = false;
            cursor += amount;
            selected[cursor_r][cursor_c] = true;
            signals[(int)puyoButtonCursorSignal::cursor] = true;
        }
    public :
        puyoButtonCursor()
        {
            selected = {{false,},};
            selected[0][0] = true;
            cursor_r = 0;
            cursor_c = 0;
        }
        void let_select(){signals[(int)puyoButtonCursorSignal::select] = true;}
        void let_choose_left()
        {
            if(cursor_c > 0)
                cursor_move(cursor_c,-1);
        }
        void let_choose_right()
        {
            if(cursor_c < C-1)
                cursor_move(cursor_c,1);
        }
        void let_choose_up()
        {
            if(cursor_r > 0)
                cursor_move(cursor_r,-1);
        }
        void let_choose_down()
        {
            if(cursor_r < R-1)
                cursor_move(cursor_r,1);
        }
        const bool& get_select_status(buttonName type){return selected[(int)type/C][(int)type%C];}
        buttonName get_selected_button(){return static_cast<buttonName>(cursor_r*C+cursor_c);}
};