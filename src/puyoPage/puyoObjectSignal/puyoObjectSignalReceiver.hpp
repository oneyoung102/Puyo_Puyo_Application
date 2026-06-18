#pragma once

#include "puyoPage/puyoObjectSignal/puyoObjectSignal.hpp"
#include "puyoTool/puyoCast.hpp"
#include <array>
#include <functional>

template<class T, class ... ARGS>
class puyoObjectSignalReceiver // FUNC : function, T : enum (last element : COUNT)
{
    private :
        using FUNC = std::function<void(ARGS ...)>;
        std::array<FUNC, CASTs(T::COUNT)> executes;
    public :
        puyoObjectSignalReceiver(){}

        void execute(puyoObjectSignal<T>& object_signal, ARGS ... args)
        {
            while(!object_signal.signal_empty())
            {
                const auto idx = CASTs(object_signal.give_signal());
                if(executes[idx])
                    executes[idx](args ...);
            }
        }
        void add_execute(T signal, FUNC&& execute)
        {
            executes[CASTs(signal)] = std::move(execute);
        }
};