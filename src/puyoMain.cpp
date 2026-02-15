#include <SFML/Graphics.hpp>

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting.hpp"
#include "puyoPhase/puyoPlayer.hpp"
#include "puyoPhase/puyoBoard.hpp"
#include "puyoPhase/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoLet.hpp"
#include "puyoPhase/puyoPhasing.hpp"

#include "puyoResources/printObject/puyoPrintScreen.hpp"
#include "puyoResources/printObject/puyoPrintScreenhead.hpp"
#include "puyoResources/printObject/puyoPrintScreenbar.hpp"
#include "puyoResources/printObject/puyoPrintVanishPuyo.hpp"
#include "puyoResources/printObject/puyoPrintGravityPuyo.hpp"
#include "puyoResources/printObject/puyoPrintFuturePuyo.hpp"
#include "puyoResources/printObject/puyoPrintBoard.hpp"
#include "puyoResources/printObject/puyoPrintPlayPuyo.hpp"
#include "puyoResources/printObject/puyoPrintSpawnspot.hpp"
#include "puyoResources/printObject/puyoPrintNextPuyo.hpp"
#include "puyoResources/printObject/puyoPrintScore.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

int main()
{
    puyoFileSystem pfs;
    const Sprite PUYO_SPRITE = pfs.get_sprite(pfs.puyo);
    const Sprite NUM_SPRITE = pfs.get_sprite(pfs.num);
    const Sprite BOARD_SPRITE = pfs.get_sprite(pfs.board);

    RenderWindow window(VideoMode({SCREEN_X, SCREEN_Y}),"Puyo Puyo"); //창 설정
    puyoPrinting pp(window);
    puyoLet pl;

    puyoPhasing phase;
    auto player0 = make_unique<puyoPlayer>(0, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1));
    auto player1 = make_unique<puyoPlayer>(1, puyoBoard(), puyoPlayPuyo({0,0},{-1,-1},-1,-1));

    pl.allot_key((int)(Keyboard::Key::A),player0->get_let_left());
    pl.allot_key((int)(Keyboard::Key::S),player0->get_let_down());
    pl.allot_key((int)(Keyboard::Key::D),player0->get_let_right());
    pl.allot_key((int)(Keyboard::Key::W),player0->get_let_turn());
    pl.allot_key((int)(Keyboard::Key::LShift),player0->get_let_drop());

    pl.allot_key((int)(Keyboard::Key::Left),player1->get_let_left());
    pl.allot_key((int)(Keyboard::Key::Down),player1->get_let_down());
    pl.allot_key((int)(Keyboard::Key::Right),player1->get_let_right());
    pl.allot_key((int)(Keyboard::Key::Up),player1->get_let_turn());
    pl.allot_key((int)(Keyboard::Key::RShift),player1->get_let_drop());

    phase.add_player(std::move(player0));
    phase.add_player(std::move(player1));
    phase.set_game(2,-1.5, 4,1800,2000);

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

    while (window.isOpen())
    {
        window.clear();
        while (auto event = window.pollEvent())//이벤트 처리
        {
            if (event->is<Event::Closed>())//닫힘 이벤트
                window.close();
            pl.detect_keyboard(event);
        }
        pp.print_all_objects();
        phase.proceed_game();
        if(phase.game_ended())
            return -1;
        window.display();
    }
    return 0;
}