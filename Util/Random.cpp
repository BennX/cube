/*
 * Random.cpp
 *
 * Created: 30.03.2015 19:39:42
 *  Author: Benjamin
 */
#include "Random.h"

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

uint8_t rnd(const uint8_t &max)
{
    return rnd() % max;
}