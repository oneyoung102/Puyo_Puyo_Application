#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"

class puyoBomb : public _puyoType
{
    private :
        int bomb_tick;
        const int bomb_tick_init;
    public :
        puyoBomb(typeState state, bool is_frozen = false, int bomb_tick_init = 1, int bomb_tick = 0);
        std::unique_ptr<_puyoType> clone() const override;
        int get_weight() const override;

        bool is_colored() const override;
        bool is_linkable(const _puyoType& other) const override;

        void update() override;
};