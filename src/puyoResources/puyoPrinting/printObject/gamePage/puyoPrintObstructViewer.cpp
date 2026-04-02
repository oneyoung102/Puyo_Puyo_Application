#include <SFML/Graphics.hpp>
#include "puyoPrintObstructViewer.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace puyoImageConstant;
using namespace puyoGameConstant;
using namespace std;
using namespace sf;

puyoPrintObstructViewer::puyoPrintObstructViewer(const int& obstruct_puyo, Sprite puyo, int x, int y, int life)
    : puyoPrintObject(puyo,x,y,life),
    obstruct_puyo(obstruct_puyo)
{}

void puyoPrintObstructViewer::print_object(RenderWindow& w)
{
    int img_x = PUYO_SIZE*OBSTRUCT_PUYO_VIEWER_X, img_y = PUYO_SIZE*OBSTRUCT_PUYO_VIEWER_Y, obp = obstruct_puyo, dx = 0;
    int count = 6;//6자리만 보여줌
    for(int i = OBSTRUCT_PUYO_VIEWER_UNIT.size()-1 ; i >= 0 && count > 0 ; --i)
    {
        while(obp >= OBSTRUCT_PUYO_VIEWER_UNIT[i] && count > 0)
        {
            sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
            print_sprite(w,x+dx,y);
            obp -= OBSTRUCT_PUYO_VIEWER_UNIT[i];
            dx += PUYO_SIZE;
            --count;
        }
        img_x -= PUYO_SIZE;
    }
}