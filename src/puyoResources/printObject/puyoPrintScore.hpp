#pragma once

#include "puyoPrintObject.hpp"

class puyoPrintScore : public puyoPrintObject
{
    private :
        int player_num;
        int& score;
        void print_num(RenderWindow& w, int img_x,int px, int py);
    public :
        puyoPrintScore(int pn, int& s, Sprite num, int x, int y, int life);
        void print_object(RenderWindow& w);
};