#pragma once

#include <vector>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
class puyoBoard;

class puyoEnergyControll
{
    private :
        std::vector<puyoPuyo> temp_energy_puyos; 
        std::vector<puyoPuyo> energy_puyos; 
    public :
        puyoEnergyControll();
        void fly(const puyoBoard& board);
        void spawn(int from_player_num, int to_player_num);// temp_energy_puyo를 energy_puyo로
        const std::vector<puyoPuyo>& get() const;

        void add(puyoPuyo&& temp_energy_puyo);
        void add(std::vector<puyoPuyo>&& temp_energy_puyos);
        void clear();
        bool empty() const;
};