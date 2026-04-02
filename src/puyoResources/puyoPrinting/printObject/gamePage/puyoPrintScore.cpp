#include <SFML/Graphics.hpp>
#include "puyoPrintScore.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"


using namespace std;
using namespace puyoImageConstant;
using namespace sf;


puyoPrintScore::puyoPrintScore(int player_num, const int& score, Sprite num, int x, int y, int life)
    : puyoPrintObject(num,x,y,life),
        to_score(score)
{
    from_score = score;
    this->player_num = player_num;
}

void puyoPrintScore::print_num(RenderWindow& w, int img_x, int px, int py)
{
    img_x = NUM_SIZE_X*(img_x+player_num*10);
    sprite.setTextureRect(IntRect({img_x, 0}, {NUM_SIZE_X, NUM_SIZE_Y})); 
    print_sprite(w,px,py);
}

void puyoPrintScore::print_object(RenderWindow& w)
{
    from_score = min(++from_score,to_score);
    for(int px = x, tens = 1e7 ; tens != 0 ; tens /= 10)
    {
        print_num(w,(from_score/tens)%10,px,y);
        px += NUM_SIZE_X;
    }
}