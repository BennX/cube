/*
 * settings.h
 *
 * Created: 18.04.2015 18:53:17
 *  Author: Benjamin
 */
#include <avr/io.h>

//RGB
const uint8_t RGB::MAX_COLOR_RGB = 30;

//GUID generator
uint8_t GUID::current_id = 0;

//TEMPERATUR
const volatile uint8_t Temperatur::m_port = PORTC;

//Cube definitions. Use ptr for the port etc. else get a cpy.....
volatile uint8_t *Cube::m_to_storage_port = &PORTC;
volatile uint8_t *Cube::m_to_storage_ddr = &DDRC;
const uint8_t Cube::m_to_storage_pin_no = DDC6;

volatile uint8_t *Cube::m_disable_port = &PORTC;
volatile uint8_t *Cube::m_disable_ddr = &DDRC;
const uint8_t Cube::m_disable_pin_no = DDC7;

//ball animation
const float Ball::START_UPDATE_TIME = 500.0f;
const float Ball::MAX_SIZE = 4.5f;
const float Ball::MIN_UPDATE_TIME = 50.0f;
const float Ball::UPDATE_TIME_CHANGE = 25.0f;

//input def
volatile uint8_t *Input::INC_PIN = &PINB;
volatile uint8_t *Input::INC_DDR = &DDRB;
volatile uint8_t *Input::INC_PORT = &PORTB;
const uint8_t Input::INC_PHASE1_PIN = PINB0;
const uint8_t Input::INC_PHASE2_PIN = PINB1;
const uint8_t Input::INC_TASER_PIN = PINB2;

volatile uint8_t *Input::BUTTON_PIN = &PINC;
volatile uint8_t *Input::BUTTON_DDR = &DDRC;
volatile uint8_t *Input::BUTTON_PORT = &PORTC;
const uint8_t Input::BUTTON0 = PINC2;
const uint8_t Input::BUTTON1 = PINC3;
const uint8_t Input::BUTTON2 = PINC4;
const uint8_t Input::BUTTON3 = PINC5;

const uint16_t Input::INC_CLICK_DELAY = 500;

//Wall animation
const uint16_t Wall::START_UPDATE_TIME = 100;
const uint8_t Wall::START_PROBABILITY = 70;

//DISPLAY 
short Display::m_offtime = 5000; //after 5 seconds
short Display::m_fadeInTime = 2000; // half second