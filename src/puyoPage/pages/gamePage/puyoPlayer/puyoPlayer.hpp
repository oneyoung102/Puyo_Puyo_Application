#pragma once

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/puyoObjectSignal.hpp"
#include "puyoBotAlgorithm.hpp"

#include <utility>
#include <functional>
#include <memory>

enum class puyoPlayerSignal
{
    puyo_dropped,
    COUNT
};

class puyoPlayer : public puyoObjectSignal<puyoPlayerSignal>
{
    private :
        std::unique_ptr<puyoBoard> board;
        std::unique_ptr<puyoPlayPuyo> puyo;
        const int player_num; // 0 또는 1
        
        int score;
        int new_puyo_count;//새 뿌요를 받은 횟수

        const bool player_is_bot;
        std::unique_ptr<puyoBotAlgorithm> bot_algorithm;

    public :
        puyoPlayer(int player_num, std::unique_ptr<puyoBoard>&& board ,bool player_is_bot);

        int get_player_num();
        puyoBoard& get_board();
        puyoPlayPuyo& get_puyo();

        const int& get_score();
        void add_score(int s);

        void give_new_puyos(std::pair<puyoType,puyoType> types, int puyo_gravity_value, int puyo_stay_value);
        const int& get_new_puyo_count();

        std::function<void()> get_let_left();
        std::function<void()> get_let_right();
        std::function<void()> get_let_down();
        std::function<void()> get_let_turn();
        std::function<void()> get_let_drop();

        void sign_puyo_dropped();

        bool is_bot();
        void act_bot_let();
};