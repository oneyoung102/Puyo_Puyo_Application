#include <SFML/Graphics.hpp>
#include "puyoPrintNextPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintNextPuyo::puyoPrintNextPuyo(int pn, const int& npc, const vector<pair<int,int>>& nc, Sprite puyo, int x, int y, int life)
    : puyoPrintObject(puyo,x,y,life),
     new_colors(nc),
    new_puyo_count(npc)
{
    player_num = pn;
}

void puyoPrintNextPuyo::print_object(RenderWindow& w)
{
    const auto [player_next_puyo_viewer_x,player_next_puyo_viewer_y] = PLAYER_NEXT_PUYO_VIEWER_POS[player_num];
    const auto[color1,color2] = new_colors[new_puyo_count];
    const auto[color3,color4] = new_colors[new_puyo_count+1];
    print_puyo(w,0,color2,x,y);
    print_puyo(w,0,color1,x,y+PUYO_SIZE);
    const int x1 = x + ((player_num == 0) ? NEXT_PUYO_VIEWER_BREADTH : -NEXT_PUYO_VIEWER_BREADTH), y1 = y+PUYO_SIZE;
    print_puyo(w,0,color4,x1,y1);
    print_puyo(w,0,color3,x1,y1+PUYO_SIZE);
}