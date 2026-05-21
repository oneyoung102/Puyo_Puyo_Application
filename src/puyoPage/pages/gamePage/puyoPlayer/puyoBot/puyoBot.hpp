#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <utility>
#include <random>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

class puyoPlayer;

class puyoBot
{
    protected :
        puyoBoard simulate_board;

        int act_time; // 한 행동을 하기까지 걸리는 시간
        const int init_act_tick;

        using PROBABLITY = std::pair<int,int>;

        bool get_fire(int puyo_count, int obstruct_puyo);
        std::vector<std::function<void()>> lets;
        std::vector<PROBABLITY> calc_all_probablities(const puyoBoard& board); //{좌우이동, 화전수}
        std::pair<POSi,POSi> to_coord(PROBABLITY probablity, const puyoPlayPuyo& puyo); //가능성을 좌표로 변환
        void to_let(PROBABLITY perfect_probablity, puyoPlayPuyo& puyo);///probablity를 명령으로 변환
        std::pair<POSi,POSi> simulate_drop(const std::vector<puyoPuyo>& puyos);
        std::mt19937 gen;
    public :
        puyoBot(POSi bsize, unsigned int init_act_tick = 0);     
        virtual ~puyoBot() = default; 
        virtual void think_perfect_lets(const puyoPlayer& player) = 0;
        bool bot_lets_empty();
        void let_bot_act();
};