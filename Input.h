/*
* Input.h
*
* Created: 15.03.2015 19:18:34
* Author: Benjamin
*/


#ifndef __INPUT_H__
#define __INPUT_H__

#include <avr/io.h>

#define INC_PIN PINB
#define INC_DDR DDRB
#define INC_PORT PORTB
#define INC_PHASE1_PIN PINB0
#define INC_PHASE2_PIN PINB1
#define INC_TASER_PIN PINB2

#define PHASE1 !(INC_PIN & (1<<INC_PHASE2_PIN))
#define PHASE2 !(INC_PIN & (1<<INC_PHASE1_PIN))

#define BUTTON_PIN PINC
#define BUTTON_DDR DDRC
#define BUTTON_PORT PORTC
#define BUTTON0 PINC2
#define BUTTON1 PINC3
#define BUTTON2 PINC4
#define BUTTON3 PINC5

class Input
{
//variables
public:
protected:
private:
//current difference of the incremental
    volatile int8_t enc_delta;
    int8_t last;

//functions
public:
    Input();
    ~Input();

    void update();
    bool isPressed(const uint8_t &i);
    bool isPressed();
    int8_t getIncDelta();

protected:
private:
    //no copy no assignement
    Input( const Input &c ) = delete;
    Input &operator=( const Input &c ) = delete;

}; //Input

#endif //__INPUT_H__
