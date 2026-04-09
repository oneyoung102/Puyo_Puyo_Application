#include <SFML/Graphics.hpp>
#include "puyoPrintSpawnspot.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <utility>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoPrintSpawnspot::puyoPrintSpawnspot(int player_num, Sprite puyo, int x, int y, int life)
    : puyoPrintObject(puyo,x,y,life)
    , SPAWN_SPOT_CYCLE(800)
{
    this->player_num = player_num;
    spawn_spot_state = 0;
    spawn_spot_rotate_dir = false;//왼쪽
}

void puyoPrintSpawnspot::print(RenderWindow& w)
{
    if(spawn_spot_state == SPAWN_SPOT_STATE_MAX*SPAWN_SPOT_CYCLE-1 || spawn_spot_state == -1)
        spawn_spot_rotate_dir ^= 1;
    const auto [player_board_x,player_board_y] = PLAYER_BOARD_POS[player_num];
    const int img_x = PUYO_SIZE*(SPAWN_SPOT_STATE_X+spawn_spot_state/SPAWN_SPOT_CYCLE), img_y = PUYO_SIZE*SPAWN_SPOT_STATE_Y;
    
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    if(spawn_spot_rotate_dir)
    {
        sprite.setScale({1, 1});
        ++spawn_spot_state;
        print_sprite(w,player_board_x + PUYO_SIZE*x,player_board_y + PUYO_SIZE*max(y,0.0));
    }
    else
    {
        sprite.setScale({-1, 1});
        --spawn_spot_state;
        print_sprite(w,player_board_x + PUYO_SIZE*(x+1),player_board_y + PUYO_SIZE*max(y,0.0));//반전 때문에 +1
    }
}