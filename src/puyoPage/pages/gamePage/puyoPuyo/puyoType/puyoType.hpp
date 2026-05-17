#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"

class puyoType
{
    private :
        std::unique_ptr<_puyoType> type;
    public :
        puyoType();
        puyoType(std::unique_ptr<_puyoType> type);
        puyoType(const puyoType& other);
        puyoType& operator=(const puyoType& other) noexcept;
        puyoType& operator=(puyoType&& other) noexcept;

        bool operator==(const puyoType& other) const noexcept;
        bool operator!=(const puyoType& other) const noexcept;
        
        _puyoType::Type get() const;
        int get_weight() const;

        bool is_colored() const;
        bool is_linkable(const puyoType& other) const;
        bool empty() const;

        void update();
        _puyoType::typeState get_state() const;

        void freeze();
        void unfreeze();
        bool is_frozen() const;

        void charge();
        void uncharge();
        bool is_charged() const;
};

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoColor.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoObstruct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoBomb.hpp"

#define P_COLOR(x) std::make_unique<puyoColor>(_puyoType::Type::x)
#define P_RED = P_COLOR(red)
#define P_GREEN = P_COLOR(green)
#define P_BLUE = P_COLOR(blue)
#define P_YELLOW = P_COLOR(yellow)
#define P_PUPPLE = P_COLOR(pupple)
#define P_OBSTRUCT std::make_unique<puyoObstruct>()
#define P_BOMB(x) std::make_unique<puyoBomb>(_puyoType::typeState::explode_stay1,false,x)