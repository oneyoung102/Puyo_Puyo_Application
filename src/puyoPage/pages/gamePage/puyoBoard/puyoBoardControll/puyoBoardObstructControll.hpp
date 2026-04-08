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
        void give(int count);
        void spawn(puyoBoard& board, int obstruct_puyo_for_dropping);
        bool empty();
        const int& get();
        int temp_get();

        void approve_spawn();
        void disapprove_spawn();
};