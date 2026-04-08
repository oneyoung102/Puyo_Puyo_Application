#pragma once

#include <functional>
#include <vector>
#include <utility>
#include <tuple>
#include <random>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

class puyoBotAlgorithm
{
    private :
        std::vector<std::function<void()>> lets;
        std::vector<std::pair<int,int>> calc_all_probablities(puyoBoard& board); //{좌우이동, 화전수}
        std::tuple<int,int,int,int> to_coord(std::pair<int,int> probablity, puyoPlayPuyo& puyo); //가능성을 좌표로 변환
        void to_let(std::pair<int,int> perfect_probablity, puyoPlayPuyo& puyo);///probablity를 명령으로 변환
        bool simulate_drop(std::vector<std::vector<puyoType>>& simulate_board, int x1, int& y1, int x2, int& y2, puyoType type1, puyoType type2);
        int get_possiblity(int puyo_count, int sum, int obstruct_puyo);
        std::mt19937 gen;
    public :
        puyoBotAlgorithm();      
        void think_perfect_lets(puyoBoard& board, puyoPlayPuyo& puyo);
        bool bot_lets_empty();
        void let_bot_act();
};