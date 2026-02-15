#include <SFML/Graphics.hpp>

#include "puyoPrinting.hpp"
#include <vector>

using namespace std;
using namespace sf;


puyoPrinting::puyoPrinting(RenderWindow& w) : window(w){}

void puyoPrinting::print_all_objects()
{
    for(int i = 0 ; i < print_objects.size() ; )
    {
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
}

void puyoPrinting::add_print_object(unique_ptr<puyoPrintObject>&& object){print_objects.push_back(std::move(object));}
