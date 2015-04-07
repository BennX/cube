/*
 * PStrings.h
 * Put all Strings here which are used multiple Times to safe progmem
 * Created: 07.04.2015 10:01:39
 *  Author: Benjamin
 */
#include <avr/pgmspace.h>
#ifndef __PSTRINGS__
#define __PSTRINGS__
namespace p_strings
{
//golbal
static const char right_arrow[] PROGMEM = ">";
const char procent[] PROGMEM = "%";
const char start[] PROGMEM = "Start";
const char speed[] PROGMEM = "Speed: ";

//single color animation
const char rot[] PROGMEM = "Rot: ";
const char gruen[] PROGMEM = "Gruen: ";
const char blau[] PROGMEM = "Blau: ";

//rain animation
const char tropfen[] PROGMEM = "Tropfen: "; 
const char rate[] PROGMEM = "Rate: ";

}
#endif