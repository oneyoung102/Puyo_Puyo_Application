#include <SFML/Graphics.hpp>
#include "puyoPrintBoard.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include "puyoTool/puyoDir.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintBoard::puyoPrintBoard(const puyoBoard& board, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , board(board){}
void puyoPrintBoard::print(RenderWindow& w)
{
    const auto bsize = board.get_size();
    
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
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
                    int dir = 0;
                    for(size_t i = 0 ; i < 4 ; ++i)
                        dir += (1<<i)*(board.in(board_pos + DIR[i]) && board.get_puyo(board_pos + DIR[i]) == puyo);
                    print_16x16(w,POSi(dir,static_cast<int>(puyo)),pos+board_pos*PUYO_SIZE);
                    break;
                }
                default :
                    print_puyo(w,puyo,pos+board_pos*PUYO_SIZE);
                    break;
            }
        }
}