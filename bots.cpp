#include "bots.h"

bots::bots(QObject *parent) :
    QAbstractTableModel(parent)
{
    columnNb=3;
    rowNb=0;
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
QVariant bots::data(const QModelIndex &index, int) const
{
    if (index.row()>rowNb || index.row()<0)
    {
        return QVariant::Invalid;
    }
    switch (index.column())
    {
        case 0:
            return botList[index.row()]->getName();
            break;
        case 1:
            return botList[index.row()]->getKills();
            break;
        case 2:
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
        botList.append(newBot);
        rowNb++;
        emit dataChanged(createIndex(index-1,0),createIndex(index,3));
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
