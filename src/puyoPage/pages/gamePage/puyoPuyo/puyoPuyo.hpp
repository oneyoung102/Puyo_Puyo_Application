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
        puyoPuyo& operator=(const puyoPuyo& other) noexcept;
        puyoPuyo& operator=(puyoPuyo&& other) noexcept;

/////////type

        bool operator==(const puyoPuyo& other) const noexcept;
        bool operator!=(const puyoPuyo& other) const noexcept;
        bool is_same(puyoType::Type type) const;
        
        puyoType::Type get_type() const;
        int get_weight() const;

        bool is_colored() const;
        bool is_linkable(const puyoPuyo& other) const;
        bool is_gravityable() const;
        bool empty() const;

        void update();
        puyoType::State get_type_state() const;

        void freeze();
        void unfreeze();
        bool is_frozen() const;

        void charge();
        void uncharge();
        bool is_charged() const;

        bool is_seed() const;
        void bloom();
///////// act
        void move(const POSf& to_pos);

        POSf get_pos() const;

        float get_act_state() const;
        int get_tick() const;

        bool acting() const;
        bool halted() const;
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
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoWall.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoWater.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoFlower.hpp"

#define P_COLOR(x) std::make_unique<puyoColor>(puyoType::Type::x)
#define P_RED = P_COLOR(red)
#define P_GREEN = P_COLOR(green)
#define P_BLUE = P_COLOR(blue)
#define P_YELLOW = P_COLOR(yellow)
#define P_PUPPLE = P_COLOR(pupple)
#define P_OBSTRUCT std::make_unique<puyoObstruct>()
#define P_BOMB(x) std::make_unique<puyoBomb>(puyoType::State::explode_stay1,false,x)
#define P_WALL std::make_unique<puyoWall>()
#define P_WATER std::make_unique<puyoWater>()
#define P_FLOWER(x) std::make_unique<puyoFlower>(puyoType::Type::x,false,0)