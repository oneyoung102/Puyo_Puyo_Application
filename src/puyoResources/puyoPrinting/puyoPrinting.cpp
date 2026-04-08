#include <SFML/Graphics.hpp>

#include "puyoPrinting.hpp"
#include <vector>

using namespace std;
using namespace sf;


puyoPrinting::puyoPrinting(){}

void puyoPrinting::print_all_objects(RenderWindow& window)
{
    for(int i = 0 ; i < print_objects.size() ; )
        if(print_objects[i]->alive())
        {
            print_objects[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(print_objects[i], print_objects.back());
            print_objects.pop_back();
        }
}
void puyoPrinting::print_all_texts(RenderWindow& window)
{
    for(int i = 0 ; i < print_texts.size() ; )
        if(print_texts[i]->alive())
        {
            print_texts[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(print_texts[i], print_texts.back());
            print_texts.pop_back();
        }
}
void puyoPrinting::print_all_buttons(RenderWindow& window)
{
    for(int i = 0 ; i < print_buttons.size() ; )
        if(print_buttons[i]->alive())
        {
            print_buttons[i]->print(window);
            ++i;
        }
        else
        {
            std::swap(print_buttons[i], print_buttons.back());
            print_buttons.pop_back();
        }
}

void puyoPrinting::add_print_object(unique_ptr<puyoPrintObject>&& object){print_objects.push_back(std::move(object));}
void puyoPrinting::add_print_text(unique_ptr<puyoPrintText>&& text){print_texts.push_back(std::move(text));}
void puyoPrinting::add_print_button(unique_ptr<puyoPrintButton>&& button){print_buttons.push_back(std::move(button));}

bool puyoPrinting::print_objects_empty(){return print_objects.empty();}
bool puyoPrinting::print_texts_empty(){return print_texts.empty();}
bool puyoPrinting::print_buttons_empty(){return print_buttons.empty();}
