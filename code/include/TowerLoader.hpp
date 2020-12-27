#ifndef TOWERLOADER_HPP
#define TOWERLOADER_HPP

#include <QString>
#include <QMap>
#include <string>

class TowerLoader
{
private:
    QMap<QString,QString> name;
    QMap<QString,float> parameters;
    QMap<QString,QString> paths;
public:
    TowerLoader(QString towerID,int level=0);
    ~TowerLoader();
    QMap<QString, QString> getName() const;
    QMap<QString, float> getParameters() const;
    QMap<QString, QString> getPaths() const;
};

#endif // TOWERLOADER_HPP
