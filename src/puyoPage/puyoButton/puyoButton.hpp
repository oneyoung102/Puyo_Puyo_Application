#pragma once

#include "puyoPage/puyoButton/puyoButtonCursor.hpp"
#include "puyoPage/puyoKeyBoard/puyoLet.hpp"
#include "puyoPage/puyoObjectSignal/puyoObjectSignalReceiver.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoSounding/puyoSounding.hpp"
#include <functional>

template<size_t R, size_t C, class buttonName>
class puyoButton
{
    private :
        bool __selected;
        puyoObjectSignalReceiver<puyoButtonCursorSignal,puyoFileSystem&> signal_receiver;
    public :
        puyoButtonCursor<R,C,buttonName> cursor;
        
        puyoButton(std::vector<std::vector<buttonName>>&& allocated, bool cyclic = false)
            : cursor(std::move(allocated), cyclic)
            , __selected(false)
        {}
        void set_executes(puyoSounding& ps, puyoLet& pl)
        {
            signal_receiver.add_execute(puyoButtonCursorSignal::cursor, [&ps](puyoFileSystem& pfs){
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cursor));
            });
            signal_receiver.add_execute(puyoButtonCursorSignal::select, [&ps,&pl,this](puyoFileSystem& pfs){
                if(!ps.sounds_empty())
                    ps.clear_back();
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::select));
                pl.clear();
                __selected = true;
            });
        }
        void add_executes(puyoButtonCursorSignal signal, std::function<void(puyoFileSystem&)>&& func)
        {
            signal_receiver.add_execute(signal, std::move(func));
        }
        void receive_signals(puyoFileSystem& pfs)
        {
            signal_receiver.execute(cursor, pfs);
        }
        
        bool selected()
        {
            const bool temp_selected = __selected;
            __selected = false;
            return temp_selected;
        }
};