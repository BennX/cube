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
public:
    static Input& getInstance()
    {
        return m_instance;
    }

    void update();

    /**
     * Returns true if the button i is "active"
     */
    bool isPressed(const uint8_t &i);

    /**
     * Retruns true if the inc is "active"
     */
    bool isPressed();

    /**
     * This method returns true if the state of the
     * incremental changed to  0 1 0.
     * if this method is called the timer starts
     * which disallows to "click" again.
     * Dont forget that it reset the click! so calling it
     * several times to check if clicked is really useless!
     */
    bool clicked();

    /**
     * Returns the delta of the inc
     * also reset the delta to "0"
     */
    int8_t getIncDelta();
private:
    static Input m_instance;

    Input();
    ~Input();
    //no copy no assignement
    Input( const Input &c ) = delete;
    Input &operator=( const Input &c ) = delete;
//current difference of the incremental
    volatile int8_t m_enc_delta;
    int8_t m_last;
    bool m_inc_last;
    bool m_inc_clicked;
    uint16_t m_inc_click_timer;

    //configurations
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

    static const uint16_t INC_CLICK_DELAY;
}; //Input

#endif //__INPUT_H__
