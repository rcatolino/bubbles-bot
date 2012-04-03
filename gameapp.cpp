#include "gameapp.h"
#include "model.h"
#include "networkclient.h"
#include "gameapp.h"

GameApp::GameApp(QObject *parent) :
    QObject(parent)
{
}

void GameApp::up()
{
    Player * target;
    Model * mod = Model::getInstance();
    QList<Player> players(mod->getUpdatedPlayers());
    qDebug() << mod->getUpdatedPlayers().size();
    qDebug() << "Retreived players positions";
    mod->updateKeys("UP",false);
    if (!players.isEmpty()){
        target = &(players.back());
        qDebug() << "Target chosen";
        mod->shot(target->x,target->y,target->z);
        qDebug() << "Target shot";
    } else {
        qDebug() << "No target";
    }
}
void GameApp::endOfThread()
{
    //qDebug() << "lol";
}

void GameApp::run(QString name, QString server, QString port)
{
    Model * mod = Model::getInstance();
    nc = new NetworkClient(this);
    nc->startOn(server,port.toShort());
    qDebug() << "Bot '" << name <<"' connected on server " << server <<":"<< port;
    mod->updateKeys("UP",true);
}
