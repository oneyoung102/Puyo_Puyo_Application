#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"
#include "puyoPuyoDrop.hpp"

using namespace std;


void puyoPuyoDrop::get_drop_height(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    const int iy1 = y1, iy2 = y2;
    for(int i = 1 ; i <= board.get_board_size().first ; ++i)
        if(puyo.puyo_touched(board,x1,iy1+i))
        {
            drop_height = iy1+i-y1-1;
            return;
        }
        else if(puyo.puyo_touched(board,x2,iy2+i))
        {
            drop_height = iy2+i-y2-1;
            return;
        }
}
bool puyoPuyoDrop::test_act(puyoBoard& board,puyoPuyo& puyo){return false;}
bool puyoPuyoDrop::decline_act(puyoBoard& board,puyoPuyo& puyo)
{
    if(act_count == 0)
        get_drop_height(board,puyo);
    return true;
}

puyoPuyoDrop::puyoPuyoDrop(int amount) : puyoPuyoAct(amount){}

void puyoPuyoDrop::act_puyo(puyoPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt_act();
        return;
    }
    const float dy = drop_height/act_count_constant;
    puyo.move_puyo(x1,y1+dy,x2,y2+dy); //이동시키지 말고 puyoPuyoTemp 라는 임시뿌요 클래스를 만들고 플레이어 뿌요를 임시뿌요로 교체하는 방식, 
    // 임시 뿌요는 ~~시스템에 의해 벡터에 들어가고 중력이 작용하여 떨어짐. 이는 보드가 업데이트 될 때마다 보드의 모든 뿌요는 임시 뿌요가 되며 중력의 영향을 받음
    ++act_count;
};
