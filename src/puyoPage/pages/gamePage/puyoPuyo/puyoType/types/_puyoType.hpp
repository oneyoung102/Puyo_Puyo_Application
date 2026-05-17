#pragma once

#include <memory>

class _puyoType
{
    public :
        enum class Type
        {
            red,
            green,
            blue,
            yellow,
            pupple,
            obstruct,
            bomb
        };
        enum class typeState
        {
            none,
            explode_stay1,
            explode_stay2,
            explode_soon1,
            explode_soon2,
            exploded,
        };
    protected :
        const Type type;
        typeState state;
        bool _is_frozen;
    public :
        _puyoType(Type type, typeState state = typeState::none, bool _is_frozen = false)
            : type(type)
            , state(state)
            , _is_frozen(_is_frozen)
        {}
        virtual ~_puyoType() = default;
        virtual std::unique_ptr<_puyoType> clone() const = 0;

        Type get() const {return type;}
        bool is_same(const _puyoType& other) const {return this->get() == other.get();}
        virtual int get_weight() const = 0;

        virtual bool is_colored() const = 0;
        virtual bool is_linkable(const _puyoType& other) const = 0; // this -> other 로의 연결 가능 여부

        virtual void update() {};
        virtual typeState get_state() const {return state;}

        void freeze() {_is_frozen = true;} 
        void unfreeze() {_is_frozen = false;} 
        bool is_frozen() const {return _is_frozen;} 

        virtual void charge() {return;}
        virtual void uncharge() {return;}
        virtual bool is_charged() const {return false;}
};