#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoFlower.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

using namespace std;

puyoFlower::puyoFlower(Type seed, bool is_frozen, int blooming_time)
    : puyoType(Type::seed_daisy <= seed && seed <= Type::flower_shield
        ? seed
        : throw runtime_error("Invalid flower"),
        State::none,is_frozen)
    , blooming_time(blooming_time)
{
    set_blooming_time();
}

void puyoFlower::set_blooming_time()
{
    switch(type)
    {
        case Type::flower_daisy :
            blooming_time = puyoGameConstant::FLOWER_DAISY_TICK;
            break;
        case Type::flower_flame :
            blooming_time = puyoGameConstant::FLOWER_FLAME_TICK;
            break;
        case Type::flower_shield :
            blooming_time = puyoGameConstant::FLOWER_SHILED_TICK;
            break;
        default :
            break;
    }
}

std::unique_ptr<puyoType> puyoFlower::clone() const {return std::make_unique<puyoFlower>(type,__is_frozen,blooming_time);}
int puyoFlower::get_weight() const {return 0;}

bool puyoFlower::is_linkable(const puyoType& other) const {return false;}

void puyoFlower::update()
{
    if(is_seed())
        return;

    if(this->is_frozen())
        state = puyoType::State::none;
    else
    {
        if(blooming_time <= 0)
            state = puyoType::State::flower_faded;
        else
        {
            --blooming_time;
            state = puyoType::State::flower_blooming;
        }
    }
}

bool puyoFlower::is_seed() const
{
    return Type::seed_daisy <= type && type < Type::flower_daisy;
}

void puyoFlower::bloom()
{
    if(is_seed())
    {
        switch(type)
        {
            case Type::seed_daisy :
                type = Type::flower_daisy;
                break;
            case Type::seed_flame :
                type = Type::flower_flame;
                break;
            case Type::seed_shield :
                type = Type::flower_shield;
                break;
            default :
                break;
        }
        state = State::flower_blooming;
        set_blooming_time();
    }
}