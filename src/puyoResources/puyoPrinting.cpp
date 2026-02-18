#include <SFML/Graphics.hpp>

#include "puyoPrinting.hpp"
#include <vector>

using namespace std;
using namespace sf;


puyoPrinting::puyoPrinting(){}

void puyoPrinting::print_all_objects(RenderWindow& window)
{
    for(int i = 0 ; i < print_objects.size() ; )
        if(print_objects[i]->is_alive())
        {
            print_objects[i]->print_object(window);
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
        if(print_texts[i]->is_alive())
        {
            print_texts[i]->print_text(window);
            ++i;
        }
        else
        {
            std::swap(print_texts[i], print_texts.back());
            print_texts.pop_back();
        }
}

void puyoPrinting::add_print_object(unique_ptr<puyoPrintObject>&& object){print_objects.push_back(std::move(object));}
void puyoPrinting::add_print_text(unique_ptr<puyoPrintText>&& text){print_texts.push_back(std::move(text));}
bool puyoPrinting::not_existed_print_object(){return print_objects.empty();}
bool puyoPrinting::not_existed_print_text(){return print_texts.empty();}
