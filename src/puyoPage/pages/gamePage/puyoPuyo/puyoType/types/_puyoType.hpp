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
    protected :
        const Type type;
        bool _is_frozen;
    public :
        _puyoType(Type type, bool _is_frozen = false) : type(type), _is_frozen(_is_frozen) {}
        virtual ~_puyoType() = default;
        virtual std::unique_ptr<_puyoType> clone() const = 0;

        Type get() const {return type;}
        bool is_same(const _puyoType& other) const {return this->get() == other.get();}

        virtual bool is_colored() const = 0;
        virtual bool is_linkable(const _puyoType& other) const = 0; // this -> other 로의 연결 가능 여부

        virtual float get_bomb_state() const {return 0;}
        virtual void proceed_bomb(){};
        virtual bool is_exploded() const {return false;};

        void freeze() {_is_frozen = true;} 
        void unfreeze() {_is_frozen = false;} 
        bool is_frozen() const {return _is_frozen;} 
};