#pragma once

#include <queue>
#include <stdexcept>

template<class T>
class puyoObjectSignal //T : enum (last element : COUNT)
{
    private :
        std::queue<T> signals;
    public :
        puyoObjectSignal(){}

        void signal(T signal){signals.push(signal);}
        T give_signal()
        {
            if(signal_empty())
                throw std::runtime_error("no signal");
            T signal = signals.front();
            signals.pop();
            return signal;
        }
        bool signal_empty() const {return signals.empty();}
};