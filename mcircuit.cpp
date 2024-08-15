#include "mcircuit.h"

MCircuit::MCircuit(QGraphicsView *map)
{
    pixel_x = 50;
    pixel_y = 50;
    choix = 0;
    this->map = map;

    //défini chaque images
    image_carole.load("Carole_Google_Map.jpg");
    image_carole = image_carole.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    image_lemans.load("Le_Mans_Google_map.jpg");
    image_lemans = image_lemans.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    image_lecastelet.load("Le_Castelet_Google_Map.jpg");
    image_lecastelet = image_lecastelet.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    image_cite.load("cite.bmp");
    image_cite = image_cite.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    //enlève les scrollbars de la map
    this->map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    paint_cite = new QPainter(&image_cite);
    paint_lemans = new QPainter(&image_lemans);
    paint_carole = new QPainter(&image_carole);
    paint_lecastelet = new QPainter(&image_lecastelet);

    pen.setWidth(25);
    pen.setBrush(Qt::SolidPattern);
    pen.setColor(Qt::red);

    //affecte l'image à une scène
    scene = new QGraphicsScene();
    scene->setBackgroundBrush(image_lemans);
    scene->setSceneRect(image_lemans.rect());
    this->map->setFrameStyle(QFrame::NoFrame);
    this->map->setStyleSheet("background: transparent");
    this->map->setTransform(QTransform());
    this->map->setScene(scene);

    this->map->show();
}

MCircuit::~MCircuit()
{
    scene->clear();
    map->close();
}

void MCircuit::SetPosition(float x, float y)
{
    if(choix == 0) //lemans
    {
        //transforme les coordonnées en pixel
        double longitude = x;
        float ecart_x = longitude - LM_LONGITUDE_GAUCHE;
        float temp = LM_RASTER_LONG;
        pixel_x = (int)(ecart_x/temp);

        double latitude = y;
        temp = LM_LATITUDE_MAX;
        float ecart_y = temp - latitude;
        temp = LM_RASTER_LAT;
        pixel_y = (int)(ecart_y/temp);

        paint_lemans->setPen(pen);
        paint_lemans->drawEllipse(pixel_x,pixel_y,50,50);
        paint_lemans->end();
        image_lemans = image_lemans.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
        scene->setBackgroundBrush(image_lemans);
        image_lemans.load("Le_Mans_Google_map.jpg");
        paint_lemans->begin(&image_lemans);
    }
    else if(choix == 1) //carole
    {
        //transforme les coordonnées en pixel
        double longitude = x;
        float ecart_x = longitude - C_LONGITUDE_GAUCHE;
        float temp = C_RASTER_LONG;
        pixel_x = (int)(ecart_x/temp);

        double latitude = y;
        temp = C_LATITUDE_MAX;
        float ecart_y = temp - latitude;
        temp = C_RASTER_LAT;
        pixel_y = (int)(ecart_y/temp);

        paint_carole->setPen(pen);
        paint_carole->drawEllipse(pixel_x,pixel_y,50,50);
        paint_carole->end();
        image_carole = image_carole.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
        scene->setBackgroundBrush(image_carole);
        image_carole.load("Carole_Google_Map.jpg");
        paint_carole->begin(&image_carole);
    }
    else if(choix == 2) //lecastelet
    {
        //transforme les coordonnées en pixel
        double longitude = x;
        float ecart_x = longitude - LC_LONGITUDE_GAUCHE;
        float temp = LC_RASTER_LONG;
        pixel_x = (int)(ecart_x/temp);

        double latitude = y;
        temp = LC_LATITUDE_MAX;
        float ecart_y = temp - latitude;
        temp = LC_RASTER_LAT;
        pixel_y = (int)(ecart_y/temp);

        paint_lecastelet->setPen(pen);
        paint_lecastelet->drawEllipse(pixel_x,pixel_y,50,50);
        paint_lecastelet->end();
        image_lecastelet = image_lecastelet.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
        scene->setBackgroundBrush(image_lecastelet);
        image_lecastelet.load("Le_Castelet_Google_Map.jpg");
        paint_lecastelet->begin(&image_lecastelet);
    }
    else if(choix == 3) //cité scolaire
    {
        //transforme les coordonnées en pixel
        double longitude = x;
        float ecart_x = longitude - CS_LONGITUDE_GAUCHE;
        float temp = CS_RASTER_LONG;
        pixel_x = (int)(ecart_x/temp);

        double latitude = y;
        temp = CS_LATITUDE_MAX;
        float ecart_y = temp - latitude;
        temp = CS_RASTER_LAT;
        pixel_y = (int)( ecart_y/temp);

        paint_cite->setPen(pen);
        paint_cite->drawPoint(pixel_x,pixel_y);
        //paint_cite->drawEllipse(pixel_x,pixel_y,15,15);
        paint_cite->end();
        image_cite = image_cite.scaled(this->map->size(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
        scene->setBackgroundBrush(image_cite);
        image_cite.load("cite.bmp");
        paint_cite->begin(&image_cite);
    }
    qDebug()<<"longitude: "<<x;
    qDebug()<<"latitude: "<<y;

    qDebug()<<"pixel_x: "<<pixel_x;
    qDebug()<<"pixel_y: "<<pixel_y;
    //affiche la map
    map->show();
}

void MCircuit::SetCircuit(int circuit)
{
    //change la map du circuit en fonction de celle que l'on a choisi
    if(circuit == 0)
    {
        scene->setBackgroundBrush(image_lemans);
        choix = 0;
    }
    else if(circuit == 1)
    {
        scene->setBackgroundBrush(image_carole);
        choix = 1;
    }
    else if(circuit == 2)
    {
        scene->setBackgroundBrush(image_lecastelet);
        choix = 2;
    }
    else if(circuit == 3)
    {
        scene->setBackgroundBrush(image_cite);
        scene->setSceneRect(image_cite.rect());
        choix = 3;
    }
}


