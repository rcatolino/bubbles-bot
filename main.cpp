//#include <QtCore/QCoreApplication>
#include <QtGui/QApplication>
#include "model.h"
#include "gameapp.h"
#include "gui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui mainWindow;
    mainWindow.show();
    qDebug()<<"execution started";
    return a.exec();
}
