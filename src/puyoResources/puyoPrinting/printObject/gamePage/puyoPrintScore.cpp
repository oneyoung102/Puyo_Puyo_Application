#include <SFML/Graphics.hpp>
#include "puyoPrintScore.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"


using namespace std;
using namespace puyoImageConstant;
using namespace sf;


puyoPrintScore::puyoPrintScore(int player_num, const int& score, Sprite num, POSf pos, int life)
    : puyoPrintObject(num,pos,life)
    , to_score(score)
    , from_score(score)
    , player_num(player_num)
{}

void puyoPrintScore::print_num(RenderWindow& w, int img_x, POSf screen_pos)
{
    img_x = NUM_SIZE.x*(img_x+player_num*10); //다음 플레이어용 숫자는 현재 플레이어 숫자 0~9 다음에 있으므로 *10
    sprite.setTextureRect(IntRect({img_x, 0}, {NUM_SIZE.x, NUM_SIZE.y})); 
    print_sprite(w,screen_pos);
}

void puyoPrintScore::print(RenderWindow& w)
{
    from_score = min(from_score+SCORE_INCREMENT_DELTA,to_score);
    int decimal = puyoGameConstant::SCORE_UPPER/10;
    for(float px = pos.x ; decimal != 0 ; decimal /= 10)
    {
        print_num(w,(from_score/decimal)%10,{px,pos.y});
        px += NUM_SIZE.x;
    }
}