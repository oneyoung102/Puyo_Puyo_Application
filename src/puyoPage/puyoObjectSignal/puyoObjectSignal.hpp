#pragma once

#include <queue>
#include <stdexcept>
#include <type_traits>

template<class T, class P = void>
class has_COUNT : std::false_type {};
template<class T>
class has_COUNT<T, std::void_t<decltype(T::COUNT)>> : std::true_type {};

template<class T>
class puyoObjectSignal //T : enum (last element : COUNT)
{
    private :
        std::queue<T> signals;
    public :
        puyoObjectSignal()
        {
            static_assert(std::is_enum<T>(),"template type of puyoObjectSignal is not as enum");
            static_assert(has_COUNT<T>::value, "enum of puyoObjectSignal must have COUNT value.");
        }

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