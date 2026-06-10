#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

class puyoObstruct : public puyoType
{
    public :
        puyoObstruct(bool is_frozen = false);
        std::unique_ptr<puyoType> clone() const override;
        int get_weight() const override;
        bool is_linkable(const puyoType& other) const override;
};