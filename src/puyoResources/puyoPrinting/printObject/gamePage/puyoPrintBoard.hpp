#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

class puyoPrintBoard : public puyoPrintObject
{
    private :
        const puyoBoard& board;
    public :
        puyoPrintBoard(const puyoBoard& board, sf::Sprite puyo, POS pos, int life);
        void print(sf::RenderWindow& w);
};