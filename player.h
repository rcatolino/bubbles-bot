#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <QString>
#include <QVariant>

#include "actor.h"

class Player: public Actor
{
public:
    Player(QString id, float x, float y, float z,
                   float vx, float vy, float vz);
    Player(QVariantMap map);
    Player();

    int getLife();
    int getDeaths();
    int getKills();
    void update(QVariantMap map);
    QString getName() const;

    int life, deaths, kills;
    QString name;

};

#endif // PLAYER_H
