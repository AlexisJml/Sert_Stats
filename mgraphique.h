/**************************************************************
Auteur: Jumel Alexis
Nom de la classe: MGraphique.h
Description:
            classe de traitement de données sous forme graphique
Date: 07/04/2021
Version:1.0
**************************************************************/
#ifndef MGRAPHIQUE_H
#define MGRAPHIQUE_H

#include <QQuickItem>
#include <QQuickView>
#include <QVariant>
#include <QQuickWidget>
#include "qcustomplot.h"

class MGraphique
{
private:
    QCustomPlot *graphique;
    float x;
    float min ;
    float max ;

public:
    MGraphique();
    MGraphique(QCustomPlot *MonGraph);
    void initialisation();
    void ajouter(float tempeau, float temphuile, float pressionhuile);
    void temp_eau_visible(int val);
    void temp_huile_visible(int val);
    void pression_huile_visible(int val);
    void setQmlObjectValue(QQuickWidget* uiWidget, const char* childName, const char* propertyName, QVariant value);
    void QmlValueChange(QQuickWidget* widget,float value);
    ~MGraphique();
};

#endif // MGRAPHIQUE_H
