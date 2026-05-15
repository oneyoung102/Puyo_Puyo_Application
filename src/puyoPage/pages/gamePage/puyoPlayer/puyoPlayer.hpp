#pragma once

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/puyoObjectSignal.hpp"

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardScoreControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardObstructControll.hpp"

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
        puyoBoardEnergyControll energy_controll;
        puyoBoardGravityControll gravity_controll;
        puyoBoardScoreControll score_controll;
        puyoBoardObstructControll obstuct_controll;
        puyoBoardVanishControll vanish_controll;
        puyoBoardFutureControll future_controll;

        std::unique_ptr<puyoPlayPuyo> puyo;
        const int player_num; // 0 또는 1
        
        int score;
        int new_puyo_count;//새 뿌요를 받은 횟수

        const bool player_is_bot;
        std::unique_ptr<puyoBot> bot_model;

    public :
        puyoPlayer(int player_num, std::unique_ptr<puyoBoard>&& board, bool player_is_bot = false, int model = 1, unsigned int init_act_tick = 0, const std::vector<std::pair<puyoType,puyoType>>& new_types = {});

        int get_player_num() const;
        int get_opposite() const;
        puyoBoard& get_board() const;
        puyoPlayPuyo& get_puyo() const;

        const int& get_score() const;
        void add_score(int s);

        void give_new_puyos(std::pair<puyoType,puyoType> types, int puyo_gravity_value, int puyo_stay_value);
        const int& get_new_puyo_count() const;

        std::function<void()> get_let_left();
        std::function<void()> get_let_right();
        std::function<void()> get_let_down();
        std::function<void()> get_let_turn();
        std::function<void()> get_let_drop();

        void signal_puyo_drop();

        bool is_bot() const;
        void act_bot_let() const;

        puyoBoardEnergyControll& controll_energy();
        puyoBoardGravityControll& controll_gravity();
        puyoBoardScoreControll& controll_score();
        puyoBoardObstructControll& controll_obstuct();
        puyoBoardVanishControll& controll_vanish();
        puyoBoardFutureControll& controll_future();

        const puyoBoardEnergyControll& controll_energy() const;
        const puyoBoardGravityControll& controll_gravity() const;
        const puyoBoardScoreControll& controll_score() const;
        const puyoBoardObstructControll& controll_obstuct() const;
        const puyoBoardVanishControll& controll_vanish() const;
        const puyoBoardFutureControll& controll_future() const;
};