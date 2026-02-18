#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "printObject/puyoPrintObject.hpp"
#include "printText/puyoPrintText.hpp"

using namespace std;
using namespace sf;

class puyoPrinting
{
    private :
        vector<unique_ptr<puyoPrintObject>> print_objects;
        vector<unique_ptr<puyoPrintText>> print_texts;
    public :
        puyoPrinting();
        void print_all_objects(RenderWindow& window);
        void print_all_texts(RenderWindow& window);
        void add_print_object(unique_ptr<puyoPrintObject>&& object);
        void add_print_text(unique_ptr<puyoPrintText>&& object);
        bool not_existed_print_object();
        bool not_existed_print_text();

};