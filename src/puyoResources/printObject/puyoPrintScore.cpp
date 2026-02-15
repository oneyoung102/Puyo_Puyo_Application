#include <SFML/Graphics.hpp>
#include "puyoPrintScore.hpp"
#include "../puyoPrinting.hpp"

puyoPrintScore::puyoPrintScore(int pn, int& s, Sprite num, int x, int y, int life)
    : puyoPrintObject(num,x,y,life),
        score(s)
{
    player_num = pn;
}

void puyoPrintScore::print_num(RenderWindow& w, int img_x, int px, int py)
{
    img_x = NUM_SIZE_X*(img_x+player_num*10);
    sprite.setTextureRect(IntRect({img_x, 0}, {NUM_SIZE_X, NUM_SIZE_Y})); 
    print_sprite(w,px,py);
}

void puyoPrintScore::print_object(RenderWindow& w)
{
    for(int px = x, tens = 1e7 ; tens != 0 ; tens /= 10)
    {
        print_num(w,(score/tens)%10,px,y);
        px += NUM_SIZE_X;
    }
}