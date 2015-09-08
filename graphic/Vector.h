/*
* Vector.h
*
* Created: 06.09.2015 11:05:41
* Author: Benjamin
*/


#ifndef __VECTOR_H__
#define __VECTOR_H__
class Vector
{
public:
    float x, y, z;

    Vector();
    Vector(const Vector& c);   //copy ctor
    inline Vector& operator=(const Vector& c);
    Vector(const float& x, const float& y, const float& z);

    ~Vector();

    inline Vector& nor();
    inline Vector cross(const Vector& other) const;
    inline float dot(const Vector& other) const;
    inline float norm() const;

    //calculates the distance to the other
    inline float dist(const Vector& other) const;

    inline Vector& rnd();
    inline Vector& rnd(const float& f);

    inline Vector& operator+=(const Vector& other);
    inline Vector operator+(const Vector& other) const;

    inline Vector& operator-=(const Vector& other);
    inline Vector operator-(const Vector& other) const;

    inline Vector& operator*=(const float& f);
    inline Vector operator*(const float& other) const;
}; //Vector

//include the inlines
#include "Vector.hpp"
#endif //__VECTOR_H__
