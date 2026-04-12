
#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardObstructControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardScoreControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include "puyoPage/puyoObjectSignal.hpp"

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
        enum class Phase{
            play,
            gravity,
            vanish
        };
        Phase get_phase(puyoBoard& board);

        std::vector<std::unique_ptr<puyoPlayer>> players;
        std::vector<int> delay_times;
        
        std::mt19937 gen;
        std::vector<std::pair<puyoType,puyoType>> new_types;

        puyoScoreCalc calc;

        bool game_end;
        int win_player_num;

        std::unique_ptr<puyoMode> curr_mode; 
        Mode mode_type;
        int gravity_value, stay_value, color_count;

        void delay(int player_num,int time);
        void wait(int player_num);
        bool delayed(int player_num);

        void ready_for_play(int player_num, puyoBoardObstructControll& co, puyoBoardScoreControll& cs);
        void proceed_play(const std::unique_ptr<puyoPlayer>& player, int& added_score);
        void proceed_gravity(const std::unique_ptr<puyoPlayer>& player, int& added_score);
        void proceed_vanish(const std::unique_ptr<puyoPlayer>& player, int& added_score);
        void calc_obstruct(const std::unique_ptr<puyoPlayer>& player, int& added_score);

    public :
        puyoPhase();

        void end_game();////

        std::pair<puyoType,puyoType> get_new_puyos(int count);
        const std::vector<std::pair<puyoType,puyoType>>& get_new_types();

        void set_game(Diff diff, Mode mode);
        void proceed_game();
        bool game_ended();

        int get_player_count();
        const std::vector<std::unique_ptr<puyoPlayer>>& get_players();
        void add_player(std::unique_ptr<puyoPlayer>&& player);
        
        int get_gravity_value();
        void set_gravity_value(int value);
        int get_stay_value();
        void set_stay_value(int value);
        int get_color_count();
        void set_color_count(int value);
        Mode get_mode_type();

        int get_win_player_num();
        void set_win_player_num(int num);
};