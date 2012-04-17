#include "bots.h"

bots::bots(QObject *parent) :
    QAbstractTableModel(parent)
{
    columnNb=3;
    rowNb=0;
    qDebug() << "roles count" <<roleNames().size();
    qDebug() << "roles " <<roleNames()[Qt::DisplayRole];
    qDebug() << "roles " <<roleNames()[1];
    qDebug() << "roles " <<roleNames()[2];
    qDebug() << "roles " <<roleNames()[3];
    qDebug() << "roles " <<roleNames()[4];
    qDebug() << "roles " <<roleNames()[5];
    end=(GameApp*)-1;
}

int bots::columnCount(const QModelIndex &) const
{
    return columnNb;
}
int bots::rowCount(const QModelIndex &) const
{
    return rowNb;
}
int bots::size() const
{
    return rowNb;
}
QVariant bots::data(const QModelIndex &index, int role) const
{
    qDebug() <<"Data called with col: "<<index.column()<<"row:"<<index.row() << "role :" << roleNames()[role];
    if (role!=Qt::DisplayRole)
    {
        qDebug() << "Invalid Role";
        return QVariant();
    }
    if (index.row()>rowNb || index.row()<0)
    {
        qDebug() << "Invalid Index";
        return QVariant::Invalid;
    }
    switch (index.column())
    {
        case 0:
            qDebug()<<"return " << botList[index.row()]->getName();
            return botList[index.row()]->getName();
            break;
        case 1:
            qDebug()<<"return kills";
            qDebug()<<"return " << botList[index.row()]->getKills();
            return botList[index.row()]->getKills();
            break;
        case 2:
            qDebug()<<"return " << botList[index.row()]->getDeaths();
            return botList[index.row()]->getDeaths();
    }
    return QVariant::Invalid;
}
QVariant bots::headerData(int section, Qt::Orientation orientation, int) const
{
    if (orientation==Qt::Horizontal){
        switch (section)
        {
            case 0:
                return "Bot Name";
                break;
            case 1:
                return "Kills";
                break;
            case 2:
                return "Deaths";
        }
    }
    return QVariant::Invalid;
}
GameApp* & bots::operator[](const QString & key)
{
    int index=0;
    for(; index<botList.size(); index++)
    {
        if(botList.at(index)->getName()==key)
        {
            return botList[index];
        }
    }
    if (index==botList.size())
    {
        GameApp * newBot;
        beginInsertRows(QModelIndex(),rowNb,rowNb);
        botList.append(newBot);
        rowNb++;
        endInsertRows();
        return botList[index];
    }
    return end;
}
int bots::find(const QString & key)
{
    int index=0;
    for(; index<botList.size(); index++)
    {
        if(botList.at(index)->getName()==key)
        {
            return index;
        }
    }
    return index;
}
void bots::erase(const QString & key)
{
    erase(find(key));
}
void bots::erase(int index)
{
    botList.removeAt(index);
    emit dataChanged(createIndex(index-1,0),createIndex(index+1,3));
}
