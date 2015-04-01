#pragma once

#include "Animation.h"
#include "../Cube.h"
#include "../Util/Random.h"
#define UPDATE_TIME 0
class FadeAnimation : public Animation
{
private:
    Cube *cube;
    uint8_t counter, r, g, b;
    short timer;
public:
    FadeAnimation(Cube *c): cube(c), counter(0), r(rnd()), g(rnd()), b(rnd()),
        timer(0) {};
    ~FadeAnimation() {};
    void update(const uint16_t &delta);
};

void FadeAnimation::update(const uint16_t &delta)
{
    timer += delta;
    if(timer > UPDATE_TIME)
    {
        timer = 0;
        counter++;
        if(counter > MAX_COLOR)
        {
            r = rnd() % 30;
            g = rnd() % 30;
            b = rnd() % 30;
            counter = 0;
        }
        //do it max depth steps than everything should be done
        for (int z = 0; z < 5; z++)
        {
            for (int x = 0; x < 5; x++)
            {
                for (int y = 0; y < 5; y++)
                {
                    //speed it up
                    uint8_t curR = cube->getR(x, y, z);
                    uint8_t curG = cube->getG(x, y, z);
                    uint8_t curB = cube->getB(x, y, z);

                    if (curR < r)
                    {
                        cube->setRGB(x, y, z, curR + 1, curG, curB);
                    }
                    if (curR > r)
                    {
                        cube->setRGB(x, y, z, curR - 1, curG, curB);
                    }
                    if (curG < g)
                    {
                        cube->setRGB(x, y, z, curR, curG + 1, curB);
                    }
                    if (curG > g)
                    {
                        cube->setRGB(x, y, z, curR, curG - 1, curB);
                    }
                    if (curB < b)
                    {
                        cube->setRGB(x, y, z, curR, curG, curB + 1);
                    }
                    if (curB > b)
                    {
                        cube->setRGB(x, y, z, curR, curG, curB - 1);
                    }
                }
            }
        }
        //_delay_ms(50);
    }
}


