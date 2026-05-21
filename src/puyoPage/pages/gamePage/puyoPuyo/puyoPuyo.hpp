#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoTool/puyoPos.hpp"

class puyoBoard;

class puyoPuyo
{
    private :
        POSf pos;
        std::unique_ptr<puyoType> type;
        std::unique_ptr<puyoPuyoAct> act;
    public :
        puyoPuyo(const POSf& pos = POSf(), std::unique_ptr<puyoType>&& type = nullptr, std::unique_ptr<puyoPuyoAct>&& act = nullptr);
        puyoPuyo(const puyoPuyo& other);
        puyoPuyo(puyoPuyo&& other);
/////////type
        puyoPuyo& operator=(const puyoPuyo& other) noexcept;
        puyoPuyo& operator=(puyoPuyo&& other) noexcept;

        bool operator==(const puyoPuyo& other) const noexcept;
        bool operator!=(const puyoPuyo& other) const noexcept;
        bool is_same(puyoType::Type type) const;
        
        puyoType::Type get_type() const;
        int get_weight() const;

        bool is_colored() const;
        bool is_linkable(const puyoPuyo& other) const;
        bool empty() const;

        void update();
        puyoType::typeState get_type_state() const;

        void freeze();
        void unfreeze();
        bool is_frozen() const;

        void charge();
        void uncharge();
        bool is_charged() const;
///////// act
        void move(const POSf& to_pos);

        POSf const get_pos() const;

        float const get_act_state() const;
        int const get_tick() const;

        bool const acting() const;
        bool have_act() const;

        bool decide(const puyoBoard& board);
        void only_act_let();
        void act_let(const puyoBoard& board);
        
        void set_act(std::unique_ptr<puyoPuyoAct>&& act = nullptr);
        void let();   
        
};

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoColor.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoObstruct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoBomb.hpp"

#define P_COLOR(x) std::make_unique<puyoColor>(puyoType::Type::x)
#define P_RED = P_COLOR(red)
#define P_GREEN = P_COLOR(green)
#define P_BLUE = P_COLOR(blue)
#define P_YELLOW = P_COLOR(yellow)
#define P_PUPPLE = P_COLOR(pupple)
#define P_OBSTRUCT std::make_unique<puyoObstruct>()
#define P_BOMB(x) std::make_unique<puyoBomb>(puyoType::typeState::explode_stay1,false,x)