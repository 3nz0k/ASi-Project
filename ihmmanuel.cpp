#include "ihmmanuel.h"
#include "ui_ihmmanuel.h"
#include <QDebug>
#include <vector>
#include <iostream>

IhmManuel::IhmManuel(QWidget *parent) : QDialog(parent), ui(new Ui::IhmManuel)
{
    ui->setupUi(this);
    mcasi = new ControllerASi;

    setWindowTitle("Test Manuel");
    connect(ui->Ouvrir,SIGNAL(clicked()),this, SLOT(Ouverture()));
    connect(ui->Fermer,SIGNAL(clicked()),this, SLOT(Fermeture()));
    connect(ui->Dmposition,SIGNAL(clicked()), this , SLOT(Dposition()));
    connect(ui->BPos, SIGNAL(clicked()), this, SLOT(TrPos()));
    ui->Dmposition->setDisabled(true);
    position = 2;
}

void IhmManuel::TrPos()
{
    ui->Dmposition->setDisabled(false);
    position = 3;
}

void IhmManuel::msetRefGDA(GestionDonneesAsi *igda)
{
    mrefgda = igda;
}

void IhmManuel::Ouverture()
{
    if(position == 2)
    {
        mcasi->openDistributor(mrefgda->getIndice(), mrefgda->getdPos());
    }
    else if(position == 3)
    {
        mcasi->openDistributor(mrefgda->getIndice(), mrefgda->gettPos());
    }
}

 void IhmManuel::Dposition()
{
    if(position == 3)
    {
        mcasi->getPosDistributor(mrefgda->getIndice());
        mcasi->closeDistributor(mrefgda->getIndice());
        int pos = 0;
        do
        {
            pos = mcasi->getPosDistributor(mrefgda->getSensorPos());
            std::cout << pos << std::endl;
        }
        while (pos == 0);
        mcasi->openDistributor(mrefgda->getIndice(), mrefgda->getposInter());
    }
}

 void IhmManuel::Fermeture()
 {
    mcasi->closeDistributor(mrefgda->getIndice());
 }

 IhmManuel::~IhmManuel()
 {
     delete mrefgda;
     delete mcasi;
     delete ui;
 }
