#include "puyoPhasing.hpp"
#include "puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoTempPuyo/puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoTempPuyo/puyoAction/puyoPuyoVanish_temp.hpp"
#include "../puyoResources/puyoPrinting.hpp"

#include "puyoBoard.hpp"

#include <vector>
#include <algorithm>
#include <memory>
#include <queue>

using namespace std;

puyoPhasing::puyoPhasing()
{
    dir = {
        {1,0},{-1,0},{0,1},{0,-1}
    };
    gravity_value = 450;
    vanish_value = 510;
    game_end = false;
    delay_time = 0;
}


void puyoPhasing::set_condition_for_vanish(int amount){condition_for_vanish = amount;}
int puyoPhasing::get_condition_for_vanish(){return condition_for_vanish;}

void puyoPhasing::act_play_puyo(puyoBoard& board, puyoPlayPuyo& puyo)
{
    puyo.gravity_let(board);
    puyo.act_let(board);
}

void puyoPhasing::gravity_gravity_puyos(puyoBoard& board)
{
    auto& gravity_puyos = board.get_gravity_puyos();
    for(auto it = gravity_puyos.begin(); it != gravity_puyos.end(); )//삭제 수정
        if(it->gravity_stopped())
        {
            if(!it->deploy_puyo(board))
            {
                end_game(); //배치할 뿌요가 범위를 나감
                return;
            }
            it = gravity_puyos.erase(it);
        }
        else
        {
            it->gravity_let(board);
            ++it;
        } 
}
void puyoPhasing::find_gravity_puyo(puyoBoard& board)
{
    const auto [board_r,board_c] = board.get_board_size();
    for(int i = 0 ; i < board_c ; ++i)
    {
        bool push = false;
        for(int j = board_r-1 ; j >= 0 ; --j)//아래에 있는 뿌요가 먼저 오게
        {
            const int puyo = board.get_puyo(j,i);
            if(puyo != -1)
            {
                if(push)
                {
                    board.push_gravity_puyo(std::move(puyoGravityPuyo(i,j,puyo,gravity_value)));
                    board.remove_puyo(j,i);
                    continue;
                }
            }
            else
                push = true;
        }

    }
}



void puyoPhasing::vanish_vanish_puyo(puyoBoard& board)
{
    auto& temp_puyos = board.get_vanish_puyos();
    for(auto it = temp_puyos.begin(); it != temp_puyos.end(); ++it)
        if(it->vanish_stopped())
        {
            temp_puyos.clear();
            return;
        }
        else
            it->vanish_let(board);
}
void puyoPhasing::find_vanish_puyo(puyoBoard& board)
{
    const auto [board_r,board_c] = board.get_board_size();
    vector<vector<bool>> visited(board_r,vector<bool>(board_c,false));
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            const int puyo = board.get_puyo(i,j);
            if(puyo == -1 || visited[i][j])
                continue;
            vector<pair<int,int>> stored_coords;
            queue<pair<int,int>> coords;
            coords.push(make_pair(i,j));
            while(!coords.empty())
            {
                const auto [r,c] = coords.front();
                coords.pop();
                if(visited[r][c])
                    continue;
                stored_coords.push_back(make_pair(r,c));
                visited[r][c] = true;
                for(const auto [dr,dc] : dir)
                {
                    const int nr = r+dr, nc = c+dc;
                    if(board.is_in_board(nr,nc) && board.get_puyo(nr,nc) == puyo && !visited[nr][nc])
                        coords.push(make_pair(nr,nc));
                }
            }
            if(stored_coords.size() >= condition_for_vanish)
                for(const auto [r,c] : stored_coords)
                {
                    board.push_vanish_puyo(std::move(puyoVanishPuyo(c,r,puyo,vanish_value)));
                    board.remove_puyo(r,c);
                }
        }
    
}

void puyoPhasing::delay(int time){delay_time = time;}
void puyoPhasing::wait(){delay_time = max(delay_time-1,0);}
bool puyoPhasing::is_delayed(){return delay_time > 0;}


pair<int,int> puyoPhasing::get_new_puyo_color(int count)
{
    random_device rd;
    mt19937 gen(rd());//랜덤
    while(new_colors.size() < count)
    {
        uniform_int_distribution<> dist1(0, MAX_PUYO_COLOR-1);
        uniform_int_distribution<> dist2(0, MAX_PUYO_COLOR-1);
        new_colors.push_back(make_pair(dist1(gen),dist2(gen)));
    }
    return new_colors[count-1];
}




bool puyoPhasing::game_ended(){return game_end;}
void puyoPhasing::end_game(){game_end = true;}
void puyoPhasing::proceed_game()
{
}

void puyoPhasing::set_game()
{

}

int puyoPhasing::get_player_count(){return (int)players.size();}
vector<unique_ptr<puyoPlayer>>&& puyoPhasing::get_players(){return std::move(players);}