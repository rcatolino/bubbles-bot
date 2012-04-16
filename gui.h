#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QString>
#include "gameapp.h"
#include "bots.h"

namespace Ui {
    class gui;
}

class gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui(QWidget *parent = 0);
    ~gui();

private slots :
    void addBots();
    void remBot();
    void quit();

private:
    void majtable();
    void createBot(QString name);
    Ui::gui *ui;
    bots botList;

};

#endif // GUI_H
