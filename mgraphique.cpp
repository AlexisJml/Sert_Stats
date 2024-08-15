#include "mgraphique.h"

MGraphique::MGraphique()
{
    graphique = new QCustomPlot();
    x = 0;
    min = 0.0;
    max = 0.0;
}

MGraphique::MGraphique(QCustomPlot *MonGraph)
{
    //constructeur copie
    graphique = MonGraph;
    x = 0;
    min = 0.0;
    max = 0.0;
}

void MGraphique::initialisation()
{
    //initialisation des variables
    QPen Pen0 ;
    QPen Pen1;
    QPen Pen2;
    QLinearGradient degrader;
    QCPLayoutGrid *legende = new QCPLayoutGrid;

    //défini la taille et la couleur des droites
    Pen0.setWidth(2);
    Pen0.setColor("cyan");
    Pen1.setWidth(2);
    Pen1.setColor("red");
    Pen2.setWidth(2);
    Pen2.setColor("green");

    //défini la couleur de l'arrière plan
    degrader.setStart(0,0);
    degrader.setFinalStop(0,200);
    degrader.setColorAt(0,QColor(100,100,100));
    degrader.setColorAt(1,QColor(50,50,50));
    graphique->setBackground(degrader);


    //défini la couleur des axes
    graphique->xAxis->setBasePen(QPen(Qt::white));
    graphique->yAxis->setBasePen(QPen(Qt::white));
    graphique->xAxis->setTickPen(QPen(Qt::white));
    graphique->yAxis->setTickPen(QPen(Qt::white));
    graphique->xAxis->setSubTickPen(QPen(Qt::white));
    graphique->yAxis->setSubTickPen(QPen(Qt::white));
    graphique->xAxis->setTickLabelColor(Qt::white);
    graphique->yAxis->setTickLabelColor(Qt::white);
    graphique->xAxis->grid()->setPen(QPen(QColor(140,140,140),1,Qt::DotLine));
    graphique->yAxis->grid()->setPen(QPen(QColor(140,140,140),1,Qt::DotLine));
    graphique->xAxis->grid()->setSubGridPen(QPen(QColor(140,140,140),1,Qt::DotLine));
    graphique->yAxis->grid()->setSubGridPen(QPen(QColor(140,140,140),1,Qt::DotLine));
    graphique->xAxis->grid()->setSubGridVisible(true);
    graphique->yAxis->grid()->setSubGridVisible(true);
    graphique->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    graphique->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    graphique->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    graphique->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    graphique->xAxis->setLabelColor(Qt::white);
    graphique->yAxis->setLabelColor(Qt::white);

    //affiche la légende
    graphique->legend->setFont(graphique->font());
    graphique->legend->setVisible(true);

    graphique->plotLayout()->addElement(1,0,legende);
    legende->setMargins(QMargins(2,0,2,2));
    legende->addElement(0,0,graphique->legend);
    graphique->legend->setFillOrder(QCPLegend::foColumnsFirst);
    graphique->plotLayout()->setRowStretchFactor(1,0.001);


    //création du graph et assignation des données
    graphique->addGraph();
    graphique->graph(0)->setPen(Pen0);      //graph 0 ==> température eau
    graphique->graph(0)->setName("température de l'eau");
    graphique->addGraph();
    graphique->graph(1)->setPen(Pen1);      //graph 1 ==> température huile
    graphique->graph(1)->setName("température d'huile");
    graphique->addGraph();
    graphique->graph(2)->setPen(Pen2);      //graph 2 ==> pression de l'huilde
    graphique->graph(2)->setName("pression de l'huile");


    //à chaque point de mesure fait un cercle
    graphique->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::cyan,1.5), QBrush(Qt::white),5));
    graphique->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::red,1.5), QBrush(Qt::white),5));
    graphique->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::green,1.5), QBrush(Qt::white),5));

    //donne des noms aux axe x et y
    graphique->xAxis->setLabel("temps en secondes");
    graphique->yAxis->setLabel("grandeur universelle");

    //ajoute le choix de zommer, et de naviguer librement sur le graphique
    graphique->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );

}

void MGraphique::ajouter(float tempeau,float temphuile,float pressionhuile)
{
    //ajout des nouvelles données
    graphique->graph(0)->addData(x,tempeau);
    graphique->graph(1)->addData(x,temphuile);
    graphique->graph(2)->addData(x,pressionhuile);

    //vérifie si les données sont plus grandes ou plus petites que les variables min et max
    if(min>tempeau)
    {
        min = tempeau;
    }
    else if(min>temphuile)
    {
        min = temphuile;
    }
    else if(min>pressionhuile)
    {
        min = pressionhuile;
    }
    if(max<tempeau)
    {
        max = tempeau;
    }
    if(max<temphuile)
    {
        max = temphuile;
    }
    if(max<pressionhuile)
    {
        max = pressionhuile;
    }

    //recalibre le graph en fonction des nouvelles valeurs
    graphique->xAxis->setRange(0,x+0.5);
    graphique->yAxis->setRange(min-1,max+1);

    x += 1;
}

MGraphique::~MGraphique()
{
    graphique->~QCustomPlot();
}

void MGraphique::temp_eau_visible(int val)
{
    if(val==2)
    {
        graphique->graph(0)->setVisible(true);
    }
    else
    {
        graphique->graph(0)->setVisible(false);
    }
}

void MGraphique::temp_huile_visible(int val)
{
    if(val==2)
    {
        graphique->graph(1)->setVisible(true);
    }
    else
    {
        graphique->graph(1)->setVisible(false);
    }
}
void MGraphique::pression_huile_visible(int val)
{
    if(val==2)
    {
        graphique->graph(2)->setVisible(true);
    }
    else
    {
        graphique->graph(2)->setVisible(false);
    }
}

void MGraphique::setQmlObjectValue(QQuickWidget* uiWidget, const char* childName, const char* propertyName, QVariant value)
{
    // Récupération de l'objet racine du fichier QML
    QObject* qmlObject = uiWidget->rootObject();

    // Recherche de l'élément QML enfant à modifier
    QObject* child = qmlObject->findChild<QObject*>(childName);

    // Si l'élément enfant a été trouvé
        if (child)
            // Modification de la valeur de la propriété
            child->setProperty(propertyName, value);
}

void MGraphique::QmlValueChange(QQuickWidget* widget,float value)
{
        // Si on modifie la valeur du Slider, on appel la méthode "setQmlObjectValue"
        setQmlObjectValue(widget, "gauge", "value", value);

}

