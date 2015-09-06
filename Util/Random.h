/*
* Random.h
* Simple 8bit random number generator. Using shifting
* to have a longer Period shift the shiftvalues
* http://www.arklyffe.com/main/2010/08/29/xorshift-pseudorandom-number-generator/
* Created: 24.02.2015 11:57:51
* Author: Benjamin
*/
#ifndef __RANDOM_H__
#define __RANDOM_H__
#include <avr/pgmspace.h>
/**
 * Put the variables in namespace so "not exedentaly used"
 */

namespace Random
{
    extern PROGMEM const uint8_t shift[];
    extern uint8_t y8;
    extern uint8_t cur_shift;
    extern uint8_t request_count;
}

/**
 * return random 8bit value
 */
extern uint8_t rnd();

/**
 * Return a random float between 0 and 1
 */
extern float rndF();


/**
 * return random 8bit value with max
 */
extern uint8_t rnd(const uint8_t &max);

/**
 * Returns a 16bit value out of 2 rnd8 values
 */
extern uint16_t rnd16_8();

namespace Random
{
    extern PROGMEM const uint8_t shift16[];
    extern uint8_t cur_shift16;
    extern uint16_t y16;
    extern uint16_t request_count16;
}

/**
 * return random 16bit value
 */
extern uint16_t rnd16();

/**
 * return random 16bit value with max
 */
extern uint16_t rnd16(const uint16_t &max);

/**
 * Returns a uint8_t but calculates by a 16bit rnd
 */
extern uint8_t rnd8_16();
#endif