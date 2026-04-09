#include "puyoBotAlgorithm.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include <random>
#include <cmath>
#include <queue>

using namespace std;

vector<pair<int,int>> puyoBotAlgorithm::calc_all_probablities(puyoBoard& board)
{
    vector<pair<int,int>> all_probablities;
    const auto[board_r,board_c] = board.get_size();
    const auto[spawn_x,spawn_y] = board.get_spawn_pos();
    for(int c = 0 ; c < board_c ; ++c)
        for(int t = 0 ; t < 4 ; ++t)//4방위
            all_probablities.push_back(make_pair(c-spawn_x,t));
    return all_probablities;
}
tuple<int,int,int,int> puyoBotAlgorithm::to_coord(pair<int,int> probablity, puyoPlayPuyo& puyo)
{
    auto[x1,y1,x2,y2] = puyo.get_pos();
    const auto[move_count,turn_count] = probablity;
    x1 += move_count;
    x2 += move_count;
    int dx = round(x2 - x1), dy = round(y2 - y1);
    for(int i = 0; i < turn_count; ++i)
    {
        const int ndx = dy, ndy = -dx;
        dx = ndx;
        dy = ndy;
    }
    x2 = x1 + dx;
    y2 = y1 + dy;
    return make_tuple(x1,y1,x2,y2);
}

bool puyoBotAlgorithm::simulate_drop(std::vector<std::vector<puyoType>>& simulate_board, int x1, int& y1, int x2, int& y2, puyoType type1, puyoType type2)
{
    const bool swapped = y1 < y2;
    if(swapped) //더 아래있는 걸 먼저 낙하시키기 위해 순서 바꾸기
    {
        swap(y1,y2);
        swap(x1,x2);
    }
    while(y1+1 < simulate_board.size())
        if(y1+1 >= 0 && simulate_board[y1+1][x1] != puyoType::blank)
            break;
        else
            ++y1;
    if(y1 < 0)
        return false;
    simulate_board[y1][x1] = type1;
    while(y2+1 < simulate_board.size())
        if(y2+1 >= 0 && simulate_board[y2+1][x2] != puyoType::blank)
            break;
        else
            ++y2;
    if(y2 < 0)
        return false;
    simulate_board[y2][x2] = type2;
    if(swapped) //복구
    {
        swap(y1,y2);
        swap(x1,x2);
    }
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
    const double ratio = (puyo_count+obstruct_puyo)/(sum + 0.0);
    if(ratio < 0.4)
        return 0;
    const double k = 6.0;  //기울기
    const double x = ratio - 0.75; //0.75 이후는 확률 100
    return (int)100/exp(-k * x);
}

puyoBotAlgorithm::puyoBotAlgorithm() : gen(random_device{}()) {}


void puyoBotAlgorithm::think_perfect_lets(puyoBoard& board, puyoPlayPuyo& puyo)
{
    uniform_int_distribution<> dist(0,99);

    const vector<pair<int,int>> dir = {
        {1,0},{-1,0},{0,1},{0,-1}
    };
    
    const auto[spawn_x,spawn_y] = board.get_spawn_pos();
    const auto[board_r,board_c] = board.get_size();

    int puyo_count = 0;
    vector<vector<puyoType>> simulate_board(board_r,vector<puyoType>(board_c));
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            simulate_board[i][j] = board.get_puyo(i,j);
            if(simulate_board[i][j] != puyoType::blank)
                ++puyo_count;
        }
    bool fire_chain = false;
    if(dist(gen) < get_possiblity(puyo_count,board_r*board_c,board.controll_obstuct().get()))
        fire_chain = true;

    pair<int,int> perfect_probablity(-spawn_x,0);
    int max_cluster_size = 0, max_cluster_size_sum = 0, bottom_y = 0;

    for(const auto probablity : calc_all_probablities(board))
    {
        auto[x1,y1,x2,y2] = to_coord(probablity,puyo);
        if(!board.in(y1,x1) || !board.in(y2,x2))
            continue;

        const auto [type1,type2] = puyo.get_type();
        if(!simulate_drop(simulate_board,x1,y1,x2,y2,type1,type2))
            continue;

        int cluster_size = 0, cluster_size_sum = 0;
        vector<vector<bool>> visited(board_r,vector<bool>(board_c,false));
        vector<tuple<int,int,puyoType>> changed;//{x,y,puyo}
        changed.push_back(make_tuple(x1,y1,(puyoType)type1));
        changed.push_back(make_tuple(x2,y2,(puyoType)type2));

        for(const auto[x,y,curr_puyo] : changed)
        {
            int temp_cluster_size = 0;
            queue<pair<int,int>> coords;//{r,c}
            coords.push(make_pair(y,x));
            while(!coords.empty())
            {
                const auto [r,c] = coords.front();
                coords.pop();
                if(visited[r][c])
                    continue;
                visited[r][c] = true;
                ++temp_cluster_size;
                for(const auto [dr,dc] : dir)
                {
                    const int nr = r+dr, nc = c+dc;
                    if(!board.in(nr,nc))
                        continue;
                    const puyoType npuyo = simulate_board[nr][nc];
                    if(npuyo == curr_puyo && !visited[nr][nc])
                        coords.push(make_pair(nr,nc));
                }
            }
            cluster_size = max(cluster_size,temp_cluster_size);
            cluster_size_sum += temp_cluster_size;
        }
        
        const int temp_bottom_y = max(y1,y2);
        if(cluster_size < puyoGameConstant::PUYO_VANISH_CONDITION || fire_chain)
            if(max_cluster_size < cluster_size
                || max_cluster_size == cluster_size && max_cluster_size_sum < cluster_size_sum
                || max_cluster_size == cluster_size && max_cluster_size_sum == cluster_size_sum &&  bottom_y < temp_bottom_y)
                {
                    max_cluster_size = cluster_size;
                    max_cluster_size_sum = cluster_size_sum;
                    perfect_probablity = probablity;
                    bottom_y = temp_bottom_y;
                }
        simulate_board[y1][x1] = puyoType::blank;//복구
        simulate_board[y2][x2] = puyoType::blank;
    }
    to_let(perfect_probablity,puyo);
}
bool puyoBotAlgorithm::bot_lets_empty(){return lets.empty();}
void puyoBotAlgorithm::let_bot_act()
{
    if(lets.empty())
        return;
    lets.back()();
    lets.pop_back();
}