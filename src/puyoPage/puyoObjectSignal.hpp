#pragma once

#include <vector>

template<class T>
class puyoObjectSignal
{
    protected :
        std::vector<bool> signals;
    public :
        puyoObjectSignal()
        {
            signals = vector<bool>((int)T::COUNT,false);
        }
        bool get_signal(T name)
        {
            const bool s = signals[(int)name];
            signals[(int)name] = false;
            return s;
        };
};