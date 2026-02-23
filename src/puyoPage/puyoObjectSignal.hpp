#pragma once

#include <vector>

template<class T>
class puyoObjectSignal // 템플릿 자료형으로 enum을 사용할 것, enum 마지막 원소로 COUNT를 사용할 것 
{
    protected :
        std::vector<bool> signals;
    public :
        puyoObjectSignal()
        {
            signals = std::vector<bool>((int)T::COUNT,false);
        }
        bool get_signal(T name)
        {
            const bool s = signals[(int)name];
            signals[(int)name] = false;
            return s;
        };
};