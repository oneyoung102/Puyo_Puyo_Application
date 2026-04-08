#pragma once

#include <vector>
#include <tuple>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"

class puyoBoard;

class puyoBoardEnergyControll
{
    private :
        std::vector<std::tuple<int,int,puyoType>> temp_energy_puyos; 
        std::vector<puyoPuyo> energy_puyos; 
    public :
        puyoBoardEnergyControll();
        void fly(puyoBoard& board);
        void find(float fx, float fy, float tx, float ty);// temp_energy_puyo를 energy_puyo로

        void temp_add(std::tuple<int,int,puyoType> temp_energy_puyo);
        void temp_clear();

        std::vector<puyoPuyo>& get();

        bool temp_empty();
};