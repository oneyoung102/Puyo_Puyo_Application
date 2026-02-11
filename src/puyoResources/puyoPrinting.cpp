#include <SFML/Graphics.hpp>

#include "../puyoBoard.hpp"
#include "../puyoPlayPuyo.hpp"
#include "puyoPrinting.hpp"
#include "../puyoPhase/puyoTempPuyo.hpp"

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
puyoPrinting::puyoPrinting(RenderWindow& w) : window(w) {};

void puyoPrinting::print_puyo(Sprite puyo, float x, float y, int color, int dir)
{
    const int img_x = PUYO_SIZE*dir, img_y = PUYO_SIZE*color;
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
            const int x = player_board_x + PUYO_SIZE*j, y = player_board_y + PUYO_SIZE*i;
            const int curr_puyo = board.get_puyo(i,j);
            const int dir = 1*(board.is_in_board(i+1,j) && board.get_puyo(i+1,j) == curr_puyo)+
                            2*(board.is_in_board(i-1,j) && board.get_puyo(i-1,j) == curr_puyo)+
                            4*(board.is_in_board(i,j+1) && board.get_puyo(i,j+1) == curr_puyo)+
                            8*(board.is_in_board(i,j-1) && board.get_puyo(i,j-1) == curr_puyo);
            print_puyo(puyo,x,y,board.get_puyo(i,j),dir);//0대신 주변 뿌요 감지해서 방향 설정
        }
}

void puyoPrinting::print_player_puyo(Sprite puyo, puyoPlayPuyo& playPuyo, int player_num)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];

    const auto [x1,y1,x2,y2] = playPuyo.get_puyo_pos();
    const auto [color1,color2] = playPuyo.get_puyo_color();

    const int x3 = player_board_x + PUYO_SIZE*x1, y3 = player_board_y + PUYO_SIZE*y1;
    print_puyo(puyo,x3,y3,color1,0);
    const int x4 = player_board_x + PUYO_SIZE*x2, y4 = player_board_y + PUYO_SIZE*y2;
    print_puyo(puyo,x4,y4,color2,0);
}

void puyoPrinting::print_future_puyo(Sprite puyo, int player_num, vector<future_puyo> future_puyos)
{
    puyo.setColor(Color(255, 255, 255, 128*FUTURE_PUYO_ALPHA_VALUE));//투명도 조절

    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    future_puyo fp1 = future_puyos[0], fp2 = future_puyos[1]; 
    const int x1 = player_board_x + PUYO_SIZE*fp1.x, y1 = player_board_y + PUYO_SIZE*fp1.y;
    print_puyo(puyo,x1,y1,fp1.color,0);
    const int x2 = player_board_x + PUYO_SIZE*fp2.x, y2 = player_board_y + PUYO_SIZE*fp2.y;
    print_puyo(puyo,x2,y2,fp2.color,0);
}

void puyoPrinting::print_temp_puyo(Sprite puyo, puyoBoard& board, int player_num, vector<puyoTempPuyo>& temp_puyos)
{
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    for(auto& temp_puyo : temp_puyos)
    {
        const auto [x,y] = temp_puyo.get_puyo_pos();
        const int color = temp_puyo.get_puyo_color();
        const int x1 = player_board_x + PUYO_SIZE*x, y1 = player_board_y + PUYO_SIZE*y;
        print_puyo(puyo,x1,y1,TEMP_PUYO_Y,TEMP_PUYO_X+color);
        print_puyo(puyo,x1,y1,TEMP_PUYO_Y+1,TEMP_PUYO_X+color);
    }
}

void puyoPrinting::print_screen(Sprite screen, int player_count)
{
    if(player_count != 1 && player_count != 2)
        throw runtime_error("Player count is over limit");
    screen.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count), 0}, {static_cast<int>(SCREEN_X),static_cast<int>(SCREEN_Y)})); 
    print_sprite(screen,0,0);
}
