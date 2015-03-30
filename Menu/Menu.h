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

const char entry1[] PROGMEM = "test\n";
class Menu
{
//functions
public:
    Menu();
    ~Menu();
    void update();

private:
    LinkedList<const char *> list;
    Menu( const Menu &c );
    Menu &operator=( const Menu &c );

}; //Menu

#endif //__MENU_H__
