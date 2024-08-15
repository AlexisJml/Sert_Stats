/**************************************************************
Auteur: Jumel Alexis
Nom de la classe: ihm_sert.h
Description:
            interface du projet
Date: 20/02/2020
Version: 1.0
    ajout de la classe MAcquisition
Version: 2.0
    ajout de la classe MGraphique
Version: 3.0
    ajout de la classe MCircuit
**************************************************************/
#ifndef IHM_SERT_H
#define IHM_SERT_H

#include <QDialog>
#include "macquisition.h"
#include "mgraphique.h"
#include "mcircuit.h"
#include "archivage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ihm_sert; }
QT_END_NAMESPACE

class ihm_sert : public QDialog
{
    Q_OBJECT

public:
    ihm_sert(QWidget *parent = nullptr);
    ~ihm_sert();

private slots:
    void result(QString*);
    void on_start_clicked();
    void on_stop_clicked();
    void on_check_tempeau_stateChanged(int arg1);
    void on_check_temphuile_stateChanged(int arg1);
    void on_check_pressionhuile_stateChanged(int arg1);
    void on_valider_clicked();
    void on_connexion_xbee_clicked();

    void on_button_BDD_clicked();

private:
    Ui::ihm_sert *ui;
    MAcquisition *Acquisition;
    MGraphique *MonGraph;
    MCircuit *MonCircuit;
    Archivage *db;
    float vitessemoy;
};
#endif // IHM_SERT_H
