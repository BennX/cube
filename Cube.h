/*
* Cube.h
*
* Created: 16.12.2014 11:44:05
* Author: Benjamin
*/


#ifndef __CUBE_H__
#define __CUBE_H__

#include <avr/io.h>
#include "SPI.h"

#define MAX_COLOR 30

struct RGB
{
    uint8_t r, g, b;
};

class Cube
{
protected:

    uint8_t colors[5][MAX_COLOR][10];
    RGB cur_colors[5][5][5];
    //for SPI!
    uint8_t level;
    uint8_t cur_color_counter;
    //functions
public:
    Cube();
    ~Cube();
    inline RGB setRGB(const uint8_t &x, const uint8_t &y, const uint8_t &z,
                      const uint8_t &r, const uint8_t &g, const uint8_t &b);
    inline RGB setRGB(const uint8_t &x, const uint8_t &y, const uint8_t &z,
                      const RGB &color);
    inline uint8_t getR(const uint8_t &x, const uint8_t &y, const uint8_t &z);
    inline uint8_t getG(const uint8_t &x, const uint8_t &y, const uint8_t &z);
    inline uint8_t getB(const uint8_t &x, const uint8_t &y, const uint8_t &z);
    inline RGB getRGB(const uint8_t &x, const uint8_t &y, const uint8_t &z);
    void off();
    inline void render();

private:
    //no copy!
    Cube( const Cube &c ) = delete;
    Cube &operator=( const Cube &c ) = delete;

//static definitions for the cube object
    static volatile uint8_t *m_to_storage_port;
    static volatile uint8_t *m_to_storage_ddr;
    static const uint8_t m_to_storage_pin_no;

    static volatile uint8_t *m_disable_port;
    static volatile uint8_t *m_disable_ddr;
    static const uint8_t m_disable_pin_no;
}; //Cube

void Cube::render()
{
    // DISABLE_LINE_PORT |= (1 << DISABLE_LINE_PIN); //set high to disable the register
    *m_disable_port |= (1 << m_disable_pin_no);
    //reverse shift out
    for(int8_t i = 9; i >= 0; i--)
    {
        SPI::transmit(colors[level][cur_color_counter][i]);
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

    *m_disable_port &= ~(1 << m_disable_pin_no); //set low to enable the register
}

RGB Cube::setRGB(const uint8_t &x, const uint8_t &y, const uint8_t &z,
                 const RGB &color)
{
    return setRGB(x, y, z, color.r, color.g, color.b);
}

/************************************************************************/
/* Take care it has no bounds checking!                                 */
/************************************************************************/
RGB Cube::setRGB(const uint8_t &x, const uint8_t &y, const uint8_t &z,
                 const uint8_t &r, const uint8_t &g, const uint8_t &b)
{
    RGB ret = cur_colors[x][y][z];//save old value to return
    //change value to new one
    cur_colors[x][y][z].r = r;
    cur_colors[x][y][z].g = g;
    cur_colors[x][y][z].b = b;

    //update colors
    uint8_t pos = x * 3 + z * 15 + 5;
    //+0
    uint8_t rbyte = pos / 8;
    uint8_t rbit = pos % 8;
    //+1
    uint8_t gbyte = (pos + 1) / 8;
    uint8_t gbit = (pos + 1) % 8;
    //+2
    uint8_t bbyte = (pos + 2) / 8;
    uint8_t bbit = (pos + 2) % 8;

    for(uint8_t i = 0; i < MAX_COLOR; i++)
    {
        if(i < r)
        {
            colors[y][i][rbyte] |= 1 << rbit; //set all to 1 till r
        }
        else
        {
            //bitwise not = ~ ! (invert with &)
            colors[y][i][rbyte] &= ~(1 << rbit);//set all other to 0
        }
        if(i < g)
        {
            colors[y][i][gbyte] |= 1 << gbit; //set all to 1 till r
        }
        else
        {
            colors[y][i][gbyte] &= ~(1 << gbit);//set all other to 0
        }
        if(i < b)
        {
            colors[y][i][bbyte] |= 1 << bbit; //set all to 1 till r
        }
        else
        {
            colors[y][i][bbyte] &= ~(1 << bbit);//set all other to 0
        }
    }
    return ret;
}

uint8_t Cube::getR(const uint8_t &x, const uint8_t &y, const uint8_t &z)
{
    return cur_colors[x][y][z].r;
}

uint8_t  Cube::getG(const uint8_t &x, const uint8_t &y, const uint8_t &z)
{
    return cur_colors[x][y][z].g;
}

uint8_t  Cube::getB(const uint8_t &x, const uint8_t &y, const uint8_t &z)
{
    return cur_colors[x][y][z].b;
}

RGB  Cube::getRGB(const uint8_t &x, const uint8_t &y, const uint8_t &z)
{
    return cur_colors[x][y][z];
}

#endif //__CUBE_H__