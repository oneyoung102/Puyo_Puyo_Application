#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

using namespace std;
puyoType::puyoType() : type(nullptr) {}
puyoType::puyoType(std::unique_ptr<_puyoType> type) : type(std::move(type)) {}
puyoType::puyoType(const puyoType& other) : type(other.type ? other.type->clone() : nullptr){}
puyoType& puyoType::operator=(const puyoType& other) noexcept
{
    if(this != &other) 
    {
        if(other.empty())
            type = nullptr;
        else
            type = other.type->clone();
    }
    return *this;
}
puyoType& puyoType::operator=(puyoType&& other) noexcept
{
    if(this != &other)
    {
        if(other.empty())
            type = nullptr;
        else
            type = std::move(other.type);
    }
    return *this;
}
bool puyoType::operator==(const puyoType& other) const noexcept
{
    if(this == &other) return true;
    if(empty() && other.empty()) return true;
    if(empty() || other.empty()) return false;
    return type->is_same(*other.type);
}
bool puyoType::operator!=(const puyoType& other) const noexcept {return !(*this == other);}


_puyoType::Type puyoType::get() const {return type ? type->get() : _puyoType::Type::obstruct;}
bool puyoType::is_colored() const {return !empty() && type->is_colored();}
bool puyoType::is_linkable(const puyoType& other) const {return !empty() && !other.empty() && type->is_linkable(*other.type);}
bool puyoType::empty() const {return type == nullptr;}

void puyoType::update(){ if(!empty()) type->update();}
_puyoType::typeState puyoType::get_state() const { return empty() ? _puyoType::typeState::none : type->get_state();}

void puyoType::freeze(){ if(!empty()) type->freeze(); }
void puyoType::unfreeze(){ if(!empty()) type->unfreeze(); }
bool puyoType::is_frozen() const {return !empty() && type->is_frozen();}