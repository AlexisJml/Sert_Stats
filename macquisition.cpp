#include "macquisition.h"
#include <QtCore>

MAcquisition::MAcquisition(QObject *parent) : QThread(parent)
{
/*///////////recherche le port de la xBee/////////////////////////////*/

    for(int i = 2;i<15;i++)
    {
        if(serial.isOpen()) //vérifie si ce COM est déjà ouvert
        {
            break;
        }
        QString com = "COM";
        com += QString::number(i);
        qDebug()<< com;
        serial.setPortName(com);
        serial.setBaudRate(QSerialPort::Baud57600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        int error = serial.open(QIODevice::ReadOnly);
        if(error == 0)
        {
            stop = true;
        }
        else
        {
            stop = false;
        }
        serial.clear();
    }

/*//////////////////////////////////////////////////////////////////////////////*/

    capteur = false;
    accelero = false;
    angle = false;
    gps = false;

}

void MAcquisition::run()
{
    //initialisation
    int i = 0;
    int j = 0;
    QMutex mutex;

    QString trame;
    QStringList tramefinal;
    QString donnee[100];

    //traitement
    //boucle infini tant que la variable stop n'est pas égal à 1
    while(etat()== true && stop != true)
    {
        //attend la reception de trame
        if(serial.waitForReadyRead(1000))
        {
            tramefinal.clear();
            data = serial.readLine();
            trame = data.mid(0,data.indexOf('*'));
            tramefinal = trame.split(",");

            if(tramefinal[0] == "$IRCAP" && capteur == false)  //$IRCAP,95.00,90.50,4.50,150.00,3000.00,*61
            {
                j = 0;
                for(i=1;i<=5;i++)
                {
                    donnee[j] = tramefinal[i];
                    j++;
                    //qDebug() << "IRCAP : " + tramefinal[i];
                }
                capteur = true;
            }

            if(tramefinal[0] == "$IRACC" && accelero == false)  //$IRACC,-1.20,-1.05,-1.17,*69
            {
                j = 5;
                for(i=1;i<=3;i++)
                {
                    donnee[j] = tramefinal[i];
                    j++;
                    //qDebug() << "IRACC : " + tramefinal[i];
                }
                accelero = true;
            }

            if(tramefinal[0] == "$IRANG" && angle == false)  //$IRANG,36.4,58.4*7C
            {
                //récupère et place au bonne endroit les données
                j = 8;
                for(i=1;i<=2;i++)
                {
                    donnee[j] = tramefinal[i];
                    j++;
                    //qDebug() << "IRANG : " + tramefinal[i];
                }
                angle = true;
            }
            if(tramefinal[0] == "$GPRMC" && gps == false)
            {
                float la_d = tramefinal[3].mid(0,2).toFloat();
                float la_m = tramefinal[3].mid(2,tramefinal[3].indexOf("/n")).toFloat();
                donnee[11] = QString::number(la_d +(la_m/60));  //longitude

                float lo_d = tramefinal[5].mid(0,3).toFloat();
                float lo_m = tramefinal[5].mid(3,tramefinal[5].indexOf("/n")).toFloat();
                donnee[10] = QString::number(lo_d +(lo_m/60));  //latitude

                //qDebug()<<"latitude: "<<donne[10];
                //qDebug()<<"longitude: "<<donnee[11];
                gps = true;
            }

            //sortie
            if(capteur==true && accelero==true && angle==true && gps == true)
            {
                //envoi le tableau de données en signal
                mutex.lock();
                emit Traitement(donnee);
                mutex.unlock();

                capteur = false;
                accelero = false;
                angle = false;
                gps = false;
            }
            msleep(140);   //attend 140 pour ReadLine
        }
    }
    if(etat() == false)
    {
        QString *erreur = new QString("erreur");
        mutex.lock();
        emit Traitement(erreur);
        mutex.unlock();
        capteur = false;
        accelero = false;
        angle = false;
        gps = false;
    }
}

bool MAcquisition::etat()
{
    //vérifie si la COM de la xBee et ouverte
    if(serial.isOpen())
    {
        return true;
    }
    else
    {
        for(int i = 2;i<10;i++)
        {
            if(serial.isOpen()) //vérifie si ce COM est déjà ouvert
            {
                break;
            }
            QString com = "COM";
            com += QString::number(i);
            qDebug()<< com;
            serial.setPortName(com);
            serial.setBaudRate(QSerialPort::Baud9600);
            serial.setDataBits(QSerialPort::Data8);
            serial.setParity(QSerialPort::NoParity);
            serial.setStopBits(QSerialPort::OneStop);
            serial.setFlowControl(QSerialPort::NoFlowControl);
            int error = serial.open(QIODevice::ReadOnly);
            if(error == 0)
            {
                stop = true;
                return false;
            }
            else
            {
                stop = false;
                serial.clear();
                return true;
            }
        }
    }
}

MAcquisition::~MAcquisition()
{
    serial.close();
}
