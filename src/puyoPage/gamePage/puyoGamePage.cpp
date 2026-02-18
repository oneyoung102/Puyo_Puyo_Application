#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "puyoGamePage.hpp"

#include "puyoPlayer.hpp"
#include "puyoBoard.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPhasing.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintScreen.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintScreenhead.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintScreenbar.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintVanishPuyo.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintGravityPuyo.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintFuturePuyo.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintBoard.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintPlayPuyo.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintSpawnspot.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintNextPuyo.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintScore.hpp"
#include "../../puyoResources/printObject/gamePage/puyoPrintObstructViewer.hpp"
#include "../../puyoResources/printText/puyoPrintText.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../puyoLet.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoGamePage::puyoGamePage(puyoFileSystem& pfs, int player_count) 
    : PUYO_SPRITE(pfs.get_sprite(pfs.puyo))
    , NUM_SPRITE(pfs.get_sprite(pfs.num))
    , BOARD_SPRITE(pfs.get_sprite(pfs.board))
    , COUNT_DOWN_BACK_SPRITE(pfs.get_sprite(pfs.black_back))
{
    auto player0 = make_unique<puyoPlayer>(0, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1));
    pl.allot_key((int)(Keyboard::Key::A),player0->get_let_left());
    pl.allot_key((int)(Keyboard::Key::S),player0->get_let_down());
    pl.allot_key((int)(Keyboard::Key::D),player0->get_let_right());
    pl.allot_key((int)(Keyboard::Key::W),player0->get_let_turn());
    pl.allot_key((int)(Keyboard::Key::LShift),player0->get_let_drop());
    phase.add_player(std::move(player0));

    if(player_count == 2)
    {
        auto player1 = make_unique<puyoPlayer>(1, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1));
        pl.allot_key((int)(Keyboard::Key::Left),player1->get_let_left());
        pl.allot_key((int)(Keyboard::Key::Down),player1->get_let_down());
        pl.allot_key((int)(Keyboard::Key::Right),player1->get_let_right());
        pl.allot_key((int)(Keyboard::Key::Up),player1->get_let_turn());
        pl.allot_key((int)(Keyboard::Key::RShift),player1->get_let_drop());
        phase.add_player(std::move(player1));
    }
    phase.set_game(2,-1.5, 4,1800,2000,4);

    pp.add_print_object(make_unique<puyoPrintScreen>(phase.get_player_count(),BOARD_SPRITE,0,0,-1));
    for(auto&& player : phase.get_players())
    {
        const int player_num = player->get_player_num();
        const auto[spawn_x,spawn_y] = player->get_puyo_spawn_pos();
        pp.add_print_object(make_unique<puyoPrintSpawnspot>(player_num,PUYO_SPRITE,spawn_x,spawn_y,-1));
        const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintFuturePuyo>(player->get_board().get_future_puyos(),PUYO_SPRITE,player_board_x,player_board_y,-1));
        pp.add_print_object(make_unique<puyoPrintVanishPuyo>(player->get_board().get_vanish_puyos(),PUYO_SPRITE,player_board_x,player_board_y,-1));
        pp.add_print_object(make_unique<puyoPrintGravityPuyo>(player->get_board().get_gravity_puyos(),PUYO_SPRITE,player_board_x,player_board_y,-1));
        pp.add_print_object(make_unique<puyoPrintBoard>(player->get_board(),PUYO_SPRITE,player_board_x,player_board_y,-1));
        pp.add_print_object(make_unique<puyoPrintPlayPuyo>(player->get_puyo(),PUYO_SPRITE,player_board_x,player_board_y,-1));

        const auto [player_next_puyo_viewer_x,player_next_puyo_viewer_y] = PLAYER_NEXT_PUYO_VIEWER_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintNextPuyo>(player_num,player->get_new_puyo_count(),phase.get_new_colors(),PUYO_SPRITE,player_next_puyo_viewer_x,player_next_puyo_viewer_y,-1));

        const auto [player_score_x, player_score_y] = PLAYER_SCORE_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintScore>(player_num,player->get_score(),NUM_SPRITE,player_score_x,player_score_y,-1));
    }
    pp.add_print_object(make_unique<puyoPrintScreenhead>(BOARD_SPRITE,0,0,-1));
    pp.add_print_object(make_unique<puyoPrintScreenbar>(phase.get_player_count(),BOARD_SPRITE,SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y,-1));
    for(auto&& player : phase.get_players())
    {
        const int player_num = player->get_player_num();
        const auto [player_obstruct_viewer_x,player_obstruct_viewer_y] = PLAYER_OBSTRUCT_VIEWER_POS[player_num];
        pp.add_print_object(make_unique<puyoPrintObstructViewer>(player->get_board().get_obstruct_puyo(),PUYO_SPRITE,player_obstruct_viewer_x,player_obstruct_viewer_y,-1));
    }

    count_down = 3;
    count_down_time = 2800;
    pp.add_print_object(make_unique<puyoPrintObject>(COUNT_DOWN_BACK_SPRITE,0,0,count_down_time*(count_down+1))); //검은색 반투명 배경
}
Page puyoGamePage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    if(count_down != -1)
    {
        if(pp.not_existed_print_text())
        {
            if(count_down == 0)
                pp.add_print_text(make_unique<puyoPrintText>(SCREEN_X/2,SCREEN_Y/2,"START!",pfs.get_font(),60,Color::White,Text::Style::Bold,count_down_time));
            else
                pp.add_print_text(make_unique<puyoPrintText>(SCREEN_X/2,SCREEN_Y/2,to_string(count_down),pfs.get_font(),60,Color::White,Text::Style::Bold,count_down_time));
            --count_down;
        }
        return Page::none;
    }
    phase.proceed_game();
    for(auto&& player : phase.get_players())
    {
        const int player_num = player->get_player_num();
        auto& board = player->get_board();
        if(board.chain_signal_for_printing())
        {
            const auto[chain_x,chain_y] = PLAYER_CHAIN_POS[player_num];
            pp.add_print_text(make_unique<puyoPrintText>(chain_x,chain_y,to_string(board.get_chain_count())+" combo",pfs.get_font(),29,Color::Red,Text::Style::Bold,1800));
        }
        if(board.all_cleared_signal_for_printing())
        {
            const auto[all_clear_x,all_clear_y] = PLAYER_ALL_CLEAR_POS[player_num];
            pp.add_print_text(make_unique<puyoPrintText>(all_clear_x,all_clear_y,"All Clear!",pfs.get_font(),31,Color::Red,Text::Style::Bold,4500));
        }
    }
    if(phase.game_ended())
        return Page::ending;
    return Page::none;
}