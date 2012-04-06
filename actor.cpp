#include "actor.h"
#include <QtCore/qmath.h>

Actor::Actor()
{
}
Actor::Actor(QString id, float x, float y, float z,
               float vx, float vy, float vz)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->z = z;
    this->vx = vx;
    this->vy = vy;
    this->vz = vz;
}
Actor::Actor(QVariantMap map)
{
    //Safegard 'cause default value changes ...
    x = y = z = vx = vy = vz = cube = 0;
    width = height = length = 0.0;

    id = map["id"].toString();
    x = map["x"].toInt();
    y = map["y"].toInt();
    z = map["z"].toInt();
    vx = map["vx"].toInt();
    vy = map["vy"].toInt();
    vz = map["vz"].toInt();
    width = map["w"].toFloat();
    height = map["h"].toFloat();
    length = map["l"].toFloat();
    cube = map["cube"].toInt();
}
/*
vector Actor::getPos()
{
    return vector(x,y,z);
}
vector Actor::getSight()
{
    return vector(vx,vy,vz);
}
*/
float Actor::getDistance(const Actor * self)
{
    float sx = self->getX();
    float sy = self->getY();
    float sz = self->getZ();
    return sqrt((x-sx)*(x-sx)+(y-sy)*(y-sy)+(z-sz)*(z-sz));
}
QString Actor::toString()
{
    QString str = "name : " + id + " x:" + x + " y:" + y + " z:" + z;

    return str;
}

QString Actor::getId() const{
    return id;
}

float Actor::getX() const{
    return x;
}

float Actor::getY() const{
    return y;
}

float Actor::getZ() const{
    return z;
}

float Actor::getVx() const{
    return vx;
}

float Actor::getVy() const{
    return vy;
}

float Actor::getVz() const{
    return vz;
}

float Actor::getWidth() const{
    return width;
}

float Actor::getLength() const{
    return length;
}

float Actor::getHeight() const{
    return height;
}

bool Actor::operator ==(const Actor& a) const{
    return (id == a.id);
}

int Actor::getCube()
{
    return cube;
}
void Actor::update(QVariantMap map)
{
    //Position
    if (map.contains("x"))
        x = map["x"].toInt();
    if (map.contains("y"))
        y = map["y"].toInt();
    if (map.contains("z"))
        z = map["z"].toInt();

    //Color
    if (map.contains("r"))
        r = map["r"].toInt();
    if (map.contains("g"))
        g = map["g"].toInt();
    if (map.contains("b"))
        b = map["b"].toInt();

    if (map.contains("vx"))
        vx = map["vx"].toFloat();
    if (map.contains("vy"))
        vy = map["vy"].toFloat();
    if (map.contains("vz"))
        vz = map["vz"].toFloat();
    if (map.contains("w"))
        width = map["w"].toFloat();
    if (map.contains("h"))
        height = map["h"].toFloat();
    if (map.contains("l"))
        length = map["l"].toFloat();
    if (map.contains("cube"))
        cube = map["cube"].toInt();
}
