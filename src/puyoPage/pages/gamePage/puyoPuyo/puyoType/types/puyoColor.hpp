#pragma once

#include <memory>
#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"

class puyoColor : public _puyoType
{
    private :
        static const std::vector<Type> links;
    public :
        puyoColor(Type color, bool is_frozen = false);
        std::unique_ptr<_puyoType> clone() const override;
        bool is_colored() const override;

        bool is_linkable(const _puyoType& other) const override;
};