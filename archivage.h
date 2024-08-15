#ifndef ARCHIVAGE_H
#define ARCHIVAGE_H

#include <QString>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <iostream>

class Archivage
{
private:
    QSqlDatabase db;
    int timer;
public:
    Archivage();
    void Connect(QString serveur, QString user, QString password, QString table);
    void save(float temp_eau, float temp_huile, float pression_huile, float vitesse, float regime, float accelero, float angle, float latitude, float longitude);
    bool etat();
    void receive();
    void Disconnect();
    ~Archivage();
};

#endif // ARCHIVAGE_H
