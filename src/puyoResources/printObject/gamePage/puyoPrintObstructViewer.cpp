#include <SFML/Graphics.hpp>
#include "puyoPrintObstructViewer.hpp"
#include "../../puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace std;

puyoPrintObstructViewer::puyoPrintObstructViewer(int& op, Sprite puyo, int x, int y, int life)
    : puyoPrintObject(puyo,x,y,life),
    obstruct_puyo(op)
{
    unit = 7776; //6^5;
}

void puyoPrintObstructViewer::print_object(RenderWindow& w)
{
    int img_x = PUYO_SIZE*OBSTRUCT_PUYOS_X, img_y = PUYO_SIZE*OBSTRUCT_PUYOS_Y, obp = obstruct_puyo, dx = 0;
    int u = unit, count = 6;//6자리만 보여줌
    while(u > 0 && count > 0)
    {
        while(obp >= u && count > 0)
        {
            sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
            print_sprite(w,x+dx,y);
            obp -= u;
            dx += PUYO_SIZE;
            --count;
        }
        img_x -= PUYO_SIZE;
        u /= 6;
    }
}