/**************************************************************
Auteur: Jumel Alexis
Nom de la classe: MCircuit.h
Description:
            classe d'affichage de la position de la moto
Date: 18/05/2021
Version:1.0
**************************************************************/
#ifndef MCIRCUIT_H
#define MCIRCUIT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPainter>
#include <QDebug>

//coordonnées circuit Le Mans
#define LM_LARGEUR_IMAGE 580
#define LM_HAUTEUR_IMAGE 800

#define LM_LATITUDE_MAX 47.959367
#define LM_LONGITUDE_GAUCHE 0.206831
#define LM_LATITUDE_MIN 47.947871
#define LM_LONGITUDE_DROITE 0.219276

#define LM_RASTER_LAT (LM_LATITUDE_MAX - LM_LATITUDE_MIN) / LM_HAUTEUR_IMAGE
#define LM_RASTER_LONG (LM_LONGITUDE_DROITE - LM_LONGITUDE_GAUCHE) / LM_LARGEUR_IMAGE

//coordonnées circuit Carole
#define C_LARGEUR_IMAGE  456
#define C_HAUTEUR_IMAGE   890

#define C_LATITUDE_MAX      48.983822
#define C_LONGITUDE_GAUCHE  2.519034
#define C_LATITUDE_MIN      48.977555
#define C_LONGITUDE_DROITE  2.523926

#define C_RASTER_LAT (C_LATITUDE_MAX - C_LATITUDE_MIN) / C_HAUTEUR_IMAGE
#define C_RASTER_LONG (C_LONGITUDE_DROITE - C_LONGITUDE_GAUCHE) / C_LARGEUR_IMAGE

//coordonnées circuit Le Castelet
#define LC_LARGEUR_IMAGE  1330
#define LC_HAUTEUR_IMAGE   842

#define LC_LATITUDE_MAX      43.259081
#define LC_LONGITUDE_GAUCHE  5.777199
#define LC_LATITUDE_MIN      43.245922
#define LC_LONGITUDE_DROITE  5.805738

#define LC_RASTER_LAT (LC_LATITUDE_MAX - LC_LATITUDE_MIN) / LC_HAUTEUR_IMAGE
#define LC_RASTER_LONG (LC_LONGITUDE_DROITE - LC_LONGITUDE_GAUCHE) / LC_LARGEUR_IMAGE

//coordonnées cité scolaire
#define CS_LARGEUR_IMAGE  3136
#define CS_HAUTEUR_IMAGE   2260

#define CS_LATITUDE_MAX      49.876418
#define CS_LONGITUDE_GAUCHE  2.293181
#define CS_LATITUDE_MIN      49.872511
#define CS_LONGITUDE_DROITE  2.301593

#define CS_RASTER_LAT (CS_LATITUDE_MAX - CS_LATITUDE_MIN) / CS_HAUTEUR_IMAGE
#define CS_RASTER_LONG (CS_LONGITUDE_DROITE - CS_LONGITUDE_GAUCHE) / CS_LARGEUR_IMAGE

class MCircuit
{
private:
    int pixel_x;
    int pixel_y;
    QGraphicsScene *scene;
    QGraphicsView *map;
    QGraphicsPixmapItem *item_image;
    QPixmap image_carole;
    QPixmap image_lemans;
    QPixmap image_lecastelet;
    QPixmap image_cite;
    int choix;
    QPainter *paint_cite;
    QPainter *paint_lemans;
    QPainter *paint_lecastelet;
    QPainter *paint_carole;
    QPen pen;

public:
    MCircuit(QGraphicsView *map);
    void SetPosition(float x, float y);
    void SetCircuit(int circuit);
    ~MCircuit();

};

#endif // MCIRCUIT_H
