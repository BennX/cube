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
#include "../Animation/Animator.h"
#include "MenuEntry.h"
#define CLICK_DELAY 1000
#define DISPLAY_LIGHT_OF_TIMER 8000
#define DISPLAY_FADE_OUT_TIME 2000.0
#define DISPLAY_FADE_ON_TIME 2000.0
class MenuEntry;
class Menu
{
//functions
public:
    Menu(Input *i, Animator *a);
    ~Menu();
    void start(const uint8_t &animation);
    void leaveSubmenu();
    void addEntry(MenuEntry *e);
    void update(const short &delta);

private:
    Menu( const Menu &c );
    Menu &operator=( const Menu &c );
    Input *input;
    //the animator class
    Animator *animator;
    //List with all menu entrys
    LinkedList<MenuEntry *> m_list;

    //did the status change? redraw
    bool changed;
    //curent menu position
    int8_t cur_pos;
    //if submenu to know hich is selected
    int8_t m_cur_selected;
    bool m_cur_submenu;

    //click reset timer
    uint16_t clicktimer;
    //display fade timer
    uint16_t display_light_timer;

    //if display is on
    bool displayIsOn;
    //clicked some time ago? not reset yet
    bool clicked;
    //fading bools
    bool fadeOn, fading;

}; //Menu

#endif //__MENU_H__
