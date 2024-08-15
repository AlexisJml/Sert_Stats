#include "archivage.h"

using std::cout; using std::cin;
using std::endl; using std::string;

#define STRING(num) #num
Archivage::Archivage()
{
    timer = 0;
}

void Archivage::Connect(QString serveur, QString user, QString password, QString table)
{
    //connexion à la BDD
    db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(serveur);
        db.setUserName(user);
        db.setPassword(password);
        db.setDatabaseName(table);
}

void Archivage::save(float temp_eau, float temp_huile, float pression_huile, float vitesse, float regime, float accelero, float angle, float latitude, float longitude)
{
    //initialisation
    QSqlQuery query;
    QString eau = QString::number(temp_eau);
    QString thuile = QString::number(temp_huile);
    QString phuile = QString::number(pression_huile);
    QString vit = QString::number(vitesse);
    QString reg = QString::number(regime);
    QString acc = QString::number(accelero);
    QString ang = QString::number(angle);
    QString lati = QString::number(latitude);
    QString longi = QString::number(longitude);

    timer++;

    //prépare la requête SQL
    query.prepare("INSERT INTO moto_data(temp_eau, temp_huile, pression_huile, vitesse, regime, acceleroY, angleY, GPS_lati, GPS_longi, temps) VALUES (:eau, :thuile, :phuile, :vitesse, :regime, :accelero, :angle, :latitude, :longitude, :timer);");

    //affecte les valeurs correspondantes
    query.bindValue(":eau", QVariant(temp_eau));
    query.bindValue(":thuile", QVariant(temp_huile));
    query.bindValue(":phuile", QVariant(pression_huile));
    query.bindValue(":vitesse", QVariant(vitesse));
    query.bindValue(":regime", QVariant(regime));
    query.bindValue(":accelero", QVariant(accelero));
    query.bindValue(":angle", QVariant(angle));
    query.bindValue(":latitude", QVariant(latitude));
    query.bindValue(":longitude", QVariant(longitude));
    query.bindValue(":timer", QVariant(timer));

    //execute la commande SQL
    query.exec();
}

bool Archivage::etat()
{
    //savoir si on est bien connécté à la BDD
    if(db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

