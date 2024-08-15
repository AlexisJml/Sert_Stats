/**************************************************************
Auteur: Jumel Alexis
Nom de la classe: MAcquisition.h
Description:
            classe de récupération de données via la liaison xBee
Date: 20/02/2020
Version:1.0
**************************************************************/
#ifndef MACQUISITION_H
#define MACQUISITION_H

#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

class MAcquisition : public QThread
{
    Q_OBJECT
public:
    explicit MAcquisition(QObject *parent = 0);
    void run();
    bool stop;
    bool etat();
    ~MAcquisition();
signals:
    void Traitement(QString*);

public slots:

private:
    QSerialPort serial;
    QString data;
    bool capteur;
    bool accelero;
    bool angle;
    bool gps;

};

#endif // MACQUISITION_H
