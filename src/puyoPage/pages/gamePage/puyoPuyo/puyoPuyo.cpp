#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <utility>

using namespace std;

puyoPuyo::puyoPuyo(const POSf& pos, unique_ptr<puyoType>&& type, unique_ptr<puyoPuyoAct>&& act)
    : pos(pos)
    , type(std::move(type))
    , act(std::move(act))
{}
puyoPuyo::puyoPuyo(const puyoPuyo& other)
{
    this->pos = other.pos;
    if(!other.empty())
        this->type = other.type->clone();
    if(other.have_act())
        this->act = other.act->clone();

}
puyoPuyo::puyoPuyo(puyoPuyo&& other)
{
    this->pos = std::move(other.pos);
    if(!other.empty())
        this->type = std::move(other.type);
    if(other.have_act())
        this->act = std::move(other.act);
}

puyoPuyo& puyoPuyo::operator=(const puyoPuyo& other) noexcept
{
    if(this != &other) 
    {
        this->pos = other.pos;
        if(other.empty())
            type = nullptr;
        else
            type = other.type->clone();
        
        if(other.have_act())
            this->act = other.act->clone();
        else
            act = nullptr;
    }
    return *this;
}
puyoPuyo& puyoPuyo::operator=(puyoPuyo&& other) noexcept
{
    if(this != &other)
    {
        this->pos = std::move(other.pos);
        if(other.empty())
            type = nullptr;
        else
            type = std::move(other.type);
            
        if(other.have_act())
            this->act = std::move(other.act);
        else
            act = nullptr;
    }
    return *this;
}
bool puyoPuyo::operator==(const puyoPuyo& other) const noexcept
{
    if(this == &other) return true;
    if(empty() && other.empty()) return true;
    if(empty() || other.empty()) return false;
    return type->is_same(*other.type);
}
bool puyoPuyo::operator!=(const puyoPuyo& other) const noexcept {return !(*this == other);}
bool puyoPuyo::is_same(puyoType::Type type) const {return this->type->get() == type;}


puyoType::Type puyoPuyo::get_type() const {return type ? type->get() : throw runtime_error("puyoType has no type");}
int puyoPuyo::get_weight() const {return type ? type->get_weight() : 0;}

bool puyoPuyo::is_colored() const {return !empty() && type->is_colored();}
bool puyoPuyo::is_linkable(const puyoPuyo& other) const {return !empty() && !other.empty() && type->is_linkable(*other.type);}
bool puyoPuyo::is_gravityable() const {return !empty() && type->is_gravityable();}
bool puyoPuyo::empty() const {return type == nullptr;}

void puyoPuyo::update(){ if(!empty()) type->update();}
puyoType::State puyoPuyo::get_type_state() const { return empty() ? puyoType::State::none : type->get_state();}

void puyoPuyo::freeze(){ if(!empty()) type->freeze(); }
void puyoPuyo::unfreeze(){ if(!empty()) type->unfreeze(); }
bool puyoPuyo::is_frozen() const {return !empty() && type->is_frozen();}

void puyoPuyo::charge(){if(!empty()) type->charge();}
void puyoPuyo::uncharge(){if(!empty()) type->uncharge();}
bool puyoPuyo::is_charged() const {return !empty() && type->is_charged();}

bool puyoPuyo::is_seed() const {return !empty() && type->is_seed();}
void puyoPuyo::bloom() {if(!empty()) type->bloom();}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void puyoPuyo::move(const POSf& to_pos) {pos = to_pos;}

POSf puyoPuyo::get_pos() const {return pos;}

int puyoPuyo::get_tick() const
{
    if(act)
        return act->get_act_count_init();
    return -1;
}
float puyoPuyo::get_act_state() const
{
    if(act)
        return act->get_state();
    return -1.0;
}

bool puyoPuyo::acting() const {return act && act->acting();}
bool puyoPuyo::halted() const {return act && act->halted();}
bool puyoPuyo::have_act() const {return act != nullptr;}

bool puyoPuyo::decide(const puyoBoard& board){return act && act->decide(board,*this);}
void puyoPuyo::only_act_let(){act->act(*this);}
void puyoPuyo::act_let(const puyoBoard& board)
{
    if(decide(board))
        only_act_let();
}

void puyoPuyo::set_act(unique_ptr<puyoPuyoAct>&& act){this->act = std::move(act);}
void puyoPuyo::let()
{
    if(act)
        act->let();
}
