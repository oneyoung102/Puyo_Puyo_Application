#pragma once

#include <vector>

using namespace std;

class puyoTempPuyo;
class puyoBoard;

class puyoPhasing
{
    private :
        bool temp_puyo_did_existed = false;
        vector<puyoTempPuyo> temp_puyos;
    public :
        void push_temp_puyo(puyoTempPuyo&& ptp);
        void push_temp_puyo(vector<puyoTempPuyo>&& ptp_v);
        bool gravity_temp_puyos(puyoBoard& board);

        bool all_puyo_deployed();
        bool not_existed_temp_puyo();
        vector<puyoTempPuyo>& get_temp_puyos();
        pair<int,int> get_new_puyo_color();
};