#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintBoard : public puyoPrintObject
{
    private :
        const puyoBoard& board;
    public :
        puyoPrintBoard(const puyoBoard& board, sf::Sprite puyo, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};