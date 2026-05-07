#include <SFML/Graphics.hpp>
#include "puyoPrintBoard.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include "puyoTool/puyoCast.hpp"
#include "puyoTool/puyoDir.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintBoard::puyoPrintBoard(const puyoBoard& board, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , board(board)
{}
void puyoPrintBoard::print(RenderWindow& w)
{
    const auto bsize = board.get_size();
    
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            const auto board_pos = POSf(j, i);
            const auto puyo_type = board.get_puyo(board_pos);
            if(puyo_type.empty())
                continue;
            const auto type = puyo_type.get();
            switch(type)
            {
                case _puyoType::Type::blue :
                case _puyoType::Type::red :
                case _puyoType::Type::yellow :
                case _puyoType::Type::green :
                case _puyoType::Type::pupple :
                {
                    int dir = 0;
                    for(size_t i = 0 ; i < DIR.size() ; ++i)
                        dir += (1<<i)*(board.in(board_pos + DIR[i]) && board.get_puyo(board_pos + DIR[i]) == puyo_type);
                    print_16x16(w,POSi(dir,CASTi(type)),pos+board_pos*PUYO_SIZE);
                    break;
                }
                default :
                    print_puyo(w,puyo_type,pos+board_pos*PUYO_SIZE);
                    break;
            }
        }
}