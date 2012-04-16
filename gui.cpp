#include "gui.h"
#include "ui_gui.h"
#include <QtCore>

gui::gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui)
{
    ui->setupUi(this);
    ui->tvbots->setModel(&botList);
    ui->tvbots->show();
    connect(ui->pbaddbot,SIGNAL(clicked()),this,SLOT(addBots()));
    connect(ui->pbquit,SIGNAL(clicked()),this,SLOT(quit()));
}

gui::~gui()
{
    delete ui;
}
void gui::quit()
{
    exit(0);
}
void gui::majtable()
{
}
void gui::remBot()
{

}
void gui::addBots()
{
    int bnb = ui->sbbotnb->value();
    if (bnb==1)
    {
        createBot(ui->lename->text());
    } else if (bnb>1) {
       for (int i=0; i<bnb; i++)
       {
           createBot(ui->lename->text()+QString::number(i+1));
       }
    }
}
void gui::createBot(QString name)
{
    if (botList.find(name)==botList.size())
    {
        GameApp * newBot = new GameApp(name);
        newBot->run(name,ui->leaddress->text(),ui->leport->text());
        botList[name]=newBot;
        ui->tvbots->setModel(&botList);
    } else {
        qDebug() << "Bot already playing :" << name;
    }
}
