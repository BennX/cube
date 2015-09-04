#pragma once
#include "Animation.h"
#include "../Cube.h"
#include "../Util/Random.h"
#include "../Menu/MenuEntry.h"
#include "../Util/PStrings.h"
#include "../Menu/Submenu.h"

//the maximum of active raindrops
#define MAX_RAINDROPS 30
#define SPAWN_RATE 20 //its percent so 20% chance to spawn a not active raindrop
#define UPDATE_TIME_RAINDROP 110 //in ms
#define RAINDROP_SPEED_MULTIPL 10
class RainAnimation : public Animation, public MenuEntry
{
private:
    struct RainDrop
    {
        uint8_t x, y, z, r, b, g;
        bool active;
    };

    Cube &cube;
    uint16_t time_taken;
    RainDrop raindrops[MAX_RAINDROPS];
    int8_t m_raindropCount;
    int16_t m_raindropSpeed;
    int8_t m_spawnrate;
    //menu stuff
    Submenu m_submenu;
public:
    RainAnimation(Cube &c, const uint8_t &id);
    void update(const uint16_t &delta);
    //menu stuff
    void updateEntry(const uint16_t &delta, Input &i,
                     Menu &m);
    PGM_P name()
    {
        return PSTR("Rain");
    };
    bool subMenu();
};

RainAnimation::RainAnimation(Cube &c, const uint8_t &id) : Animation(id),
    cube(c), time_taken(0), m_raindropCount(MAX_RAINDROPS),
    m_raindropSpeed(UPDATE_TIME_RAINDROP),
    m_spawnrate(SPAWN_RATE), m_submenu(PSTR("Rain Animation"), id)
{
    for (int i = 0; i < MAX_RAINDROPS; i++)
    {
        raindrops[i].active = false;
    }
    m_submenu.addEntry(p_strings::tropfen, &m_raindropCount, 0, MAX_RAINDROPS, 1);
    m_submenu.addEntry(p_strings::speed, &m_raindropSpeed, 0, 2000,
                       RAINDROP_SPEED_MULTIPL);
    m_submenu.addEntry(p_strings::rate, &m_spawnrate, 0, 100, 1);
}

void RainAnimation::update(const uint16_t &delta)
{
    time_taken += delta;
    if(time_taken > m_raindropSpeed)
    {
        time_taken = 0;
        for (uint8_t i = 0; i < m_raindropCount; i++)
        {
            if (raindrops[i].active)
            {
                if (raindrops[i].y > 0 && raindrops[i].active)
                {
                    //reset old spot
                    cube.setRGB(raindrops[i].x, raindrops[i].y, raindrops[i].z, 0, 0, 0);
                    //update to new spot
                    raindrops[i].y--;
                    cube.setRGB(raindrops[i].x, raindrops[i].y, raindrops[i].z, raindrops[i].r,
                                 raindrops[i].g, raindrops[i].b);
                }
                else if (raindrops[i].y == 0 && raindrops[i].active)
                {
                    //if position is on the bottom shut the led down
                    raindrops[i].active = false;
                    cube.setRGB(raindrops[i].x, raindrops[i].y, raindrops[i].z, 0, 0, 0);
                }
            }
            else
            {
                //if not active generate a new spot to start;
                if (rnd(100) < m_spawnrate)
                {
                    raindrops[i].x = rnd(5);
                    raindrops[i].y = 4;
                    raindrops[i].z = rnd(5);
                    raindrops[i].r = rnd(MAX_COLOR);
                    raindrops[i].g = rnd(MAX_COLOR);
                    raindrops[i].b = rnd(MAX_COLOR);
                    raindrops[i].active = true;
                    //dont forget to set the led ;)
                    cube.setRGB(raindrops[i].x, raindrops[i].y, raindrops[i].z, raindrops[i].r,
                                 raindrops[i].g, raindrops[i].b);
                }
            }
        }
    }
}

void RainAnimation::updateEntry(const uint16_t &delta, Input &i, Menu &m)
{
    m_submenu.update(time_taken, i, m);
};

bool RainAnimation::subMenu()
{
    return true;
};