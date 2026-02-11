#include <SFML/Graphics.hpp>

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting.hpp"
#include "puyoPlayer.hpp"
#include "puyoBoard.hpp"
#include "puyoPlayPuyo.hpp"
#include "puyoLet.hpp"
#include "puyoPhase/puyoPhasing.hpp"

#include <functional>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

int main()
{
    puyoFileSystem pfs;
    const Sprite PUYO_SPRITE = pfs.get_sprite(pfs.puyo);
    const Sprite BOARD_SPRITE = pfs.get_sprite(pfs.board);

    RenderWindow window(VideoMode({SCREEN_X, SCREEN_Y}),"Puyo Puyo"); //창 설정
    puyoPrinting pp(window);
    puyoLet pl;

    puyoPlayer player0(0,puyoBoard(2,-1),puyoPhasing()), player1(1,puyoBoard(2,-1),puyoPhasing());

    pl.allot_key((int)(Keyboard::Key::A),player0.get_puyo().get_let_left());
    pl.allot_key((int)(Keyboard::Key::S),player0.get_puyo().get_let_down());
    pl.allot_key((int)(Keyboard::Key::D),player0.get_puyo().get_let_right());
    pl.allot_key((int)(Keyboard::Key::W),player0.get_puyo().get_let_turn());
    pl.allot_key((int)(Keyboard::Key::LShift),player0.get_puyo().get_let_drop());

    pl.allot_key((int)(Keyboard::Key::Left),player1.get_puyo().get_let_left());
    pl.allot_key((int)(Keyboard::Key::Down),player1.get_puyo().get_let_down());
    pl.allot_key((int)(Keyboard::Key::Right),player1.get_puyo().get_let_right());
    pl.allot_key((int)(Keyboard::Key::Up),player1.get_puyo().get_let_turn());
    pl.allot_key((int)(Keyboard::Key::RShift),player1.get_puyo().get_let_drop());


    player0.give_puyo(puyoPlayPuyo(player0.get_board().get_puyo_appear_pos(),
                                    player0.get_phase().get_new_puyo_color()));
    player1.give_puyo(puyoPlayPuyo(player1.get_board().get_puyo_appear_pos(),
                                    player1.get_phase().get_new_puyo_color()));

    vector<puyoPlayer*> players;
    players.push_back(&player0);
    players.push_back(&player1);
    
    
    while (window.isOpen())
    {
        window.clear();
        while (auto event = window.pollEvent())//이벤트 처리
        {
            if (event->is<Event::Closed>())//닫힘 이벤트
                window.close();
            pl.detect_keyboard(event);
        }
        pp.print_screen(BOARD_SPRITE,(int)players.size());

        for(auto player : players)
        {
            auto& board = player->get_board();
            auto& puyo = player->get_puyo();
            auto& phase = player->get_phase();
            const int player_num = player->get_player_num();

            if(phase.not_existed_temp_puyo())
            {
                if(!puyo.act_let(board) || !puyo.act_fall(board))
                {
                    phase.push_temp_puyo(puyo.to_temp_puyo());
                    player->give_puyo(puyoPlayPuyo(board.get_puyo_appear_pos(),phase.get_new_puyo_color()));
                }
                pp.print_future_puyo(PUYO_SPRITE,player_num,puyo.get_future_puyo(board));
            }
            if(!phase.gravity_temp_puyos(board))
                return -1;
        
            pp.print_temp_puyo(PUYO_SPRITE,board,player_num,phase.get_temp_puyos());
            pp.print_player_puyo(PUYO_SPRITE,puyo,player_num);
            pp.print_board(PUYO_SPRITE,board,player_num);
        }
        window.display();
    }
    return 0;
}