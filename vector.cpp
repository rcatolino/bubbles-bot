#include "vector.h"
#include "actor.h"
#include <QtCore/qmath.h>

vector::vector() : x(0), y(0), z(0)
{
}
vector::vector(float x, float y, float z) : x(x), y(y), z(z)
{
}
vector::vector(int x, int y, int z): x(x), y(y), z(z)
{
}
vector::vector(const vector &v): x(v.getX()),y(v.getY()),z(v.getZ())
{
}
vector::vector(const Actor *a){
   x=a->getX();
   y=a->getY();
   z=a->getZ();
}
vector::vector(const Actor &a){
   x=a.getX();
   y=a.getY();
   z=a.getZ();
}
void vector::operator =(const vector &v)
{
   x=v.x;
   y=v.y;
   z=v.z;
}
float vector::dotProduct(const vector &v) const
{
   return (v.x*x+v.y*y+v.z*z);
}
float vector::norm() const
{
    return sqrt(x*x+y*y+z*z);
}
vector vector::operator +(const vector &v) const
{
    return vector(x+v.x,y+v.y,z+v.z);
}
vector vector::operator -(const vector &v) const
{
    return vector(x-v.x,y-v.y,z-v.z);
}
bool vector::operator ==(const vector &v) const
{
    if (x==v.x && y==v.y && z==v.z)
    {
        return true;
    }
    return false;
}
vector vector::operator *(float a) const
{
    return vector(x*a,y*a,z*a);
}
vector vector::operator *(int a) const
{
    return vector(x*a,y*a,z*a);
}
float vector::getX() const
{
   return x;
}
float vector::getY() const
{
   return y;
}
float vector::getZ() const
{
   return z;
}
