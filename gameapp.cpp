#include "gameapp.h"
#include "model.h"
#include "networkclient.h"
#include "gameapp.h"

GameApp::GameApp(QString name, QObject *parent) :
    QObject(parent)
{
    lastTarget=0;
    mod=new Model;
    mod->setName(name);
}

void GameApp::up()
{
    const Player * target;
    const Player * self;
    float svx, svy, svz;
    //Model * mod = Model::getInstance();
    QList<Player> players(mod->getUpdatedPlayers());
    int nbPlayers = players.size();
    if (nbPlayers > 1){
        target = mod->getBestPlayer();
        self = mod->getSelf();
        if (target->name==mod->getName()){
            qDebug() << "Don't shoot";
            return; //don't shoot yourself!!
        }
        qDebug() << "Target chosen";
        if(!mod->freeWay(self,target))
        {
            qDebug() << "There is an obstacle, don't shoot";
            return; //There is an obstacle, don't shoot
        }
        svx=self->getVx();
        svy=self->getVy();
        svz=self->getVz();
        mod->shot(target->getX()-self->getX(),target->getY()-self->getY(),target->getZ()-self->getZ());
        nc->sendMouseState(svx,svy,svz);
        //qDebug() << "bot is in :" << self->getX() << self->getY() << self->getZ();
        //qDebug() << "player is in :" << target->getX() << target->getY() << target->getZ();
        //qDebug() << "fireing at :" << target->getX()-self->getX() << target->getY()-self->getY()<< target->getZ()-self->getZ();
    } else {
        //qDebug() << "No target";
    }
}
const QString & GameApp::getName() const
{
    return mod->getName();
}
int GameApp::getKills() const
{
    return mod->getSelf()->getKills();
}
int GameApp::getDeaths() const
{
    return mod->getSelf()->getDeaths();
}
void GameApp::changeCourse()
{
    //Model * mod = Model::getInstance();
    const Player * target = mod->getBestPlayer();
    qDebug() << "target name :" << target->getName();
    const Player * self = mod->getSelf();
    if (self!=target){
        mod->shot(target->getX()-self->getX(),target->getY()-self->getY(),target->getZ()-self->getZ());
    }
    dir=qrand()%4;
    qDebug() << "direction" << dir;
    switch (dir){
        case 0 :
            mod->updateKeys("UP",false);
            mod->updateKeys("LEFT",true);
            break;
        case 1 :
            mod->updateKeys("LEFT",false);
            mod->updateKeys("UP",true);
            break;
        case 2 :
            mod->updateKeys("UP",false);
            mod->updateKeys("RIGHT",true);
            break;
        case 3 :
            mod->updateKeys("RIGHT",false);
            mod->updateKeys("UP",true);
            break;
    }
}
void GameApp::chooseDirection()
{
    //Model * mod = Model::getInstance();
    QList<Obstacles> obstacles = mod->getUpdatedObstacles();
    Obstacles * ob;
    const Player * self = mod->getSelf();
    int minId=-1;
    float minDis=400;
    for (int i=0; i<obstacles.size(); ++i)
    {
        float distance = obstacles[i].getDistance(self);
        if (distance < 500) {
            if (i>minId && distance<minDis){
                minId=i;
                minDis=distance;
            }
            qDebug() << "distance :" << distance << " width :" <<obstacles[i].getWidth() \
                     << "length :" << obstacles[i].getLength() << "height :" << obstacles[i].getHeight();
        }
    }
    if (minId>-1) {
        ob=&obstacles[minId];
        int aleax = qrand()%150 - 75;
        int aleay = qrand()%150 - 75;
        int aleaz = qrand()%150 - 75;
        nc->sendMouseState(self->getX()-ob->getX()+aleax,self->getY()-ob->getY()+aleay,self->getZ()-ob->getZ()+aleaz);
    }
    mod->updateKeys("UP",true);
}
void GameApp::run(QString name, QString server, QString port)
{
    //Model * mod = Model::getInstance();
    dir=0;
    QTimer * posTimer = new QTimer;
    connect(posTimer,SIGNAL(timeout()),this,SLOT(changeCourse()));
    posTimer->start(1500);
    QTimer * shotTimer = new QTimer;
    connect(shotTimer,SIGNAL(timeout()),this,SLOT(up()));
    shotTimer->start(240);
    QTimer * dirTimer = new QTimer;
    connect(dirTimer,SIGNAL(timeout()),this,SLOT(chooseDirection()));
    dirTimer->start(100);
    nc = new NetworkClient(mod,this);
    nc->startOn(server,port.toShort());
    qDebug() << "Bot '" << name <<"' connected on server " << server <<":"<< port;
    mod->updateKeys("UP",true);
    mod->updateKeys("UP",false);
}
