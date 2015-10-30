/*
* Cube.h
*
* Created: 16.12.2014 11:44:05
* Author: Benjamin
*/


#ifndef __CUBE_H__
#define __CUBE_H__

#include <avr/io.h>
#include "RGB.h"
#include "CubeProxy.h"
#include "SPI.h"
#include "graphic/Vector.h"

#define MAX_COLOR 31

class Cube
{
protected:
    uint8_t m_colors[5][MAX_COLOR][10];
    RGB m_cur_colors[5][5][5];
    //for SPI!
    uint8_t level;
    uint8_t cur_color_counter;
    //functions
public:

    static Cube& getInstance()
    {
        return m_instance;
    }

    RGB setRGB(uint8_t x, uint8_t y, uint8_t z,
               uint8_t r, uint8_t g, uint8_t b);

    RGB setRGB(uint8_t x, uint8_t y, uint8_t z,
               const RGB& color);

    RGB setRGB(const Vector& v, const RGB& rgb);
    RGB getRGB(uint8_t x, uint8_t y, uint8_t z);
    void off();
    inline void render();

    cube::CubeProxy& operator()(uint8_t x, uint8_t y, uint8_t z);
private:
	cube::CubeProxy m_proxy;
    Cube();
    //no copy!
    Cube( const Cube& c ) = delete;
    Cube& operator=( const Cube& c ) = delete;

    static Cube m_instance;

//static definitions for the cube object
    static volatile uint8_t* m_to_storage_port;
    static volatile uint8_t* m_to_storage_ddr;
    static const uint8_t m_to_storage_pin_no;

    static volatile uint8_t* m_disable_port;
    static volatile uint8_t* m_disable_ddr;
    static const uint8_t m_disable_pin_no;
}; //Cube

void Cube::render()
{
    // DISABLE_LINE_PORT |= (1 << DISABLE_LINE_PIN); //set high to disable the register
    //*m_disable_port |= (1 << m_disable_pin_no);
    //reverse shift out
    for(int8_t i = 9; i >= 0; i--)
    {
        SPI::transmit(m_colors[level][cur_color_counter][i]);
    }

    cur_color_counter++;
    if(cur_color_counter >= MAX_COLOR)
    {
        cur_color_counter = 0;
        level++;
        if(level > 4)
        {
            level = 0;
        }
    }

    *m_to_storage_port |= (1 << m_to_storage_pin_no); //1 clock to storage
    *m_to_storage_port &= ~(1 << m_to_storage_pin_no); //1 clock to storage

    //*m_disable_port &= ~(1 << m_disable_pin_no); //set low to enable the register
}

#endif //__CUBE_H__