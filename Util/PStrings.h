/*
 * PStrings.h
 * Put all Strings here which are used multiple Times to safe progmem
 * dont forget the declaration one time!
 * Created: 07.04.2015 10:01:39
 *  Author: Benjamin
 */
#include <avr/pgmspace.h>
#ifndef __STRINGS__
#define __STRINGS__


class p_strings
{
public:
    static PROGMEM const char right_arrow[];
    static PROGMEM const char procent[];
    static PROGMEM const char start[];
    static PROGMEM const char speed[];

    //single color animation
    static PROGMEM const char rot[];
    static PROGMEM const char gruen[];
    static PROGMEM const char blau[];

    //rain animation
    static PROGMEM const char tropfen[];
    static PROGMEM const char rate[];
	
	//Ball animation
	static PROGMEM const char size[];
	static PROGMEM const char rnd[];
};


#endif