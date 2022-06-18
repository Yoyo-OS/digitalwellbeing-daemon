#include "dbusinterface.h"
#include "dbushelper.h"
#include <iostream>
#include <QJsonDocument>

DBusInterface::DBusInterface(Logger& l):logger(l)
{
    QDBusConnection::sessionBus().registerService("com.yoyo.DigitalWellbeing");
    std::cerr<<"register"<<QDBusConnection::sessionBus().registerObject("/DigitalWellbeing","com.yoyo.DigitalWellbeing",this,QDBusConnection::ExportAllSlots|QDBusConnection::ExportAllSignals)<<std::endl;
}
QString DBusInterface::getDailyStatJson(){
    qWarning()<<"DBusInterface::getDailyStatJson";
    auto res=logger.readDailyRecordJson();
    return QJsonDocument(res).toJson(QJsonDocument::Compact);
}
QString DBusInterface::getWeeklyStatJson(){
    qWarning()<<"DBusInterface::getWeeklyStatJson";
    auto res=logger.readWeeklyRecordJson();
    return QJsonDocument(res).toJson(QJsonDocument::Compact);
}
QString DBusInterface::getPerAppStatJson(){
    qWarning()<<"DBusInterface::getPerAppStatJson";
    auto res=logger.readPerAppDailyStatJson();
    return QJsonDocument(res).toJson(QJsonDocument::Compact);
}
QString DBusInterface::getBasicStatJson(){
    qWarning()<<"DBusInterface::getBasicStatJson";
    auto res=logger.readBasicStatJson();
    return QJsonDocument(res).toJson(QJsonDocument::Compact);
}
