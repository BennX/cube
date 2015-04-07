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
namespace p_strings
{
//golbal
    extern PROGMEM const char right_arrow[];
    extern PROGMEM const char procent[];
    extern PROGMEM const char start[];
    extern PROGMEM const char speed[];

//single color animation
    extern PROGMEM const char rot[];
    extern PROGMEM const char gruen[];
    extern PROGMEM const char blau[];

//rain animation
    extern PROGMEM const char tropfen[];
    extern PROGMEM const char rate[];
}
#endif