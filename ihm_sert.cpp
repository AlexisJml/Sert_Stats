#include "ihm_sert.h"
#include "ui_ihm_sert.h"

ihm_sert::ihm_sert(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ihm_sert)
{
    ui->setupUi(this);
    ui->stop->setDisabled(true);

    //initialisation
    vitessemoy = 0.0;

    MonCircuit = new MCircuit(ui->map);

    Acquisition = new MAcquisition(this);

    db = new Archivage();

    //initialisation du signal (thread)
    connect(Acquisition,SIGNAL(Traitement(QString*)),this,SLOT(result(QString*)));

    //initialise le graphique
    MonGraph = new MGraphique(ui->graph);
    MonGraph->initialisation();
    ui->graph->replot();

    //vérifie l'état de conncetion avec la xBee
    if(Acquisition->etat())
    {
        ui->etat_xbee->setText("xBee Connecté");
        ui->etat_xbee->setStyleSheet("QLabel { color : #00FF00; }");
        ui->connexion_xbee->setDisabled(true);
    }
    else
    {
        ui->etat_xbee->setText("xBee Déconnecté");
        ui->etat_xbee->setStyleSheet("QLabel { color : #FF0000; }");
        ui->connexion_xbee->setDisabled(false);
        ui->start->setDisabled(true);
    }


    //initialise la jauge d'accéleromètre
    /*ui->accelero->setSource(QUrl(QStringLiteral("qrc:/gauge/gauge2.qml")));
    ui->accelero->show();

    //initialise la jauge de l'angle
    ui->angle->setSource(QUrl(QStringLiteral("qrc:/gauge/gauge.qml")));
    ui->angle->show();*/
}

ihm_sert::~ihm_sert()
{
    //arrêt du thread
    Acquisition->stop = true;
    Acquisition->terminate();

    MonGraph->~MGraphique();

    delete ui;
}

void ihm_sert::result(QString *data)
{
    //message d'erreur si il y a un problème avec la liaison xBee
    if(data[0] == "erreur")
    {
        QMessageBox erreur;
        erreur.setText("Veuillez vérifier la liasion xBee");
        erreur.exec();

        ui->start->setDisabled(true);
        ui->stop->setDisabled(false);
    }
    else
    {
        //récupère chaque données
        float eau = data[0].toFloat();
        float thuile = data[1].toFloat();
        float phuile = data[2].toFloat();
        float vitesse = data[3].toFloat();
        float regime = data[4].toFloat();
        float accelero = data[6].toFloat();
        float angle = data[9].toFloat();
        float longitude = data[10].toFloat();
        float latitude = data[11].toFloat();

        //calcul la moyenne de la vitesse
        if(vitessemoy==0.0)
        {
            vitessemoy = vitesse;
        }
        else
        {
            vitessemoy = (vitessemoy+vitesse)/2;
        }

        //envoi des données
        MonGraph->ajouter(eau, thuile,phuile);
        ui->graph->replot();

        //affiche les donnée de la vitesse et du régime moteur
        ui->vitesse_moyenne->setText(QString::number(vitessemoy) + " km/h");
        ui->vitesse->setText(QString::number(vitesse) + " km/h");
        ui->regime_moteur->setText(QString::number(regime) + " tr/min");

        //envoi les valeurs de l'angle et de l'accélèromètre
        //MonGraph->QmlValueChange(ui->accelero,accelero);
        //MonGraph->QmlValueChange(ui->angle,angle);

        //envoi la longitude et la latitude
        MonCircuit->SetPosition(longitude,latitude);

        //sauvegarde les données
        if(db->etat())
        {
            db->save(eau, thuile, phuile, vitesse, regime, accelero, angle, latitude, longitude);
        }
    }
}

void ihm_sert::on_start_clicked()
{
    //déclenche le thread
    ui->stop->setEnabled(true);
    ui->start->setDisabled(true);
    //lance le thread
    Acquisition->start();
    Acquisition->stop = false;
}

void ihm_sert::on_stop_clicked()
{
    //arrete le thread
    ui->start->setEnabled(true);
    ui->stop->setDisabled(true);
    //arrete le thread
    Acquisition->stop = true;
}

void ihm_sert::on_check_tempeau_stateChanged(int arg1)
{
    MonGraph->temp_eau_visible(arg1);
    ui->graph->replot();
}

void ihm_sert::on_check_temphuile_stateChanged(int arg1)
{
    MonGraph->temp_huile_visible(arg1);
    ui->graph->replot();
}

void ihm_sert::on_check_pressionhuile_stateChanged(int arg1)
{
    MonGraph->pression_huile_visible(arg1);
    ui->graph->replot();
}

void ihm_sert::on_valider_clicked()
{
    // 0 = Le Mans
    // 1 = Carole
    // 2 = Le Castelet
    //3 = cité scolaire
    //choix du circuit
    MonCircuit->SetCircuit(ui->combo_circuit->currentIndex());      //problème taille de la map
}

void ihm_sert::on_connexion_xbee_clicked()
{
    if(Acquisition->etat() == true)
    {
        ui->stop->setDisabled(true);
        ui->start->setDisabled(false);
        ui->connexion_xbee->setDisabled(true);
    }
    else
    {
        ui->stop->setDisabled(true);
        ui->start->setDisabled(true);
        ui->connexion_xbee->setDisabled(false);

        QMessageBox erreur;
        erreur.setText("Veuillez vérifier la liasion xBee");
        erreur.exec();
    }
}

void ihm_sert::on_button_BDD_clicked()
{
    QString ip = ui->adresseIP->toPlainText();
    QString user = ui->utilisateur->toPlainText();
    QString password = ui->motdepasse->toPlainText();
    QString table = ui->table->toPlainText();

    db->Connect(ip,user,password,table);

    if(db->etat())
    {
        ui->etat_BDD->setText("BDD Connecté");
        ui->etat_BDD->setStyleSheet("QLabel { color : #00FF00; }");
    }
    else
    {
        ui->etat_BDD->setText("BDD déconnecté");
        ui->etat_BDD->setStyleSheet("QLabel { color : #FF0000; }");
        QMessageBox erreur;
        erreur.setText("Veuillez vérifier les information pour accèder à la BDD");
        erreur.exec();
    }
}
