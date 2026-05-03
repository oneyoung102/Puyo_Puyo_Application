#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "printObject/puyoPrintObject.hpp"
#include "printText/puyoPrintText.hpp"
#include "printButton/puyoPrintButton.hpp"


class puyoPrinting
{
    private :
        std::vector<std::unique_ptr<puyoPrintObject>> print_objects;
        std::vector<std::unique_ptr<puyoPrintText>> print_texts;
        std::vector<std::unique_ptr<puyoPrintButton>> print_buttons;
    public :
        puyoPrinting();
        void print_all_objects(sf::RenderWindow& window);
        void print_all_texts(sf::RenderWindow& window);
        void print_all_buttons(sf::RenderWindow& window);

        void add_print_object(std::unique_ptr<puyoPrintObject>&& object);
        void add_print_text(std::unique_ptr<puyoPrintText>&& text);
        void add_print_button(std::unique_ptr<puyoPrintButton>&& button);

        bool print_objects_empty();
        bool print_texts_empty();
        bool print_buttons_empty();

        void clear_object_back();
        void clear_text_back();
        void clear_button_back();

        bool object_back_alive();
        bool text_back_alive();
        bool button_back_alive();
};