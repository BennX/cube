#pragma once

#include "Animation.h"
#include "../Cube.h"
#include "../Util/Random.h"
#include "../Menu/MenuEntry.h"
#include "../Util/PStrings.h"
#include <avr/io.h>
#define COLOR_STAY_TIME 5000
#define FADE_DELAY 250
#define SPEED_CHANGE_SPEED 500
#define CLICK_DELAY_FADE 1000
class FadeAnimation : public Animation, public MenuEntry
{
private:
    Cube& cube;
    uint8_t counter, r, g, b;
    int8_t m_curMenuPos;
    uint16_t timer, m_speed, m_clickdelay;
    bool m_speedSelected, m_menuChanged, m_clicked;
public:
    FadeAnimation(Cube& c, const uint8_t& id): Animation(id), cube(c), counter(0),
        r(rnd()), g(rnd()),
        b(rnd()), timer(0), m_curMenuPos(0), m_speed(COLOR_STAY_TIME),
        m_speedSelected(false), m_menuChanged(true), m_clickdelay(0),
        m_clicked(true) {};
    ~FadeAnimation() {};

    //animation
    void update(const uint16_t& delta);
    //menu entry
    void updateEntry(const uint16_t& delta, Input& i, Menu& m);
    PGM_P name()
    {
        return PSTR("Fade");
    };
    bool subMenu();
};

void FadeAnimation::update(const uint16_t& delta)
{
    if(counter <= MAX_COLOR)
        counter++;
    if(counter > MAX_COLOR)
    {
        timer += delta;
        if(timer > m_speed)
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
                RGB col = cube.getRGB(x, y, z);
                uint8_t curR = col.r;
                uint8_t curG = col.g;
                uint8_t curB = col.b;

                if (curR < r)
                {
                    cube.setRGB(x, y, z, curR + 1, curG, curB);
                }
                if (curR > r)
                {
                    cube.setRGB(x, y, z, curR - 1, curG, curB);
                }
                if (curG < g)
                {
                    cube.setRGB(x, y, z, curR, curG + 1, curB);
                }
                if (curG > g)
                {
                    cube.setRGB(x, y, z, curR, curG - 1, curB);
                }
                if (curB < b)
                {
                    cube.setRGB(x, y, z, curR, curG, curB + 1);
                }
                if (curB > b)
                {
                    cube.setRGB(x, y, z, curR, curG, curB - 1);
                }
            }
        }
    }
    //_delay_ms(50);
}

void FadeAnimation::updateEntry(const uint16_t& delta, Input& i,
                                Menu& m)
{
    if(m_menuChanged)
    {
        Display::clear();
        Display::out_p(0, 0) << PSTR("Fade Animation");
        Display::out_p(1, 1) << p_strings::speed;
        Display::out << (float)(m_speed / 1000.0);
        Display::out_p << PSTR("s");
        Display::out_p(2, 1) << p_strings::start;
        Display::out_p(1 + m_curMenuPos, 0)  << p_strings::right_arrow;
        m_menuChanged = false;
    }

    bool click = i.clicked();
    if(click && m_curMenuPos == 0)
    {
        m_speedSelected = !m_speedSelected;
        m_clicked = true;
    }
    else if (click && m_curMenuPos == 1)
    {
        m.start(m_ID);
        m.leaveSubmenu();
        m_menuChanged = true;
        m_clicked = true;
    }

    int8_t enc = i.getIncDelta();
    if(enc != 0 && m_speedSelected)
    {
        m_speed += enc * SPEED_CHANGE_SPEED;
        if(m_speed < 0)
            m_speed = 0;
        m_menuChanged = true;
    }

    else if(enc != 0)
    {
        m_curMenuPos += enc;
        if(m_curMenuPos < 0)
        {
            m_curMenuPos = 0;
        }
        else if(m_curMenuPos > 1)
        {
            m_curMenuPos = 1;
        }
        m_menuChanged = true;
    }
}

bool FadeAnimation::subMenu()
{
    return true;
}