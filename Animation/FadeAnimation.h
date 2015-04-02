#pragma once

#include "Animation.h"
#include "../Cube.h"
#include "../Util/Random.h"
#define COLOR_STAY_TIME 5000
#define FADE_DELAY 250
class FadeAnimation : public Animation
{
private:
    Cube *cube;
    uint8_t counter, r, g, b;
    short timer;
public:
    FadeAnimation(Cube *c): cube(c), counter(0), r(rnd()), g(rnd()),
        b(rnd()), timer(0) {};
    ~FadeAnimation() {};
    void update(const uint16_t &delta);
};

void FadeAnimation::update(const uint16_t &delta)
{
    if(counter <= MAX_COLOR)
        counter++;
    if(counter > MAX_COLOR)
    {
        timer += delta;
        if(timer > COLOR_STAY_TIME)
        {
            r = rnd(MAX_COLOR);
            g = rnd(MAX_COLOR);
            b = rnd(MAX_COLOR);
            counter = 0;
            timer = 0;
        }
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