#include <SFML/Graphics.hpp>
#include "puyoPrintObstructViewer.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace puyoImageConstant;
using namespace puyoGameConstant;
using namespace std;
using namespace sf;

puyoPrintObstructViewer::puyoPrintObstructViewer(const int& obstruct_puyo, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life),
    obstruct_puyo(obstruct_puyo)
{}

void puyoPrintObstructViewer::print(RenderWindow& w)
{
    POSi img_pos = puyoImageConstant::OBSTRUCT_VIEWER_PUYO_POS*PUYO_SIZE;
    int obp = obstruct_puyo, dx = 0, count = OBSTRUCT_VIEWER_UPPER;//몇 자리까지 보여줄지
    for(int i = OBSTRUCT_VIEWER_UNIT.size()-1 ; i >= 0 && count > 0 ; --i)
    {
        while(obp >= OBSTRUCT_VIEWER_UNIT[i] && count > 0)
        {
            sprite.setTextureRect(IntRect({img_pos.x, img_pos.y}, {PUYO_SIZE, PUYO_SIZE})); 
            print_sprite(w,pos+POSf(dx,0));
            obp -= OBSTRUCT_VIEWER_UNIT[i];
            dx += PUYO_SIZE;
            --count;
        }
        img_pos.x -= PUYO_SIZE;
    }
}