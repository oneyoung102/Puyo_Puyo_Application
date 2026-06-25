#include "puyoBot.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoTool/puyoDir.hpp"
#include "puyoTool/puyoCast.hpp"
#include <algorithm>
#include <utility>

using namespace std;

bool puyoBot::get_fire(int puyo_count, int obstruct_puyo)
{
    if(obstruct_puyo >= puyoGameConstant::OBSTRUCT_PUYO_MID)
        return true;
    const auto bsize = simulate_board.get_size();
    const float ratio = (puyo_count+obstruct_puyo)/CASTf(bsize.r * bsize.c);
    if(ratio < 0.4)
        return false;

    const float k = 6.5, x = ratio - 0.70; //0.70 이후는 확률 100
    uniform_int_distribution<> dist(0,99);
    return dist(gen) < CASTi(100/exp(-k * x));
}

vector<puyoBot::PROBABLITY> puyoBot::calc_all_probablities(const puyoBoard& board)
{
    vector<PROBABLITY> all_probablities;
    const auto bsize_c = board.get_size().c;
    const auto spawn_x = board.get_spawn_pos().x;
    for(size_t c = 0 ; c < bsize_c ; ++c)
        for(int t = 0 ; t < DIR.size() ; ++t)//4방위
            all_probablities.push_back(make_pair(c-spawn_x,t));
    return all_probablities;
}
pair<POSi,POSi> puyoBot::to_coord(PROBABLITY probablity, const puyoPlayPuyo& puyo)
{
    auto[pos1,pos2] = puyo.get_pos();
    const auto[move_count,turn_count] = probablity;
    pos1.x += move_count;
    pos2.x += move_count;
    auto dpos = POSi(round(pos2.x - pos1.x), round(pos2.y - pos1.y));
    for(int i = 0; i < turn_count; ++i)
        dpos = POSi(dpos.y,-dpos.x);  
    pos2 = pos1+dpos;
    return {pos1,pos2};
}

pair<POSi,POSi> puyoBot::simulate_drop(const vector<puyoPuyo>& puyos)
{
    auto temp_puyos = puyos;
    const bool swapped = temp_puyos[0].get_pos().r < temp_puyos[1].get_pos().r;
    if(swapped)
        swap(temp_puyos[0],temp_puyos[1]);
        
    for(int i = 0; i < 2; ++i)
    {
        auto pos = temp_puyos[i].get_pos();
        while(pos.r + 1 < simulate_board.get_size().r)
        {
            if(pos.r + 1 >= 0 && !simulate_board.empty(pos+POSi(0,1)))
                break;
            ++pos.r;
        }
        temp_puyos[i].move(pos);
        if(i == 0 && pos.r >= 0)
            simulate_board.insert(temp_puyos[i]);//가상으로 떨어뜨림
    }
    if(temp_puyos[0].get_pos().r >= 0)
        simulate_board.remove(temp_puyos[0].get_pos()); //가상으로 떨어뜨린 거 복구s

    if(swapped)
        swap(temp_puyos[0],temp_puyos[1]);
    return make_pair(temp_puyos[0].get_pos(),temp_puyos[1].get_pos());
}

void puyoBot::to_let(PROBABLITY perfect_probablity, puyoPlayPuyo& puyo) //명령 벡터 삭제 용이를 위해 거꾸로 명령 푸쉬
{
    const auto[move_count,turn_count] = perfect_probablity;
    lets.push_back([&puyo](){return puyo.let_drop();});//드롭
    if(move_count > 0) //좌우 이동
        for(int i = 0 ; i < move_count ; ++i)
            lets.push_back([&puyo](){return puyo.let_right();});
    else
        for(int i = 0 ; i < -move_count ; ++i)
            lets.push_back([&puyo](){return puyo.let_left();});
    for(int i = 0 ; i < turn_count ; ++i)// 회전
        lets.push_back([&puyo](){return puyo.let_turn();});
}

puyoBot::puyoBot(POSi bsize, unsigned int init_act_tick)
    : gen(random_device{}())
    , act_time(0)
    , init_act_tick(init_act_tick)
{}

bool puyoBot::bot_lets_empty(){return lets.empty();}
void puyoBot::let_bot_act()
{
    if(lets.empty())
        return;
    if(act_time > 0)
    {
        --act_time;
        return;
    }
    else
        act_time = init_act_tick;
    lets.back()();
    lets.pop_back();
}