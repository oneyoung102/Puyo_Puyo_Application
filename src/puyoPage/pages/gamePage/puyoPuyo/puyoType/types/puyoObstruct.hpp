#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"

class puyoObstruct : public _puyoType
{
    public :
        puyoObstruct(bool is_frozen = false);
        std::unique_ptr<_puyoType> clone() const override;
        int get_weight() const override;
        bool is_colored() const override;
        bool is_linkable(const _puyoType& other) const override;
};