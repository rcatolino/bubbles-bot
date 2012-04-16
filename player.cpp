#include "player.h"

Player::Player(){

}

Player::Player(QVariantMap map)
    :Actor(map)
{
    name = map["name"].toString();
    life = map["life"].toInt();
    deaths = map["deaths"].toInt();
    kills = map["kills"].toInt();
}
void Player::update(QVariantMap map)
{
    Actor::update(map);

    if (map.contains("name"))
        name = map["name"].toString();
    if (map.contains("life"))
        life = map["life"].toInt();
    if (map.contains("deaths"))
        deaths = map["deaths"].toInt();
    if (map.contains("kills"))
        kills = map["kills"].toInt();
}
int Player::getLife() const
{
    return life;
}

int Player::getKills() const
{
    return kills;
}


int Player::getDeaths() const
{
    return deaths;
}

QString Player::getName() const
{
    return name;
}
