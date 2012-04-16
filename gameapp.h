#ifndef GAMEAPP_H
#define GAMEAPP_H

#include <QObject>
#include "model.h"
#include "networkclient.h"

class GameApp : public QObject
{
    Q_OBJECT
public:
    explicit GameApp(QString name, QObject *parent = 0);
    void run(QString name, QString server, QString port);
    const QString & getName() const;
    int getKills() const;
    int getDeaths() const;

signals:
public slots:
    void up();
    void changeCourse();
    void chooseDirection();

 private:
    Model * mod;
    NetworkClient * nc;
    int lastTarget;
    int dir;

};

#endif // GAMEAPP_H
