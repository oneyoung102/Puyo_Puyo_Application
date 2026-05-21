#pragma once

#include <memory>
#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

class puyoColor : public puyoType
{
    private :
        bool charged;
        static const std::vector<Type> links;
    public :
        puyoColor(Type color, bool is_frozen = false, bool charged = false);
        std::unique_ptr<puyoType> clone() const override;
        int get_weight() const override;
        bool is_colored() const override;

        bool is_linkable(const puyoType& other) const override;

        void charge() override;
        void uncharge() override;
        bool is_charged() const override;
};