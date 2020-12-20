
#include <code/include/TowerLoader.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <QDebug>
#include <QDirIterator>
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <sstream>

namespace pt = boost::property_tree;

QMap<QString, QString> TowerLoader::getName() const
{
    return name;
}

QMap<QString, float> TowerLoader::getParameters() const
{
    return parameters;
}

QMap<QString, QString> TowerLoader::getPaths() const
{
    return paths;
}

TowerLoader::TowerLoader(QString towerID)
    : name(QMap<QString,QString>()),parameters(QMap<QString,float>()),paths(QMap<QString,QString>())
{
    QString fileName=towerID.append("Tower.json");
    QString path=QString(":/towerTypes/").append(fileName);

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::exception();
    QTextStream in(&file);
    std::stringstream str;
    str<<in.readAll().toStdString();
    pt::ptree tree;
    pt::read_json(str,tree);
//    qDebug()<<QString::fromStdString(tree.get("name",""));
    for(auto& it : tree)
    {
        if(it.first=="name" || it.first=="id")
            name[QString::fromStdString(it.first)]=QString::fromStdString(tree.get(it.first,""));
        else if(QString::fromStdString(it.first).contains("path",Qt::CaseInsensitive))
            paths[QString::fromStdString(it.first)]=QString::fromStdString(tree.get(it.first,""));
        else
            parameters[QString::fromStdString(it.first)]=static_cast<float>(tree.get<float>(it.first));
    }
}

TowerLoader::~TowerLoader()
{

}
