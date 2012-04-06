#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>

#include <qjson/serializer.h>

#include "networkclient.h"
#include "model.h"
#include "player.h"

NetworkClient::NetworkClient(QObject *parent) :
    QObject(parent)
{
    sock = new QTcpSocket(this);
    Model * m = Model::getInstance();
    name = m->getName();

    connect(sock, SIGNAL(connected()), this, SLOT(init()));
    connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(err()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(processIncommingData()));
    connect(m, SIGNAL(keyChanged(QString,bool)), this, SLOT(sendKeyState(QString,bool)));
    connect(m, SIGNAL(mouseChanged(float,float,float)), this, SLOT(sendMouseState(float,float,float)));
    connect(m, SIGNAL(shotEvent(float,float,float)), this, SLOT(sendShot(float,float,float)));
    connect(this,SIGNAL(event()),parent,SLOT(up()));
}
void NetworkClient::err(){
    qDebug() << "tcp connection : error";
}
void NetworkClient::startOn(QString host, qint16 port)
{
    sock->connectToHost(host, port);
    if (!sock->waitForConnected(1000)){
         qDebug()<< "connection error :" << sock->errorString();
    } else {
        qDebug() << "conncected";
    }
}

void NetworkClient::setName(QString name)
{
    this->name = name;
}

void NetworkClient::init()
{
    sock->write("init "+name.toAscii()+"$$");
    QString mess =
            "init "+name+" "+QString::number(255)+" "+QString::number(215)
            +" "+QString::number(0)+"$$";
    sock->write(mess.toAscii());
    qDebug() << "server name :" << name.toAscii();
}

void NetworkClient::modifications(QList<QPair<QString, QVariant> > keys)
{
    QVariantMap map;
    QVariantList list;

    for(int i = 0; i < keys.size(); ++i)
    {
        QPair<QString, QVariant> pair = keys.at(i);
        QVariantMap v;
        v.insert("name", pair.first);
        v.insert("state", pair.second);
        list.append(v);
    }
    map.insert("modifications", list);


    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(map);
    //qDebug() << json;

    send(json);
}

void NetworkClient::send(QString mess)
{
    qDebug() << "Sent " << mess;

    sock->flush();
    sock->write((mess+"$$").toAscii());
}

void NetworkClient::processIncommingData()
{
    /*
    QByteArray received = sock->readAll();

    QString curr(received);

    //qDebug() << "Data received";
    messages += curr;

    if (messages.contains("$$"))
    {
        QList<QString> toProcess = messages.split("$$");

        for(int i=0; i < toProcess.size() - 1; i++)
        {
            Model * m = Model::getInstance();

            if (toProcess[i].contains("field"))
            {
                m->setUpdatedObstacles(toProcess[i]);
                m->setMap(toProcess[i]);
            }

            m->setUpdatedPlayers(toProcess[i]);
            m->setUpdatedBullets(toProcess[i]);            
        }

        messages = toProcess[toProcess.size() - 1];
    }
    */
      QByteArray received = sock->readAll();
    //qDebug() << "Received " <<  received;

    QString curr(received);

    messages += curr;

    if (messages.contains("$$"))
    {
        QList<QString> toProcess = messages.split("$$");

        for(int i=0; i < toProcess.size() - 1; i++)
        {
            Model * m = Model::getInstance();

            if (toProcess[i].contains("field"))
            {
                m->setUpdatedObstacles(toProcess[i]);
                m->setMap(toProcess[i]);
            }

            m->setUpdatedPlayers(toProcess[i]);
            m->setUpdatedBullets(toProcess[i]);
            m->setToClear(toProcess[i]);
        }

        messages = toProcess[toProcess.size() - 1];
    }
}

void NetworkClient::sendKeyState(QString name, bool state)
{
    //qDebug() << "In sendKeyState Slot";
    QList<QPair<QString, QVariant> > list;
    QPair<QString, QVariant> pair(name, state);
    list.append(pair);
    modifications(list);
}

void NetworkClient::sendMouseState(float x, float y, float z)
{
    QList<QPair<QString, QVariant> > list;
    QVariantMap obj;
    obj["x"] = (double)x;
    obj["y"] = (double)y;
    obj["z"] = (double)z;
    //qDebug() << obj["x"];
    QPair<QString, QVariant> pair("MOUSE", obj);
    list.append(pair);
    modifications(list);
}

void NetworkClient::sendShot(float x, float y, float z)
{
    QVariantMap obj;
    QVariantMap shoot;
    QVariantMap state;

    state["x"] = (double)x;
    state["y"] = (double)y;
    state["z"] = (double)z;
    shoot["state"] = state;
    shoot["name"] = "MOUSE";
    obj["shoot"] = shoot;

    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(obj);

    send(json);
}


