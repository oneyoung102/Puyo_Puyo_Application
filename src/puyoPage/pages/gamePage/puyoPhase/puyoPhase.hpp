
#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include "puyoPage/puyoObjectSignal.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseStatement.hpp"

enum class puyoModeSignal
{
    speed_up,//스피드 업 모드
    bomb_fused,//폭탄 모드
    bomb_explode,
    COUNT
};
 
class puyoPlayPuyo;
class puyoPuyo;
class puyoBoard;

class puyoPhase : public puyoObjectSignal<puyoModeSignal>
{
    private :
        std::vector<std::unique_ptr<puyoPlayer>> players;
        std::mt19937 gen;
        std::vector<std::pair<puyoType,puyoType>> new_types;

        puyoScoreCalc calc;
        puyoPhaseStatement pstate;

        bool game_end;
        int win_player_num;

        std::unique_ptr<puyoMode> curr_mode; 
        Mode mode_type;
        int gravity_value, stay_value, color_count;

        void proceed_play(const std::unique_ptr<puyoPlayer>& player, int& added_score);
        void proceed_gravity(const std::unique_ptr<puyoPlayer>& player, int& added_score);
        void proceed_vanish(const std::unique_ptr<puyoPlayer>& player, int& added_score);
        void calc_obstruct(const std::unique_ptr<puyoPlayer>& player, int& added_score);

    public :
        puyoPhase();

        void end_game();////

        std::pair<puyoType,puyoType> get_new_puyos(int count);
        const std::vector<std::pair<puyoType,puyoType>>& get_new_types() const;

        void set_game(Diff diff, Mode mode);
        void proceed_game();
        bool game_ended() const;

        int get_player_count() const;
        const std::vector<std::unique_ptr<puyoPlayer>>& get_players() const;
        void add_player(std::unique_ptr<puyoPlayer>&& player);
        
        int get_gravity_value() const;
        void set_gravity_value(int value);
        int get_stay_value() const;
        void set_stay_value(int value);
        int get_color_count() const;
        void set_color_count(int value);
        Mode get_mode_type() const;

        int get_win_player_num() const;
        void set_win_player_num(int num);
};