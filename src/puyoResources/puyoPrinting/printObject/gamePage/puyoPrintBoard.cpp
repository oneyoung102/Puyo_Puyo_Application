#include <SFML/Graphics.hpp>
#include "puyoPrintBoard.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintBoard::puyoPrintBoard(const puyoBoard& board, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , board(board){}
void puyoPrintBoard::print(RenderWindow& w)
{
    const auto bsize = board.get_size();
    
    for(int i = 0 ; i < bsize.r ; ++i)
        for(int j = 0 ; j < bsize.c ; ++j)
        {
            const auto board_pos = POSf(j, i);
            const puyoType puyo = board.get_puyo(board_pos);
            switch(puyo)
            {
                case puyoType::blue :
                case puyoType::red :
                case puyoType::yellow :
                case puyoType::green :
                case puyoType::pupple :
                {
                    const int dir = 1*(board.in({j, i+1}) && board.get_puyo({j, i+1}) == puyo)+
                            2*(board.in({j, i-1}) && board.get_puyo({j, i-1}) == puyo)+
                            4*(board.in({j+1, i}) && board.get_puyo({j+1, i}) == puyo)+
                            8*(board.in({j-1, i}) && board.get_puyo({j-1, i}) == puyo);
                    print_16x16(w,POSi(dir,(int)puyo),pos+board_pos*PUYO_SIZE);
                    break;
                }
                default :
                    print_puyo(w,puyo,pos+board_pos*PUYO_SIZE);
                    break;
            }
        }
}