#pragma once

#include "puyoTool/puyoCast.hpp"
#include <array>

template<class T>
class puyoObjectSignal // 템플릿 자료형으로 enum을 사용할 것, enum 마지막 원소로 COUNT를 사용할 것 
{
    private :
        std::array<bool,CASTi(T::COUNT)> signals;
    public :
        puyoObjectSignal()
        {
            signals.fill(false);
        }
        void set_signal(T name){signals[CASTs(name)] = true;}
        bool get_signal(T name)
        {
            const bool s = signals[CASTs(name)];
            signals[CASTs(name)] = false;
            return s;
        };
};