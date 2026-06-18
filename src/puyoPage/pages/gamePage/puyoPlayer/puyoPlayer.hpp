#pragma once

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseAsset/puyoForwardVector.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/puyoObjectSignal/puyoObjectSignal.hpp"

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"

#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoScoreControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoObstructControll.hpp"

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
        puyoEnergyControll energy_controll;
        puyoGravityControll gravity_controll;
        puyoScoreControll score_controll;
        puyoObstructControll obstuct_controll;
        puyoVanishControll vanish_controll;
        puyoFutureControll future_controll;

        std::unique_ptr<puyoPlayPuyo> puyo;
        const int player_num; // 0 또는 1
        
        int score;
        int new_puyo_count;//새 뿌요를 받은 횟수

        const bool player_is_bot;
        std::unique_ptr<puyoBot> bot_model;

    public :
        puyoPlayer(int player_num, std::unique_ptr<puyoBoard>&& board, bool player_is_bot = false, int model = 1, unsigned int init_act_tick = 0, const puyoForwardVector<PLAYPUYO>& new_types = {});

        int get_player_num() const;
        int get_opposite() const;
        puyoBoard& get_board() const;
        puyoPlayPuyo& get_puyo() const;

        const int& get_score() const;
        void add_score(int s);

        void give_new_puyos(PLAYPUYO&& puyos, int puyo_gravity_value, int puyo_stay_value);
        const int& get_new_puyo_count() const;

        std::function<void()> get_let_left() const;
        std::function<void()> get_let_right() const;
        std::function<void()> get_let_down() const;
        std::function<void()> get_let_turn() const;
        std::function<void()> get_let_drop() const;

        bool is_bot() const;
        void act_bot_let() const;

        puyoEnergyControll& controll_energy();
        puyoGravityControll& controll_gravity();
        puyoScoreControll& controll_score();
        puyoObstructControll& controll_obstuct();
        puyoVanishControll& controll_vanish();
        puyoFutureControll& controll_future();
        const puyoEnergyControll& controll_energy() const;
        const puyoGravityControll& controll_gravity() const;
        const puyoScoreControll& controll_score() const;
        const puyoObstructControll& controll_obstuct() const;
        const puyoVanishControll& controll_vanish() const;
        const puyoFutureControll& controll_future() const;
};