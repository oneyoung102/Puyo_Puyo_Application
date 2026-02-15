#include <vector>
#include <utility>
#include <queue>

#include "puyoBoard.hpp"
#include "puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoTempPuyo/puyoVanishPuyo.hpp"

using namespace std;


puyoBoard::puyoBoard() : board_r(12), board_c(6)
{
    dir = {
        {1,0},{-1,0},{0,1},{0,-1}
    };
    gravity_value = 450;
    vanish_value = 510;
    board = vector<vector<int>>(board_r,vector<int>(board_c,-1));
    gravity_puyo_is_out_in_board = false;
}

pair<float,float> puyoBoard::get_puyo_spawn_pos(){return make_pair(puyo_spawn_x,puyo_spawn_y);}
void puyoBoard::set_puyo_spawn_pos(float x, float y)
{
    puyo_spawn_x = x;
    puyo_spawn_y = y;
};

pair<int,int> puyoBoard::get_board_size(){return make_pair(board_r,board_c);}
bool puyoBoard::is_in_row(int r){return 0 <= r && r < board_r;}
bool puyoBoard::is_in_col(int c){return 0 <= c && c < board_c;}
bool puyoBoard::is_in_board(int r, int c){return is_in_row(r) && is_in_col(c);}//이건 행,열

int puyoBoard::get_puyo(int r, int c){return board[r][c];}//이건 행,열
void puyoBoard::insert_puyo(int puyo, int r, int c){board[r][c] = puyo;}//이건 행,열
void puyoBoard::remove_puyo(int r, int c){board[r][c] = -1;}//이건 행,열


void puyoBoard::push_gravity_puyo(puyoGravityPuyo&& ptp) //std::move
{
    gravity_puyos.push_back(std::move(ptp));
}
void puyoBoard::push_gravity_puyo(vector<puyoGravityPuyo>&& ptp_v)//std::move
{
    for(auto&& ptp : ptp_v)
        push_gravity_puyo(std::move(ptp));
}
void puyoBoard::push_vanish_puyo(puyoVanishPuyo&& ptp) //std::move
{
    vanish_puyos.push_back(std::move(ptp));
}


vector<puyoGravityPuyo>& puyoBoard::get_gravity_puyos(){return gravity_puyos;}
vector<puyoVanishPuyo>& puyoBoard::get_vanish_puyos(){return vanish_puyos;}
vector<puyoFuturePuyo>& puyoBoard::get_future_puyos(){return future_puyos;}
bool puyoBoard::not_existed_gravity_puyo(){return gravity_puyos.empty();}
bool puyoBoard::not_existed_vanish_puyo(){return vanish_puyos.empty();}
bool puyoBoard::gravity_puyo_is_out(){return gravity_puyo_is_out_in_board;}


void puyoBoard::gravity_gravity_puyos()
{
    for(int i = 0 ; i < gravity_puyos.size() ; )
    {
        if(gravity_puyos[i].gravity_stopped())
        {
            if(!gravity_puyos[i].deploy_puyo(*this))
            {
                gravity_puyo_is_out_in_board = true; //배치할 뿌요가 범위를 나감
                return;
            }
            std::swap(gravity_puyos[i], gravity_puyos.back());
            gravity_puyos.pop_back();
        }
        else
        {
            gravity_puyos[i].gravity_let(*this);
            ++i;
        }
    }
}
void puyoBoard::vanish_vanish_puyo()
{
    for(int i = 0 ; i < vanish_puyos.size() ; )
    {
        if(vanish_puyos[i].vanish_stopped())
        {
            std::swap(vanish_puyos[i], vanish_puyos.back());
            vanish_puyos.pop_back();
        }
        else
        {
            vanish_puyos[i].vanish_let(*this);
            ++i;
        }
    }
}

void puyoBoard::find_gravity_puyo()
{
    for(int i = 0 ; i < board_c ; ++i)
    {
        bool push = false;
        for(int j = board_r-1 ; j >= 0 ; --j)//아래에 있는 뿌요가 먼저 오게
        {
            const int puyo = board[j][i];
            if(puyo != -1)
            {
                if(push)
                {
                    push_gravity_puyo(std::move(puyoGravityPuyo(i,j,puyo,gravity_value)));
                    remove_puyo(j,i);
                    continue;
                }
            }
            else
                push = true;
        }

    }
}

void puyoBoard::find_vanish_puyo()
{
    vector<vector<bool>> visited(board_r,vector<bool>(board_c,false));
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            const int puyo = board[i][j];
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
                    if(is_in_board(nr,nc) && get_puyo(nr,nc) == puyo && !visited[nr][nc])
                        coords.push(make_pair(nr,nc));
                }
            }
            if(stored_coords.size() >= condition_for_vanish)
                for(const auto [r,c] : stored_coords)
                {
                    push_vanish_puyo(std::move(puyoVanishPuyo(c,r,puyo,vanish_value)));
                    remove_puyo(r,c);
                }
        }
}
void puyoBoard::find_future_puyos(puyoPlayPuyo& puyo)
{
    future_puyos.clear();
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    const auto[color1,color2] = puyo.get_puyo_color();
    for(int y = (int)y1 ; y < board_r ; ++y)
        if(puyo.puyo_touched(*this,round(x1),y+1))
        {
            if(y1 < y2) --y;//실제로 뿌요를 배치하지 않기에 보정
            future_puyos.push_back(puyoFuturePuyo(round(x1),y,color1));
            break;
        }
    for(int y = (int)y2 ; y < board_r ; ++y)
        if(puyo.puyo_touched(*this,round(x2),y+1))
        {
            if(y1 > y2) --y;//실제로 뿌요를 배치하지 않기에 보정
            future_puyos.push_back(puyoFuturePuyo(round(x2),y,color2));
            break;
        }
}
void puyoBoard::remove_future_puyos(){future_puyos.clear();}


void puyoBoard::set_condition_for_vanish(int amount){condition_for_vanish = amount;}
int puyoBoard::get_condition_for_vanish(){return condition_for_vanish;}