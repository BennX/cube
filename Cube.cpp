/*
* Cube.cpp
*
* Created: 16.12.2014 11:44:05
* Author: Benjamin
*/

#include "Cube.h"
#include <string.h>

Cube Cube::m_instance;

// default constructor
Cube::Cube(): level(0), cur_color_counter(0)
{
    SPI::init();//init the spi
    off();
    //set all 0 with a string function
    //memset(cur_colors, 0, 5*5*5*sizeof(RGB));

    //enabel output on ss and latch pins
    *m_to_storage_ddr |= (1 << m_to_storage_pin_no);
    *m_disable_ddr |= (1 << m_disable_pin_no);
} //Cube

// default destructor
Cube::~Cube()
{
} //~Cube

void Cube::off()
{
    memset(m_colors, 0, sizeof(m_colors));
    for(uint8_t i = 0; i < MAX_COLOR; i++)
    {
        //maxbe reverse
        m_colors[0][i][0] = 0x04;//
        m_colors[1][i][0] = 0x03;//
        m_colors[2][i][0] = 0x02;//
        m_colors[3][i][0] = 0x01;//
        m_colors[4][i][0] = 0x00;//
    }
}

RGB Cube::setRGB(const uint8_t& x, const uint8_t& y, const uint8_t& z,
                 const RGB& color)
{
    return setRGB(x, y, z, color.r, color.g, color.b);
}

/************************************************************************/
/* Take care it has no bounds checking!                                 */
/************************************************************************/
RGB Cube::setRGB(const uint8_t& x, const uint8_t& y, const uint8_t& z,
                 const uint8_t& r, const uint8_t& g, const uint8_t& b)
{
    RGB ret = m_cur_colors[x][y][z];//save old value to return
    //change value to new one
    m_cur_colors[x][y][z].r = r;
    m_cur_colors[x][y][z].g = g;
    m_cur_colors[x][y][z].b = b;

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
            m_colors[y][i][rbyte] |= 1 << rbit; //set all to 1 till r
        }
        else
        {
            //bitwise not = ~ ! (invert with &)
            m_colors[y][i][rbyte] &= ~(1 << rbit);//set all other to 0
        }
        if(i < g)
        {
            m_colors[y][i][gbyte] |= 1 << gbit; //set all to 1 till r
        }
        else
        {
            m_colors[y][i][gbyte] &= ~(1 << gbit);//set all other to 0
        }
        if(i < b)
        {
            m_colors[y][i][bbyte] |= 1 << bbit; //set all to 1 till r
        }
        else
        {
            m_colors[y][i][bbyte] &= ~(1 << bbit);//set all other to 0
        }
    }
    return ret;
}

RGB Cube::setRGB(const Vector& v, const RGB& rgb)
{
    return setRGB(v.x, v.y, v.z, rgb);
}

uint8_t Cube::getR(const uint8_t& x, const uint8_t& y, const uint8_t& z)
{
    return m_cur_colors[x][y][z].r;
}

uint8_t Cube::getG(const uint8_t& x, const uint8_t& y, const uint8_t& z)
{
    return m_cur_colors[x][y][z].g;
}

uint8_t  Cube::getB(const uint8_t& x, const uint8_t& y, const uint8_t& z)
{
    return m_cur_colors[x][y][z].b;
}

RGB  Cube::getRGB(const uint8_t& x, const uint8_t& y, const uint8_t& z)
{
    return m_cur_colors[x][y][z];
}