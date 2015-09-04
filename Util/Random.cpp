/*
 * Random.cpp
 *
 * Created: 30.03.2015 19:39:42
 *  Author: Benjamin
 */
#include "Random.h"

using namespace Random;
namespace Random
{
    uint8_t y8 = 13;
    uint8_t cur_shift = 0;
    uint8_t request_count = 0;

    const uint8_t shift[] =
    {
        0x01, 0x01, 0x02, 	0x01, 0x01, 0x03,	0x01, 0x07, 0x03,	0x01, 0x07, 0x06,	0x01, 0x07, 0x07,	0x02, 0x01, 0x01,
        0x02, 0x05, 0x05, 	0x03, 0x01, 0x01,	0x03, 0x01, 0x05,	0x03, 0x05, 0x04,	0x03, 0x05, 0x05,	0x03, 0x05, 0x07,
        0x03, 0x07, 0x01,	0x04, 0x05, 0x03,	0x05, 0x01, 0x03,	0x05, 0x03, 0x06,	0x05, 0x03, 0x07,	0x05, 0x05, 0x02,
        0x05, 0x05, 0x03,	0x06, 0x03, 0x05, 	0x06, 0x07, 0x01,	0x07, 0x03, 0x05,	0x07, 0x05, 0x03,	0x07, 0x07, 0x01
    };
}
uint8_t rnd()
{
    //shift the shifting numbers
    request_count++;
    if(request_count == 255)
    {
        request_count = 0;
        cur_shift = rnd16(24); //generate next random with rand 16
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

uint16_t rnd16_8()
{
    uint16_t ret;
    ret = (rnd() << 8) | rnd();
    return ret;
}
namespace Random
{
    uint16_t y16 = 1;
    uint16_t request_count16 = 0;
    uint8_t cur_shift16 = 0;
    const uint8_t shift16[] =
    {
        0x01, 0x01, 0x14, //1 1 14
        0x09, 0x07, 0x0D, // 9 7 13
        0x0F, 0x07, 0x02  // 15 7 2
    };
}
uint16_t rnd16()
{
    if(request_count16 == 65535)
    {
        request_count16 = 0;
        cur_shift16++;
        if(cur_shift16 > 2)
        {
            cur_shift16 = 0;
        }
    }
    y16 ^= (y16 << pgm_read_byte(&(shift16[cur_shift16])));
    y16 ^= (y16 >> pgm_read_byte(&(shift16[cur_shift16 + 1])));
    return y16 ^= (y16 << pgm_read_byte(&(shift16[cur_shift16 + 2])));
}

uint16_t rnd16(const uint16_t &max)
{
    return rnd16() % max;
}

uint8_t rnd8_16()
{
    return (uint8_t)rnd16() % 255;
}
