#include "actor.h"
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

QString Actor::toString()
{
    QString str = "name : " + id + " x:" + x + " y:" + y + " z:" + z;

    return str;
}

QString Actor::getId(){
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

