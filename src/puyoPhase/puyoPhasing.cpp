#include "puyoPhasing.hpp"
#include "puyoTempPuyo.hpp"
#include "../puyoResources/puyoPrinting.hpp"

#include "../puyoBoard.hpp"

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void puyoPhasing::push_temp_puyo(puyoTempPuyo&& ptp)
{
    temp_puyos.push_back(ptp);
    temp_puyo_did_existed = true;
}
void puyoPhasing::push_temp_puyo(vector<puyoTempPuyo>&& ptp_v)
{
    for(auto ptp : ptp_v)
        temp_puyos.push_back(ptp);
    temp_puyo_did_existed = true;
}

bool puyoPhasing::gravity_temp_puyos(puyoBoard& board)
{
    for(auto it = temp_puyos.begin(); it != temp_puyos.end(); )
        if(!it->act_gravity(board))
        {
            if(!it->deploy_puyo(board))
                return false;
            it = temp_puyos.erase(it);
        }
        else
            ++it;
    return true;
}

bool puyoPhasing::not_existed_temp_puyo(){return temp_puyos.empty();}
bool puyoPhasing::all_puyo_deployed()
{
    if(temp_puyo_did_existed && not_existed_temp_puyo())
    {
        temp_puyo_did_existed = false;
        return true;
    }
    return false;
}

vector<puyoTempPuyo>& puyoPhasing::get_temp_puyos(){return temp_puyos;}

pair<int,int> puyoPhasing::get_new_puyo_color()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist1(0, MAX_PUYO_COLOR-1);
    uniform_int_distribution<> dist2(0, MAX_PUYO_COLOR-1);
    return make_pair(dist1(gen),dist2(gen));
}

