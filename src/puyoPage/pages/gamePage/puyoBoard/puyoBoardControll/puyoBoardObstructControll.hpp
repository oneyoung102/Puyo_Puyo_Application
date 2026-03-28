#pragma once

class puyoBoard;

class puyoBoardObstructControll
{
    private :
        int obstruct_puyo;
        int temp_obstruct_puyo; //방해뿌요 소리를 위한 임시 방해뿌요 개수
        bool approvement_for_obstruct_puyo;
    public :
        puyoBoardObstructControll();
        void give_obstruct_puyo(int count);
        void spawn_obstruct_puyo(puyoBoard& board, int obstruct_puyo_for_dropping);
        bool obstructed_puyo_empty();
        int& get_obstruct_puyo();
        int get_temp_obstruct_puyo();

        void approve_spawn_obstruct_puyo();
        void disapprove_spawn_obstruct_puyo();
};