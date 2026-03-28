#pragma once

#include <vector>
#include <tuple>
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"

class puyoBoard;

class puyoBoardEnergyControll
{
    private :
        std::vector<std::tuple<int,int,puyoType>> temp_energy_puyos; 
        std::vector<puyoEnergyPuyo> energy_puyos; 
    public :
        puyoBoardEnergyControll();
        void fly_energy_puyos(puyoBoard& board);
        void find_energy_puyos(float fx, float fy, float tx, float ty);// temp_energy_puyo를 energy_puyo로

        void add_temp_energy_puyo(std::tuple<int,int,puyoType> temp_energy_puyo);
        void clear_temp_energy_puyos();

        std::vector<puyoEnergyPuyo>& get_energy_puyos();

        bool temp_energy_puyo_empty();
};