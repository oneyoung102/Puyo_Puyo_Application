#pragma once

#include <memory>
#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"

class puyoColor : public _puyoType
{
    private :
        bool charged;
        static const std::vector<Type> links;
    public :
        puyoColor(Type color, bool is_frozen = false, bool charged = false);
        std::unique_ptr<_puyoType> clone() const override;
        int get_weight() const override;
        bool is_colored() const override;

        bool is_linkable(const _puyoType& other) const override;

        void charge() override;
        void uncharge() override;
        bool is_charged() const override;
};