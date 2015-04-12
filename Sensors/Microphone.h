/*
* Microphone.h
*
* Created: 12.04.2015 17:11:11
* Author: Benjamin
*/


#ifndef __MICROPHONE_H__
#define __MICROPHONE_H__
#include <avr/io.h>

class Microphone
{
public:
    Microphone();
    ~Microphone();

    /**
     * init the adc
     */
    static void init();

    /**
     * returns one sample
     */
    static int16_t sample();
private:
    Microphone( const Microphone &c );
    Microphone &operator=( const Microphone &c );
}; //Microphone

#endif //__MICROPHONE_H__
