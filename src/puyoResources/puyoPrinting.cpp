#include <SFML/Graphics.hpp>

#include "../puyoPhase/puyoBoard.hpp"
#include "../puyoPhase/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPrinting.hpp"
#include "../puyoPhase/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "../puyoPhase/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "../puyoPhase/puyoTempPuyo/puyoFuturePuyo.hpp"

#include <tuple>
#include <vector>

using namespace std;
using namespace sf;


using namespace puyoImageConstant;


void puyoPrinting::print_sprite(Sprite sprite, float x, float y)
{
    sprite.setPosition({x, y});
    window.draw(sprite);
}
puyoPrinting::puyoPrinting(RenderWindow& w) : window(w)
{
    spwan_spot_state = 0;
    spawn_spot_rotate_dir = 0;//왼쪽
};

void puyoPrinting::print_spawn_spot(Sprite puyo, float x, float y, int player_num)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    const int img_x = PUYO_SIZE*(SPWAN_SPOT_STATE_X+spwan_spot_state/SPWAN_SPOT_CYCLE), img_y = PUYO_SIZE*SPWAN_SPOT_STATE_Y;
    puyo.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 

    if(spwan_spot_state == SPWAN_SPOT_STATE_MAX*SPWAN_SPOT_CYCLE-1 || spwan_spot_state == -1)
        spawn_spot_rotate_dir ^= 1;
    if(spawn_spot_rotate_dir)
    {
        ++spwan_spot_state;
        const int x1 = player_board_x + PUYO_SIZE*x, y1 = player_board_y + PUYO_SIZE*max(y,0.0f);
        print_sprite(puyo,x1,y1);
    }
    else
    {
        --spwan_spot_state;
        puyo.setScale({-1, 1});
        const int x1 = player_board_x + PUYO_SIZE*(x+1), y1 = player_board_y + PUYO_SIZE*max(y,0.0f);
        print_sprite(puyo,x1,y1);
    }
}

void puyoPrinting::print_puyo(Sprite puyo, float x, float y, int img_x, int img_y)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    puyo.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(puyo,x,y);
}

void puyoPrinting::print_board(Sprite puyo, puyoBoard& board, int player_num)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    const auto [board_r,board_c] = board.get_board_size();
    
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            if(board.get_puyo(i,j) == -1)
                continue;
            const int x = player_board_x + PUYO_SIZE*j, y = player_board_y + PUYO_SIZE*i;
            const int curr_puyo = board.get_puyo(i,j);
            const int dir = 1*(board.is_in_board(i+1,j) && board.get_puyo(i+1,j) == curr_puyo)+
                            2*(board.is_in_board(i-1,j) && board.get_puyo(i-1,j) == curr_puyo)+
                            4*(board.is_in_board(i,j+1) && board.get_puyo(i,j+1) == curr_puyo)+
                            8*(board.is_in_board(i,j-1) && board.get_puyo(i,j-1) == curr_puyo);
            print_puyo(puyo,x,y,dir,board.get_puyo(i,j));//0대신 주변 뿌요 감지해서 방향 설정
        }
}

void puyoPrinting::print_player_puyo(Sprite puyo, puyoPlayPuyo& playPuyo, int player_num)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];

    const auto [x1,y1,x2,y2] = playPuyo.get_puyo_pos();
    const auto [color1,color2] = playPuyo.get_puyo_color();

    const int x3 = player_board_x + PUYO_SIZE*x1, y3 = player_board_y + PUYO_SIZE*y1;
    print_puyo(puyo,x3,y3,0,color1);
    const int x4 = player_board_x + PUYO_SIZE*x2, y4 = player_board_y + PUYO_SIZE*y2;
    print_puyo(puyo,x4,y4,0,color2);
}

void puyoPrinting::print_future_puyo(Sprite puyo, int player_num, vector<puyoFuturePuyo>&& future_puyos)
{
    puyo.setColor(Color(255, 255, 255, 128*FUTURE_PUYO_ALPHA_VALUE));//투명도 조절

    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    for(auto&& future_puyo : future_puyos)
    {
        const auto [x,y] = future_puyo.get_puyo_pos();
        const int color = future_puyo.get_puyo_color();
        const int x1 = player_board_x + PUYO_SIZE*x, y1 = player_board_y + PUYO_SIZE*y;
        print_puyo(puyo,x1,y1,0,color);
    }
}


void puyoPrinting::print_gravity_puyo(Sprite puyo, puyoBoard& board, int player_num, vector<puyoGravityPuyo>& gravity_puyos)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    for(auto& gravity_puyo : gravity_puyos)
    {
        const auto [x,y] = gravity_puyo.get_puyo_pos();
        const int color = gravity_puyo.get_puyo_color();
        const int x1 = player_board_x + PUYO_SIZE*x, y1 = player_board_y + PUYO_SIZE*y;
        print_puyo(puyo,x1,y1,GRAVITY_PUYO_X+color,GRAVITY_PUYO_Y);
        print_puyo(puyo,x1,y1,GRAVITY_PUYO_X+color,GRAVITY_PUYO_Y+1);
    }
}
void puyoPrinting::print_vanish_puyo(Sprite puyo, puyoBoard& board, int player_num, vector<puyoVanishPuyo>& vanish_puyos)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    for(auto& vanish_puyo : vanish_puyos)
    {
        const auto [x,y] = vanish_puyo.get_puyo_pos();
        const int color = vanish_puyo.get_puyo_color();
        const int x1 = player_board_x + PUYO_SIZE*x, y1 = player_board_y + PUYO_SIZE*y;
        if(vanish_puyo.vanish_soon())
            print_puyo(puyo,x1,y1,VANISH_PUYO_X+2*color,VANISH_PUYO_Y);
        else
            print_puyo(puyo,x1,y1,VANISH_PUYO_X+2*color+1,VANISH_PUYO_Y);
    }
}

void puyoPrinting::print_screen(Sprite screen, int player_count)
{
    if(player_count != 1 && player_count != 2)
        throw runtime_error("Player count is over limit");
    screen.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count), 0}, {static_cast<int>(SCREEN_X),static_cast<int>(SCREEN_Y)})); 
    print_sprite(screen,0,0);
}
void puyoPrinting::print_screen_head(Sprite screen) //위에서 내려오는 뿌요를 가리기 위한 head
{
    const auto [ignore,player_board_y] = PLAYER_BOARD_POS[0];
    screen.setTextureRect(IntRect({0,0}, {static_cast<int>(SCREEN_X),player_board_y+1})); 
    print_sprite(screen,0,0);
    
}
