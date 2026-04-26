#pragma once

#include <vector>
#include <tuple>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"

class puyoBoard;

class puyoBoardEnergyControll
{
    private :
        std::vector<PUYO_INFO> temp_energy_puyos; 
        std::vector<puyoPuyo> energy_puyos; 
    public :
        puyoBoardEnergyControll();
        void fly(puyoBoard& board);
        void to_energy_puyo(int from_player_num, int to_player_num);// temp_energy_puyo를 energy_puyo로
        const std::vector<puyoPuyo>& get();

        void add_temp(PUYO_INFO temp_energy_puyo);
        void clear_temp();
        bool empty_temp() const;
};