#include <SFML/Graphics.hpp>

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting.hpp"
#include "puyoPhase/puyoPlayer.hpp"
#include "puyoPhase/puyoBoard.hpp"
#include "puyoPhase/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoLet.hpp"
#include "puyoPhase/puyoPhasing.hpp"

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

    puyoPhasing phase;
    phase.set_condition_for_vanish(4);

    //printf 함수로 개별 개별 처리하지 말고 print객체를 만들고 백터로 모아서 처리
    //이후 phasing 클래스에 게임 진행 반복문 추가, act관련 함수 분리... statement도 삭제
    puyoPlayer player0(0,puyoBoard(),puyoPlayPuyo({0,0},{-1,-1},-1)),
                player1(1,puyoBoard(),puyoPlayPuyo({0,0},{-1,-1},-1));

    player0.set_puyo_spawn_pos(2,-1.5);
    player1.set_puyo_spawn_pos(2,-1.5);

    player0.set_puyo_gravity_value(1800);
    player1.set_puyo_gravity_value(1800);

    player0.give_new_puyo(phase.get_new_puyo_color(player0.get_new_puyo_count()));
    player1.give_new_puyo(phase.get_new_puyo_color(player1.get_new_puyo_count()));

    pl.allot_key((int)(Keyboard::Key::A),player0.get_let_left());
    pl.allot_key((int)(Keyboard::Key::S),player0.get_let_down());
    pl.allot_key((int)(Keyboard::Key::D),player0.get_let_right());
    pl.allot_key((int)(Keyboard::Key::W),player0.get_let_turn());
    pl.allot_key((int)(Keyboard::Key::LShift),player0.get_let_drop());

    pl.allot_key((int)(Keyboard::Key::Left),player1.get_let_left());
    pl.allot_key((int)(Keyboard::Key::Down),player1.get_let_down());
    pl.allot_key((int)(Keyboard::Key::Right),player1.get_let_right());
    pl.allot_key((int)(Keyboard::Key::Up),player1.get_let_turn());
    pl.allot_key((int)(Keyboard::Key::RShift),player1.get_let_drop());

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
            const int player_num = player->get_player_num();

            const auto[spawn_x,spawn_y] = board.get_puyo_spawn_pos();
            pp.print_spawn_spot(PUYO_SPRITE,spawn_x,spawn_y,player_num);

            const auto statement = player->get_statement();
            if(statement == puyoPlayer::Statement::play)
            {
                pp.print_future_puyo(PUYO_SPRITE,player_num,puyo.get_future_puyo(board));
                pp.print_player_puyo(PUYO_SPRITE,puyo,player_num);

                phase.act_play_puyo(board,puyo);
                if(puyo.is_dropped())
                {
                    board.push_gravity_puyo(puyo.to_gravity_puyo());
                    player->give_new_puyo(phase.get_new_puyo_color(player->get_new_puyo_count()));
                    player->convert_statement(puyoPlayer::Statement::gravity);
                }
            }
            else if(statement == puyoPlayer::Statement::gravity)
            {
                pp.print_gravity_puyo(PUYO_SPRITE,board,player_num,board.get_gravity_puyos());

                phase.gravity_gravity_puyos(board);
                if(board.not_existed_gravity_puyo())
                {
                    phase.find_vanish_puyo(board); 
                    if(board.not_existed_vanish_puyo())
                        player->convert_statement(puyoPlayer::Statement::play);
                    else
                        player->convert_statement(puyoPlayer::Statement::vanish);
                }    
            }
            else if(statement == puyoPlayer::Statement::vanish)
            {
                pp.print_vanish_puyo(PUYO_SPRITE,board,player_num,board.get_vanish_puyos());

                phase.vanish_vanish_puyo(board);
                if(board.not_existed_vanish_puyo())
                {
                    phase.find_gravity_puyo(board);  
                    if(board.not_existed_gravity_puyo())
                        player->convert_statement(puyoPlayer::Statement::play);
                    else
                        player->convert_statement(puyoPlayer::Statement::gravity);
                } 
            }
            if(!phase.game_ended())
                pp.print_board(PUYO_SPRITE,board,player_num);
            else
                return -1;          
        }
        pp.print_screen_head(BOARD_SPRITE);
        window.display();
    }
    return 0;
}