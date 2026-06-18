#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseAsset/puyoForwardVector.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <utility>
#include <vector>

class puyoPrintNextPuyo : public puyoPrintObject
{
    private :
        int player_num;
        const int& new_puyo_count;
        const puyoForwardVector<PLAYPUYO>& new_puyos;
    public :
        puyoPrintNextPuyo(int player_num, const int& new_puyo_count, decltype(new_puyos)& new_puyos, sf::Sprite puyo, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};