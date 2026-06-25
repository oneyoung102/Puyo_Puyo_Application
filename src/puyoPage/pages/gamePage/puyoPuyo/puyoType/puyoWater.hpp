#pragma once

#include <memory>
#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

class puyoWater : public puyoType
{
    public :
        puyoWater(bool is_frozen = false);
        std::unique_ptr<puyoType> clone() const override;
        int get_weight() const override;

        bool is_linkable(const puyoType& other) const override;
        virtual void update() override;
};