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
const char entry1[] PROGMEM = "test\n";

#define CLICK_DELAY 1000
#define DISPLAY_LIGHT_OF_TIMER 8000
#define DISPLAY_FADE_OUT_TIME 2000.0
#define DISPLAY_FADE_ON_TIME 2000.0
class Menu
{
//functions
public:
    Menu(Input *i, Animator *a);
    ~Menu();
    void update(const short &delta);

private:
    Menu( const Menu &c );
    Menu &operator=( const Menu &c );
    Input *input;
    Animator *animator;

    bool changed;
    int8_t cur_pos;
    uint16_t clicktimer;
	uint16_t display_light_timer;
	bool displayIsOn;
    bool clicked;
	bool fadeOn, fading;
}; //Menu

#endif //__MENU_H__
