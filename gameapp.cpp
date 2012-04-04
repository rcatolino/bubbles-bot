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
    Model * mod = Model::getInstance();
    QList<Player> players(mod->getUpdatedPlayers());
    int nbPlayers = players.size();
    if (nbPlayers > 1){

        target = &(players.at((lastTarget++)%nbPlayers));
        qDebug() << lastTarget;
        self = &mod->getSelf();
        if (target->name==mod->getName()){
            return; //don't shot yourself!!
        }
        //qDebug() << "Target chosen";
        mod->shot(target->getX()-self->getX(),target->getY()-self->getY(),target->getZ()-self->getZ());
        //qDebug() << "bot is in :" << self->getX() << self->getY() << self->getZ();
        //qDebug() << "player is in :" << target->getX() << target->getY() << target->getZ();
        //qDebug() << "fireing at :" << target->getX()-self->getX() << target->getY()-self->getY()<< target->getZ()-self->getZ();
    } else {
        //qDebug() << "No target";
    }
}
void GameApp::endOfThread()
{
    //qDebug() << "lol";
}
void GameApp::changeCourse()
{
    Model * mod = Model::getInstance();
    switch (dir){
        case 0 :
            mod->updateKeys("UP",false);
            mod->updateKeys("LEFT",true);
            dir++;
            break;
        case 1 :
            mod->updateKeys("LEFT",false);
            mod->updateKeys("UP",true);
            dir++;
            break;
        case 2 :
            mod->updateKeys("UP",false);
            mod->updateKeys("RIGHT",true);
            dir++;
            break;
        case 3 :
            mod->updateKeys("RIGHT",false);
            mod->updateKeys("UP",true);
            dir=(dir+1)%4;
            break;
            /*
        case 5 :
            mod->updateKeys("RIGHT",false);
            mod->updateKeys("UP",true);
            dir++;
            break;
        case 6 :
            mod->updateKeys("UP",false);
            mod->updateKeys("DOWN",true);
            dir++;
            break;
        case 7 :
            mod->updateKeys("DOWN",false);
            mod->updateKeys("UP",true);
            dir=(dir+1)%8;
            break;
            */
    }
}
void GameApp::run(QString name, QString server, QString port)
{
    Model * mod = Model::getInstance();
    dir=0;
    QTimer * posTimer = new QTimer;
    connect(posTimer,SIGNAL(timeout()),this,SLOT(changeCourse()));
    posTimer->start(1000);
    QTimer * shotTimer = new QTimer;
    connect(shotTimer,SIGNAL(timeout()),this,SLOT(up()));
    shotTimer->start(40);
    nc = new NetworkClient(this);
    nc->startOn(server,port.toShort());
    qDebug() << "Bot '" << name <<"' connected on server " << server <<":"<< port;
    mod->updateKeys("UP",true);
    mod->updateKeys("UP",false);
}
