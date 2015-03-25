/*
* USART.h
* Simple Static USART
* Created: 26.01.2015 11:39:13
* Author: Benjamin
*/

#ifndef __USART_H__
#define __USART_H__
#include<avr/io.h>
//#include<interrupt.h>
//defines for the setbaud util if not in compiler
#define F_CPU 22118400

#ifndef BAUD
#define BAUD 115200
#endif
//calculates the UBRRH and UBRRL
#include<util/setbaud.h>

class USART
{
    //functions
public:
    ~USART() {};

    static inline void init();
    static inline void transmit_c(const unsigned char &data);
    static inline void transmit_s(const char *data);
    /**
    Blockend!
    */
    static inline unsigned char receive();
    //TODO using interrupt
    //static inline bool available();

private:
    USART() {};
    USART( const USART &c );
    USART &operator=( const USART &c );
}; //USART

inline void USART::init()
{
    //values from the util/setbaud
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X //from the setbaud.h
    //double the transmission speed if needed. util decides!
    UCSR0A |= (1 << U2X0)
#else
    UCSR0A &= ~(1 << U2X0);
#endif;

    // Enable receiver and transmitter //für empfangsinterupt fehlt noch (1<< RXCIE0)
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C |= (1 << USBS0) | (3 << UCSZ00); // 011 << UCSZ00
}

inline void USART::transmit_c(const unsigned char &data)
{
    //wait till empty
    while(!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
    return;
}

inline void USART::transmit_s(const char *data)
{
    while(*data)
    {
        transmit_c(*data);
        data++;
    }
}


inline unsigned char USART::receive()
{
    while(!(UCSR0A & (1 << RXC0)))
        ;
    return UDR0;
}
/*
ISR(USART0_RX_vect)
{
    //got a new char
};
*/

#endif //__USART_H__
