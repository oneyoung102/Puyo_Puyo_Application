#pragma once

#include <memory>
#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

class puyoFlower : public puyoType
{
    private :
        int blooming_time;
        void set_blooming_time();
    public :
        puyoFlower(Type seed, bool is_frozen = false, int blooming_time = 0);
        std::unique_ptr<puyoType> clone() const override;
        int get_weight() const override;

        bool is_linkable(const puyoType& other) const override;
        virtual void update() override;

        virtual bool is_seed() const override;
        virtual void bloom() override;
};