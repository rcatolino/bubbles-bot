#ifndef ACTOR_H
#define ACTOR_H

#include <QString>
#include <QVariant>

class Actor
{
public:
    Actor();
    Actor(QString id, float x, float y, float z,
                   float vx, float vy, float vz);
    Actor(QVariantMap dict);
    QString toString();
    float getX() const;
    float getY() const;
    float getZ() const;
    float getVx() const;
    float getVy() const;
    float getVz() const;
    QString getId() const;
    QString getName();
    float getWidth() const;
    float getLength() const;
    float getHeight() const;
    int getCube();

    QString id;
    float x, y, z;
    float vx, vy, vz;
    float ratio;
    float width, length, height;
    int cube;

    bool operator ==(const Actor& a) const;
};

#endif // ACTOR_H
