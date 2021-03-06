/*
* Microphone.cpp
*
* Created: 12.04.2015 17:11:11
* Author: Benjamin
*/


#include "Microphone.h"
#define F_CPU 22118400
// default constructor
Microphone::Microphone()
{
} //Microphone

// default destructor
Microphone::~Microphone()
{
} //~Microphone

void Microphone::init()
{
    ADMUX |= (1 << REFS0); //select AVcc as reference
    //select chanel7 ADC7
    ADMUX |= (1 << MUX0) | (1 << MUX1) | (1 << MUX2);

    //should be between 50 and 200khz
    // 22118400/200 = ~110 so 128 is fine
    //setup prescaler of 128 => ~200khz
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) ;
    ADCSRB &= ~((1 << ADTS0) | (1 << ADTS1) | (1 << ADTS2));

//Disable the digital input
    DIDR0 |= (1 << ADC7D); // on pin 7
//enable ADC
    ADCSRA |= (1 << ADEN);
//start one convention which is needed for autotrigger
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC)) ;

    ADCSRA |= (1 << ADATE); //enable auto trigger
    ADCSRA |= (1 << ADSC);
}

int16_t Microphone::sample()
{
    //wait till next is done
    while(!(ADCSRA & (1 << ADIF)))
    {
    } //wait till interrupt flag is set
    ADCSRA = ADCSRA; //reset interupt flag
    return ADCW; // return the current value
}