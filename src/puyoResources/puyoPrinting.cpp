#include <SFML/Graphics.hpp>

#include "../puyoPlayer.hpp"
#include "puyoPrinting.hpp"

#include <tuple>

using namespace std;
using namespace sf;


using namespace puyoImageConstant;


void puyoPrinting::printSprite(Sprite sprite, float x, float y)
{
    sprite.setPosition({x, y});
    window.draw(sprite);
}
puyoPrinting::puyoPrinting(RenderWindow& w) : window(w) {};

void puyoPrinting::printPuyo(Sprite puyo, float x, float y, int color, int dir)
{
    const int img_r = PUYO_SIZE*dir, img_c = PUYO_SIZE*color;
    puyo.setTextureRect(IntRect({img_r, img_c}, {PUYO_SIZE, PUYO_SIZE})); 
    printSprite(puyo,x,y);
}

void puyoPrinting::printBoard(Sprite puyo, puyoPlayer& player)
{
    const int player_num = player.get_player_num();
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    const auto [board_r,board_c] = player.get_board().get_board_size();
    
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            const int x = player_board_x + PUYO_SIZE*j, y = player_board_y + PUYO_SIZE*i;
            printPuyo(puyo,x,y,player.get_board().get_puyo(i,j),0);//0대신 주변 뿌요 감지해서 방향 설정
        }
}

void puyoPrinting::printPlayerPuyo(Sprite puyo, puyoPlayer& player)
{
    const int player_num = player.get_player_num();

    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];

    const auto [x1,y1,x2,y2] = player.get_puyo().get_puyo_pos();
    const auto [color1,color2] = player.get_puyo().get_puyo_color();

    const int x3 = player_board_x + PUYO_SIZE*x1, y3 = player_board_y + PUYO_SIZE*y1;
    printPuyo(puyo,x3,y3,color1,0);
    const int x4 = player_board_x + PUYO_SIZE*x2, y4 = player_board_y + PUYO_SIZE*y2;
    printPuyo(puyo,x4,y4,color2,0);
}

void puyoPrinting::printScreen(Sprite screen, int player_count)
{
    if(player_count != 1 && player_count != 2)
        throw runtime_error("Player count is over limit");
    screen.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count), 0}, {static_cast<int>(SCREEN_X),static_cast<int>(SCREEN_Y)})); 
    printSprite(screen,0,0);
}
