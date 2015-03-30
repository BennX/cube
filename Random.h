/*
* Random.h
* Simple 8bit random number generator. Using shifting
* to have a longer Period shift the shiftvalues
* http://www.arklyffe.com/main/2010/08/29/xorshift-pseudorandom-number-generator/
* Created: 24.02.2015 11:57:51
* Author: Benjamin
*/
#ifndef Random
#define Random
#include "stdlib.h"
#include <avr/pgmspace.h>

//struct shift_number
//{
//uint8_t n1, n2, n3;
//};

//throw this in progmem?!
//static shift_number shifter[24] =
//{
//{1, 1, 2}, 	{1, 1, 3},	{1, 7, 3},	{1, 7, 6},	{1, 7, 7},	{2, 1, 1},
//{2, 5, 5}, 	{3, 1, 1},	{3, 1, 5},	{3, 5, 4},	{3, 5, 5},	{3, 5, 7},
//{3, 7, 1},	{4, 5, 3},	{5, 1, 3},	{5, 3, 6},	{5, 3, 7},	{5, 5, 2},
//{5, 5, 3},	{6, 3, 5}, 	{6, 7, 1},	{7, 3, 5},	{7, 5, 3},	{7, 7, 1}
//};

const uint8_t shift[] PROGMEM =
{
    0x01, 0x01, 0x02, 	0x01, 0x01, 0x03,	0x01, 0x07, 0x03,	0x01, 0x07, 0x06,	0x01, 0x07, 0x07,	0x02, 0x01, 0x01,
    0x02, 0x05, 0x05, 	0x03, 0x01, 0x01,	0x03, 0x01, 0x05,	0x03, 0x05, 0x04,	0x03, 0x05, 0x05,	0x03, 0x05, 0x07,
    0x03, 0x07, 0x01,	0x04, 0x05, 0x03,	0x05, 0x01, 0x03,	0x05, 0x03, 0x06,	0x05, 0x03, 0x07,	0x05, 0x05, 0x02,
    0x05, 0x05, 0x03,	0x06, 0x03, 0x05, 	0x06, 0x07, 0x01,	0x07, 0x03, 0x05,	0x07, 0x05, 0x03,	0x07, 0x07, 0x01
};

static uint8_t y8 = 13;
static uint8_t cur_shift = 0, request_count = 0;

uint8_t rnd()
{
    //shift the shifting numbers
    request_count++;
    if(request_count == 255)
    {
        request_count = 0;
        cur_shift++;
        if (cur_shift == 24)
        {
            cur_shift = 0;
        }
    }
    //shift something around 3 cycles per pgm_read_byte
    y8 ^= (y8 << pgm_read_byte(&(shift[cur_shift * 3])));
    y8 ^= (y8 >> pgm_read_byte(&(shift[(cur_shift * 3 + 1)])));
    return y8 ^= (y8 << pgm_read_byte(&(shift[(cur_shift * 3 + 2)])));
}

//uint8_t rnd()
//{
////shift the shifting numbers
//request_count++;
//if(request_count == 255)
//{
//request_count = 0;
//cur_shift++;
//if (cur_shift == 24)
//{
//cur_shift = 0;
//}
//}
////shift something around
//y8 ^= (y8 << shifter[cur_shift].n1);
//y8 ^= (y8 >> shifter[cur_shift].n2);
//return y8 ^= shifter[cur_shift].n3;
//}

uint8_t rnd(const uint8_t &max)
{
    return rnd() % max;
}
#endif