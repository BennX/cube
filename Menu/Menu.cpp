/*
* Menu.cpp
*
* Created: 30.03.2015 18:28:35
* Author: Benjamin
*/


#include "Menu.h"

// default constructor
Menu::Menu()
{
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::update()
{
    Display::set_cursor(0, 0);
    Display::write_string_P(PSTR("WAT"));
}