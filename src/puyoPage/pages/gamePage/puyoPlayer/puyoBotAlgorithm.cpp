#include "puyoBotAlgorithm.hpp"
#include "puyoTool/puyoCast.hpp"
#include "puyoTool/puyoDir.hpp"
#include <random>
#include <cmath>
#include <queue>

using namespace std;

vector<pair<int,int>> puyoBotAlgorithm::calc_all_probablities(const puyoBoard& board)
{
    vector<pair<int,int>> all_probablities;
    const auto bsize = board.get_size();
    const auto[spawn_x,_] = board.get_spawn_pos();
    for(size_t c = 0 ; c < bsize.c ; ++c)
        for(int t = 0 ; t < 4 ; ++t)//4방위
            all_probablities.push_back(make_pair(c-spawn_x,t));
    return all_probablities;
}
tuple<POSi,POSi> puyoBotAlgorithm::to_coord(pair<int,int> probablity, const puyoPlayPuyo& puyo)
{
    auto[pos1,pos2] = puyo.get_pos();
    const auto[move_count,turn_count] = probablity;
    pos1.x += move_count;
    pos2.x += move_count;
    auto dpos = POSf(round(pos2.x - pos1.x), round(pos2.y - pos1.y));
    for(int i = 0; i < turn_count; ++i)
        dpos = POSf(dpos.y,-dpos.x);
    pos2 = pos1+dpos;
    return make_tuple(pos1,pos2);
}

bool puyoBotAlgorithm::simulate_drop(std::vector<std::vector<puyoType>>& simulate_board, POSi& pos1, POSi& pos2, puyoType type1, puyoType type2)
{
    const bool swapped = pos1.y < pos2.y;
    if(swapped) //더 아래있는 걸 먼저 낙하시키기 위해 순서 바꾸기
        swap(pos1,pos2);
    while(pos1.r+1 < simulate_board.size())
        if(pos1.r+1 >= 0 && simulate_board[pos1.r+1][pos1.c] != puyoType::blank)
            break;
        else
            ++pos1.r;
    if(pos1.r < 0)
        return false;
    simulate_board[pos1.r][pos1.c] = type1;
    while(pos2.r+1 < simulate_board.size())
        if(pos2.r+1 >= 0 && simulate_board[pos2.r+1][pos2.c] != puyoType::blank)
            break;
        else
            ++pos2.r;
    if(pos2.r < 0)
        return false;
    simulate_board[pos2.r][pos2.c] = type2;
    if(swapped) //복구
        swap(pos1,pos2);
    return true;
}

void puyoBotAlgorithm::to_let(pair<int,int> perfect_probablity, puyoPlayPuyo& puyo) //명령 벡터 삭제 용이를 위해 거꾸로 명령 푸쉬
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

int puyoBotAlgorithm::get_possiblity(int puyo_count, int sum, int obstruct_puyo)
{
    if(puyo_count == 2)// puyo_count == 2일 때 같은 색 새로운 2개 뿌요가 들어온다면 all clear
        return 100;
    const float ratio = (puyo_count+obstruct_puyo)/(sum + 0.0);
    if(ratio < 0.4)
        return 0;
    const float k = 6.0, x = ratio - 0.75; //0.75 이후는 확률 100
    return CASTi(100/exp(-k * x));
}

puyoBotAlgorithm::puyoBotAlgorithm()
    : gen(random_device{}())
{
    act_time = 0;
}


void puyoBotAlgorithm::think_perfect_lets(puyoBoard& board, puyoPlayPuyo& puyo)
{
    uniform_int_distribution<> dist(0,99);

    int puyo_count = 0;
    const auto bsize = board.get_size();
    vector<vector<puyoType>> simulate_board(bsize.r,vector<puyoType>(bsize.c));
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            simulate_board[i][j] = board.get_puyo({j, i});
            if(simulate_board[i][j] != puyoType::blank)
                ++puyo_count;
        }
    bool fire_chain = false;
    if(dist(gen) < get_possiblity(puyo_count,bsize.r*bsize.c,board.controll_obstuct().get()))
        fire_chain = true;

    const auto spawn_pos = board.get_spawn_pos();
    pair<int,int> perfect_probablity(-spawn_pos.x,0);
    int max_cluster_size = 0, max_cluster_size_sum = 0, bottom_y = 0;

    for(const auto probablity : calc_all_probablities(board))
    {
        auto[pos1,pos2] = to_coord(probablity,puyo);
        if(!board.in(pos1) || !board.in(pos2))
            continue;

        const auto [type1,type2] = puyo.get_type();
        if(!simulate_drop(simulate_board,pos1,pos2,type1,type2))
            continue;

        int cluster_size = 0, cluster_size_sum = 0;
        vector<vector<bool>> visited(bsize.r,vector<bool>(bsize.c,false));
        vector<tuple<POSi,puyoType>> changed;//{x,y,puyo}
        changed.push_back(make_tuple(pos1,(puyoType)type1));
        changed.push_back(make_tuple(pos2,(puyoType)type2));

        for(const auto[pos,curr_puyo] : changed)
        {
            int temp_cluster_size = 0;
            queue<POSi> coords;
            coords.push(pos);
            while(!coords.empty())
            {
                const auto cpos = coords.front();
                coords.pop();
                if(visited[cpos.r][cpos.c])
                    continue;
                visited[cpos.r][cpos.c] = true;
                ++temp_cluster_size;
                for(const auto dpos : DIR)
                {
                    const auto npos = cpos+dpos;
                    if(!board.in(npos))
                        continue;
                    const puyoType npuyo = simulate_board[npos.r][npos.c];
                    if(npuyo == curr_puyo && !visited[npos.r][npos.c])
                        coords.push(npos);
                }
            }
            cluster_size = max(cluster_size,temp_cluster_size);
            cluster_size_sum += temp_cluster_size;
        }
        
        const int temp_bottom_y = max(pos1.y,pos2.y);
        if(cluster_size < board.controll_vanish().get_condition()|| fire_chain)
            if(max_cluster_size < cluster_size
                || max_cluster_size == cluster_size && max_cluster_size_sum < cluster_size_sum
                || max_cluster_size == cluster_size && max_cluster_size_sum == cluster_size_sum &&  bottom_y < temp_bottom_y)
                {
                    max_cluster_size = cluster_size;
                    max_cluster_size_sum = cluster_size_sum;
                    perfect_probablity = probablity;
                    bottom_y = temp_bottom_y;
                }
        simulate_board[pos1.r][pos1.c] = puyoType::blank;//복구
        simulate_board[pos2.r][pos2.c] = puyoType::blank;
    }
    to_let(perfect_probablity,puyo);
}
bool puyoBotAlgorithm::bot_lets_empty(){return lets.empty();}
void puyoBotAlgorithm::let_bot_act()
{
    if(lets.empty())
        return;
    if(act_time > 0)
    {
        --act_time;
        return;
    }
    else
        act_time = 80;
    lets.back()();
    lets.pop_back();
}