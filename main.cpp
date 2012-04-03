#include <QtCore/QCoreApplication>
#include "model.h"
#include "gameapp.h"
int main(int argc, char *argv[])
{
    GameApp ga;
    QCoreApplication a(argc, argv);
    if (argc < 4){
        return 1;
    }
    Model * mod = Model::getInstance();
    mod->setName(argv[3]);
    ga.run(argv[3],argv[1],argv[2]);
    qDebug()<<"execution started";
    return a.exec();
}
