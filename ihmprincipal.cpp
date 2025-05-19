#include "ihmprincipal.h"
#include "ui_ihmprincipal.h"
#include <QDebug>
#include <QDomDocument>

IhmPrincipal::IhmPrincipal(QWidget *parent) : QMainWindow(parent) , ui(new Ui::IhmPrincipal)
{
    ui->setupUi(this);
    gasi = new GestionDonneesAsi;    
    casi = new ControllerASi;
    Ihmex = new IhmExporter;
    Ihmmanu = new IhmManuel;
    Ihmmanu->msetRefGDA(gasi);
    Ihmauto = new IhmAuto;
    Ihmauto->asetRefGDA(gasi);
    Ihmtag = new ihmTag;
    Ihmprofil = new IhmProfilRFID;

    setWindowTitle("UPL - Banc de Test"); // Modifier le nom de la fênetre
    setWindowIcon(QIcon(":/img/UPL.png"));// Modifier le logo de la fênetre
    connect(ui->actiontest_automatique, SIGNAL(triggered()), this, SLOT(ouvrirIhmAuto()));
    connect(ui->actiontest_manuel, SIGNAL(triggered()), this, SLOT(ouvrirIhmManuel()));
    connect(ui->actionexportez, SIGNAL(triggered()), this, SLOT(ouvrirIhmExporter()));
    connect(ui->ActionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->BoutOuvrirFi, SIGNAL(clicked()), this, SLOT(ouvrirListe()));
    connect(ui->BtnLireTag, SIGNAL(clicked()),this, SLOT(OuvrirIhmTag()));
    connect(ui->BtnCtag,SIGNAL(clicked()),this, SLOT(ouvrirCtag()));
    connect(ui->slaveId, SIGNAL(clicked()), this, SLOT(slaveId()));
    ui->BoutOuvrirFi->setDisabled(true);
}

void IhmPrincipal::slaveId()
{
    ui->BoutOuvrirFi->setEnabled(true);
    vec = casi->getSlave();
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        gasi->setAddress(vec[i]);
        gasi->setProfil(QString::fromStdString(casi->getProfil(vec, i)));
        if (gasi->getProfil() == "B") gasi->setSensorPos(casi->calculIndice(vec, i));
        else gasi->setIndice(casi->calculIndice(vec, i));
    }
}

void IhmPrincipal::ouvrirIhmExporter()
{
    Ihmex ->setModal(true);
    Ihmex ->show();
}

void IhmPrincipal::ouvrirIhmManuel()
{
    Ihmmanu ->setModal(true);
    Ihmmanu ->show();

}

void IhmPrincipal::ouvrirIhmAuto()
{
    Ihmauto ->setModal(true);
    Ihmauto ->show();
}

void IhmPrincipal::OuvrirIhmTag()
{
    Ihmtag ->setModal(true);
    Ihmtag->show();
    ui->actionexportez->setEnabled(true);
}

void IhmPrincipal::ouvrirCtag()
{
    Ihmprofil->setModal(true);
    Ihmprofil->show();
}

void IhmPrincipal::ouvrirListe()
{
    //ui->ListeDis->setEnabled(true);
    QString FichierConf = QFileDialog::getOpenFileName(this, tr("Open File"),"","Fichier de configuration (*.xml)");
    if(FichierConf.isEmpty())
    {
        //qDebug() << "Aucun fichier selectionné";
        return;
    }

    QFile file(FichierConf);
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        //qDebug() << "impossible d'ouvrir le fichier";
        return;
    }

    QTextStream contenu(&file);
    texte = contenu.readAll();
    file.close();
    QDomDocument doc;
    QString errorMsg;
    int errorline, errorColumn;
    //qDebug() << "Texte:" << texte;
    if (!doc.setContent(texte, &errorMsg, &errorline, &errorColumn))
    {
        //qDebug() << "Erreur de parsing XML : " <<errorMsg << "Ligne : " << errorline << "colone : " << errorColumn;
        return;
    }

    QDomElement root = doc.documentElement();
    QDomNodeList items = root.childNodes();
    for (int i = 0;i <items.count(); ++i)
    {
        QDomNode itemNode = items.at(i);
        if (itemNode.isElement())
        {
            QDomElement profilElement = itemNode.toElement();
            if(profilElement.firstChildElement("num").text() == gasi->getProfil())
            {
                gasi->setdPos(profilElement.firstChildElement("ouvrir").firstChildElement("dPos").text().toInt());
                //qDebug() << "dPos : " << gasi->getdPos();
                gasi->settPos(profilElement.firstChildElement("ouvrir").firstChildElement("tPos").text().toInt());
                //qDebug() << "tPos : " << gasi->gettPos();
                gasi->setposInter(profilElement.firstChildElement("posInter").text().toInt());
                //qDebug() << "posInter : " << gasi->getposInter();
            }
        }
    }
}

IhmPrincipal::~IhmPrincipal()
{
    delete Ihmex; //Détruire l'instance de la classe IhmExporter
    delete Ihmmanu; //Détruire l'instance de la classe IhmManuel
    delete Ihmauto; //Détruire l'instance de la classe IhmAuto
    delete casi;
    delete gasi;
    delete Ihmtag;
    delete Ihmprofil;
    delete ui;
}



