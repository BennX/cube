/*
* Input.h
*
* Created: 15.03.2015 19:18:34
* Author: Benjamin
*/


#ifndef __INPUT_H__
#define __INPUT_H__

#include <avr/io.h>

class Input
{
private:
//current difference of the incremental
    volatile int8_t enc_delta;
    int8_t last;

    static volatile uint8_t *INC_PIN;
    static volatile uint8_t *INC_DDR;
    static volatile uint8_t *INC_PORT;
    static const uint8_t INC_PHASE1_PIN;
    static const uint8_t INC_PHASE2_PIN;
    static const uint8_t INC_TASER_PIN;

    static volatile uint8_t *BUTTON_PIN;
    static volatile uint8_t *BUTTON_DDR;
    static volatile uint8_t *BUTTON_PORT;
    static const uint8_t BUTTON0;
    static const uint8_t BUTTON1;
    static const uint8_t BUTTON2;
    static const uint8_t BUTTON3;

//functions
public:
    Input();
    ~Input();

    void update();
    bool isPressed(const uint8_t &i);
    bool isPressed();
    int8_t getIncDelta();

private:
    //no copy no assignement
    Input( const Input &c ) = delete;
    Input &operator=( const Input &c ) = delete;

}; //Input

#endif //__INPUT_H__
