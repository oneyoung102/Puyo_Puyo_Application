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
            const auto& board_pos = POSf(j, i);
            const auto& puyo  = board.view(board_pos);
            if(puyo.empty())
                continue;
            switch(puyo.get_type())
            {
                case puyoType::Type::blue :
                case puyoType::Type::red :
                case puyoType::Type::yellow :
                case puyoType::Type::green :
                case puyoType::Type::purple :
                    if(!puyo.is_frozen() && !puyo.is_charged()) //의도적으로 break 안 함
                    {
                        int dir = 0;
                        for(size_t i = 0 ; i < DIR.size() ; ++i)
                        {
                            const auto pos = board_pos + DIR[i];
                            dir += (1<<i)*(board.in(pos) && board.view(pos) == puyo && !board.view(pos).is_frozen() && !board.view(pos).is_charged());
                        }
                        print_16x16(w,POSi(dir,CASTi(puyo.get_type())),pos+board_pos*PUYO_SIZE);
                        break;
                    }
                default :
                    print_puyo(w,puyo,pos+board_pos*PUYO_SIZE);
                    break;
            }
        }
}