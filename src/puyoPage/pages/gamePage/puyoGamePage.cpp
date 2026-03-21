#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoGamePage.hpp"

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScreen.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScreenhead.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScreenbar.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintVanishPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintGravityPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintFuturePuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintBoard.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintPlayPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintSpawnspot.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintNextPuyo.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintScore.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintObstructViewer.hpp"
#include "puyoResources/puyoPrinting/printObject/gamePage/puyoPrintEnergyPuyo.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintText.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/puyoLet.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoGamePage::puyoGamePage(puyoFileSystem& pfs, Arcade arcade, Diff diff, Mode mode) 
    : PUYO_SPRITE(pfs.get_sprite(puyoFileSystem::Image::puyo))
    , NUM_SPRITE(pfs.get_sprite(puyoFileSystem::Image::num))
    , BOARD_SPRITE(pfs.get_sprite(puyoFileSystem::Image::board))
    , COUNT_DOWN_BACK_SPRITE(pfs.get_sprite(puyoFileSystem::Image::black_back))
{

////////Arcade
    auto player0 = make_unique<puyoPlayer>(0, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1),false);
    pl.allot_key((int)(Keyboard::Key::A),player0->get_let_left());
    pl.allot_key((int)(Keyboard::Key::S),player0->get_let_down());
    pl.allot_key((int)(Keyboard::Key::D),player0->get_let_right());
    pl.allot_key((int)(Keyboard::Key::W),player0->get_let_turn());
    pl.allot_key((int)(Keyboard::Key::LShift),player0->get_let_drop());
    phase.add_player(std::move(player0));
    switch(arcade)
    {   
        case Arcade::solo :
            break;
        case Arcade::dual :
        {
            auto player1 = make_unique<puyoPlayer>(1, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1),false);
            pl.allot_key((int)(Keyboard::Key::Left),player1->get_let_left());
            pl.allot_key((int)(Keyboard::Key::Down),player1->get_let_down());
            pl.allot_key((int)(Keyboard::Key::Right),player1->get_let_right());
            pl.allot_key((int)(Keyboard::Key::Up),player1->get_let_turn());
            pl.allot_key((int)(Keyboard::Key::RShift),player1->get_let_drop());
            phase.add_player(std::move(player1));
            break;
        }
        case Arcade::bot :
        {
            auto bot = make_unique<puyoPlayer>(1, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1),true);
            phase.add_player(std::move(bot));
            break;
        }
        case Arcade::NONE :
            break;
    };
    phase.set_game(diff,mode);

//////출력 객체
    pp.add_print_object(make_unique<puyoPrintScreen>(phase.get_player_count(),BOARD_SPRITE,0,0,PRINT_IMMORTAL));
    for(auto&& player : phase.get_players())
    {
        const int player_num = player->get_player_num();
        const auto[spawn_x,spawn_y] = player->get_puyo_spawn_pos();
        const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
        const int board_printing_y = player_board_y + PUYO_SIZE*(BOARD_HEIGHT - player->get_board().get_board_size().first);

        pp.add_print_object(make_unique<puyoPrintSpawnspot>(player_num,PUYO_SPRITE,spawn_x,spawn_y,PRINT_IMMORTAL));
        pp.add_print_object(make_unique<puyoPrintFuturePuyo>(player->get_board().get_future_puyos(),PUYO_SPRITE,player_board_x,board_printing_y,PRINT_IMMORTAL));
        pp.add_print_object(make_unique<puyoPrintVanishPuyo>(player->get_board().get_vanish_puyos(),PUYO_SPRITE,player_board_x,board_printing_y,PRINT_IMMORTAL));
        pp.add_print_object(make_unique<puyoPrintGravityPuyo>(player->get_board().get_gravity_puyos(),PUYO_SPRITE,player_board_x,board_printing_y,PRINT_IMMORTAL));
        pp.add_print_object(make_unique<puyoPrintEnergyPuyo>(player->get_board().get_energy_puyos(),PUYO_SPRITE,0,0,PRINT_IMMORTAL));
        pp.add_print_object(make_unique<puyoPrintBoard>(player->get_board(),PUYO_SPRITE,player_board_x,board_printing_y,PRINT_IMMORTAL));
        pp.add_print_object(make_unique<puyoPrintPlayPuyo>(player->get_puyo(),PUYO_SPRITE,player_board_x,board_printing_y,PRINT_IMMORTAL));

        const auto [player_next_puyo_viewer_x,player_next_puyo_viewer_y] = PLAYER_NEXT_PUYO_VIEWER_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintNextPuyo>(player_num,player->get_new_puyo_count(),phase.get_new_colors(),PUYO_SPRITE,player_next_puyo_viewer_x,player_next_puyo_viewer_y,PRINT_IMMORTAL));

        const auto [player_score_x, player_score_y] = PLAYER_SCORE_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintScore>(player_num,player->get_score(),NUM_SPRITE,player_score_x,player_score_y,PRINT_IMMORTAL));
    }
    pp.add_print_object(make_unique<puyoPrintScreenhead>(BOARD_SPRITE,0,0,PRINT_IMMORTAL));
    pp.add_print_object(make_unique<puyoPrintScreenbar>(phase.get_player_count(),BOARD_SPRITE,SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y,PRINT_IMMORTAL));
    for(auto&& player : phase.get_players())
    {
        const int player_num = player->get_player_num();
        const auto [player_obstruct_viewer_x,player_obstruct_viewer_y] = PLAYER_OBSTRUCT_VIEWER_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintObstructViewer>(player->get_board().get_obstruct_puyo(),PUYO_SPRITE,player_obstruct_viewer_x,player_obstruct_viewer_y,PRINT_IMMORTAL));
    }

//////준비 전 단계
    pp.add_print_object(make_unique<puyoPrintObject>(COUNT_DOWN_BACK_SPRITE,0,0,8200)); //검은색 반투명 배경
    pp.add_print_text(make_unique<puyoPrintText>(SCREEN_X/2,SCREEN_Y/2,"Ready?",pfs.get_font(),60,Color::White,Text::Style::Bold,4000));
    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::ready));
    ready_status = Ready_status::ready;
}
puyoPageSignal puyoGamePage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    switch(ready_status)
    {
        case Ready_status::ready :
            if(pp.print_texts_empty())
            {
                pp.add_print_text(make_unique<puyoPrintText>(SCREEN_X/2,SCREEN_Y/2,"Start!",pfs.get_font(),60,Color::White,Text::Style::Bold,4200));
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::start));
                ps.play_music(pfs.get_random_music());
                ready_status = Ready_status::start;
            }
            break;
        case Ready_status::start :   
            if(pp.print_texts_empty())
                ready_status = Ready_status::play;
            break;
        case Ready_status::play :
            for(auto&& player : phase.get_players()) //신호 받기
            {
                const int player_num = player->get_player_num();
                auto& board = player->get_board();
                auto& puyo = player->get_puyo();
                if(board.get_signal(puyoBoardSignal::chain))
                {
                    const auto[chain_x,chain_y] = PLAYER_CHAIN_POS[player_num];
                    const int chain_count = board.get_chain_count();
                    pp.add_print_text(make_unique<puyoPrintText>(chain_x,chain_y,to_string(chain_count)+" chain",pfs.get_font(),29,Color::Red,Text::Style::Bold,1500));
                    
                    const int sound_number = min((int)puyoFileSystem::Sound::chain1+chain_count-1,(int)puyoFileSystem::Sound::chain7high);
                    ps.play_sound(pfs.get_buffer((puyoFileSystem::Sound)sound_number));
                }
                if(board.get_signal(puyoBoardSignal::all_cleared))
                {
                    const auto[all_clear_x,all_clear_y] = PLAYER_ALL_CLEAR_POS[player_num];
                    pp.add_print_text(make_unique<puyoPrintText>(all_clear_x,all_clear_y,"All Clear!",pfs.get_font(),31,Color::Red,Text::Style::Bold,4500));
                    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::all_clear));
                }
                if(board.get_signal(puyoBoardSignal::spawn_obsp))
                {
                    const int temp_obstruct_puyo = board.get_temp_obstruct_puyo_for_sounding();
                    if(temp_obstruct_puyo >= OBSTRUCT_PUYO_MANY)
                        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::many_obsp_dropped));
                    else if(temp_obstruct_puyo >= OBSTRUCT_PUYO_MID)
                        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::mid_obsp_dropped));
                    else
                        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::less_obsp_dropped));
                }
                if(board.get_signal(puyoBoardSignal::vanished))
                    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::puyo_vanished));
                if(puyo.get_signal(puyoPlayPuyoSignal::puyo_move))
                    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::puyo_move));
                if(player->get_signal(puyoPlayerSignal::puyo_dropped))
                    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::puyo_dropped));
            }
            phase.proceed_game();
            if(phase.game_ended())
            {
                signal.win_player_num = phase.get_win_player_num();
                signal.request_capture = true;
                signal.next_page = Page::ending;
            }
            break;
    };
    return signal;
}