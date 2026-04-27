#include <SFML/Graphics.hpp>
#include "puyoPrintSpawnspot.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoPrintSpawnspot::puyoPrintSpawnspot(int player_num, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , player_num(player_num)
{
    spawn_spot_state = 0;
    spawn_spot_rotate_dir = false;//왼쪽
}

void puyoPrintSpawnspot::print(RenderWindow& w)
{
    if(spawn_spot_state == SPAWN_SPOT_STATE_MAX*SPAWN_SPOT_CYCLE_TICK-1 || spawn_spot_state == -1)
        spawn_spot_rotate_dir ^= 1;
    const auto img_pos = (SPAWN_SPOT_POS+POSi(spawn_spot_state/SPAWN_SPOT_CYCLE_TICK,0))*PUYO_SIZE;
    
    sprite.setTextureRect(IntRect({img_pos.x, img_pos.y}, {PUYO_SIZE, PUYO_SIZE})); 
    if(spawn_spot_rotate_dir)
    {
        sprite.setScale({1, 1});
        ++spawn_spot_state;
        print_sprite(w,PLAYER_BOARD_POS[player_num]+POS(pos.x,max(pos.y,0.0f))*PUYO_SIZE);
    }
    else
    {
        sprite.setScale({-1, 1});
        --spawn_spot_state;
        print_sprite(w,PLAYER_BOARD_POS[player_num]+POS(pos.x+1,max(pos.y,0.0f))*PUYO_SIZE);//반전 때문에 +1
    }
}