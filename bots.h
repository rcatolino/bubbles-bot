#ifndef BOTS_H
#define BOTS_H

#include <QAbstractTableModel>
#include <QList>
#include "gameapp.h"

class bots : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit bots(QObject *parent = 0);
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int size() const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    GameApp* & operator[](const QString & key);
    int find(const QString & key);
    void erase(const QString & key);
    void erase(int index);

signals:

public slots:

private:
    int columnNb;
    int rowNb;
    QList<GameApp*> botList;
    GameApp * end;
};

#endif // BOTS_H
