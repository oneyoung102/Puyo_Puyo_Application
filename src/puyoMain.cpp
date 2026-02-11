#include <SFML/Graphics.hpp>

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting.hpp"
#include "puyoPlayer.hpp"
#include "puyoBoard.hpp"
#include "puyoPuyo.hpp"
#include "puyoLet.hpp"

#include <functional>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

int main()
{
    puyoFileSystem pfs;
    RenderWindow window(VideoMode({SCREEN_X, SCREEN_Y}),"Puyo Puyo"); //창 설정

    puyoPrinting pp(window);
    puyoLet pl;

    puyoPlayer player0(0,puyoBoard(2,0)), player1(1,puyoBoard(2,0));

    pl.allot_key((int)(Keyboard::Key::A),player0.get_puyo().get_let_left());
    pl.allot_key((int)(Keyboard::Key::S),player0.get_puyo().get_let_down());
    pl.allot_key((int)(Keyboard::Key::D),player0.get_puyo().get_let_right());
    pl.allot_key((int)(Keyboard::Key::W),player0.get_puyo().get_let_turn());
    pl.allot_key((int)(Keyboard::Key::Space),player0.get_puyo().get_let_drop());

    
    for(int i = 0 ; i < 6 ; ++i)
    {
        player0.get_board().insert_puyo(i%5,11,i);
        player1.get_board().insert_puyo(i%5,11,i);
    }

    const auto[x,y] = player0.get_board().get_puyo_appear_pos();
    player0.give_puyo(puyoPuyo(x,y,2,4));
    
    
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())//이벤트 처리
        {
            if (event->is<Event::Closed>())//닫힘 이벤트
                window.close();
            pl.detect_keyboard(event);
        }

        window.clear();
        pp.printScreen(pfs.get_sprite(pfs.board),2);

        player0.get_puyo().act_fall(player0.get_board());
        player0.get_puyo().act_let(player0.get_board());

        pp.printPlayerPuyo(pfs.get_sprite(pfs.puyo),player0);

        pp.printBoard(pfs.get_sprite(pfs.puyo),player0);
        pp.printBoard(pfs.get_sprite(pfs.puyo),player1);

        window.display();
    }
    return 0;
}