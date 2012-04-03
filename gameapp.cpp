#include "gameapp.h"
#include "model.h"
#include "networkclient.h"
#include "gameapp.h"

GameApp::GameApp(QObject *parent) :
    QObject(parent)
{
    lastTarget=0;
}

void GameApp::up()
{
    const Player * target;
    const Player * self;
    const int ratio = 180;
    Model * mod = Model::getInstance();
    QList<Player> players(mod->getUpdatedPlayers());
    //qDebug() << mod->getUpdatedPlayers().size();
    int nbPlayers = mod->getUpdatedPlayers().size();
    if (nbPlayers > 1){

        target = &(players.at((lastTarget++)%nbPlayers));
        self = &(players.at((lastTarget)%nbPlayers));
        if (target->name==mod->getName()){
            return; //don't shot yourself!!
        }
        qDebug() << "Target chosen";
        mod->shot(target->getX()-self->getX(),target->getY()-self->getY(),target->getZ()-self->getZ());
        qDebug() << "Target shot at " << target->x/ratio << target->y/ratio << target->z/ratio;
        qDebug() << "self is at " << self->x << self->y << self->z;
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
    mod->updateKeys("UP",false);
}
