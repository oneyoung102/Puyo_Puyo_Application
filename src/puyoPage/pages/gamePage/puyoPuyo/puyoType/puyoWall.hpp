#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

class puyoWall : public puyoType
{
    public :
        puyoWall(bool is_frozen = false);
        std::unique_ptr<puyoType> clone() const override;
        int get_weight() const override;
        bool is_colored() const override;
        bool is_linkable(const puyoType& other) const override;
        bool is_gravityable() const override;

        void freeze() override;
};