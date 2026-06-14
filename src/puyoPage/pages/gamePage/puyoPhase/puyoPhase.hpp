
#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include "puyoPage/puyoObjectSignal/puyoObjectSignal.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseController.hpp"

enum class puyoModeSignal
{
    speed_up,//스피드 업 모드
    bomb_fused,//폭탄 모드
    bomb_explode,
    freeze,//프로즌 모드
    COUNT
};
 
class puyoPlayPuyo;
class puyoPuyo;
class puyoBoard;

class puyoPhase : public puyoObjectSignal<puyoModeSignal>
{
    private :
        std::vector<puyoPlayer> players;
        std::mt19937 gen;
        std::vector<puyoPuyo> new_type_list;
        std::vector<std::pair<puyoPuyo,puyoPuyo>> new_types;

        puyoScoreCalc calc;
        puyoPhaseController phase_controll;

        bool game_end, game_end_ask;
        int win_player_num;

        std::unique_ptr<puyoMode> curr_mode; 
        Mode mode_type;
        int gravity_value, stay_value;

        int proceed_play(puyoPlayer& player);
        int proceed_gravity(puyoPlayer& player);
        int proceed_vanish(puyoPlayer& player);
        void manage_obstruct(puyoPlayer& player, int added_score);
        void manage_game_end(puyoPlayer& player);
        void proceed_event(puyoPlayer& player); // puyoType에서 발생하는 이벤트 처리
        
        void end_game();
        bool game_end_asked() const;
    public :
        puyoPhase();

        void ask_end_game();
        bool game_ended() const;

        std::pair<puyoPuyo,puyoPuyo> get_new_puyos(int count);
        const std::vector<std::pair<puyoPuyo,puyoPuyo>>& get_new_types() const;
        std::vector<std::pair<puyoPuyo,puyoPuyo>>& get_new_types();

        void set_game(Diff diff, Mode mode);
        void proceed_game();

        int get_player_count() const;
        std::vector<puyoPlayer>& get_players();
        void add_player(puyoPlayer&& player);
        
        int get_gravity_value() const;
        void set_gravity_value(int value);
        int get_stay_value() const;
        void set_stay_value(int value);
        int get_color_count() const;
        void add_new_type(const puyoPuyo& type);
        void remove_new_type();

        Mode get_mode_type() const;

        int get_win_player_num() const;
        void set_win_player_num(int num);

        puyoPhaseController& controll_phase();
};