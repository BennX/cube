/*
* Menu.h
*
* Created: 30.03.2015 18:28:36
* Author: Benjamin
*/


#ifndef __MENU_H__
#define __MENU_H__
#include <avr/pgmspace.h>
#include "../Util/cpp_util.h"
#include "../Util/LinkedList.h"
#include "../Display.h"
#include "../Input.h"
const char entry1[] PROGMEM = "test\n";
#define CLICK_DELAY 1000
class Menu
{
//functions
public:
    Menu(Input *i);
    ~Menu();
    void update(const short &delta);

private:
    Menu( const Menu &c );
    Menu &operator=( const Menu &c );
    Input *input;

    bool changed;
    int8_t cur_pos;
    uint16_t clicktimer;
	bool clicked;
}; //Menu

#endif //__MENU_H__
