#ifndef VECTOR_H
#define VECTOR_H

#include "actor.h"

class vector
{
public:
    vector();
    vector(float x, float y, float z);
    vector(const Actor &a);
    vector(const Actor *a);
    vector(int x, int y, int z);
    vector(const vector &v);
    void operator =(const vector &v);
    float dotProduct(const vector &v) const;
    vector operator +(const vector &v) const;
    vector operator -(const vector &v) const;
    bool operator ==(const vector &v) const;
    vector operator *(float a) const;
    vector operator *(int a) const;
    vector operator *(const vector &v) const;
    float norm() const;
    float getX() const;
    float getY() const;
    float getZ() const;

private:
    float x,y,z;
};

#endif // VECTOR_H
