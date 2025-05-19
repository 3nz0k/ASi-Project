#include "ihmauto.h"
#include "ui_ihmauto.h"
#include <QDebug>
#include "acquisition.h"

IhmAuto::IhmAuto(QWidget *parent) : QDialog(parent), ui(new Ui::IhmAuto)
{
    ui->setupUi(this);
    acq = new acquisition;

    setWindowTitle("Test Automatique");
    connect(ui->dpos, SIGNAL(clicked()), this, SLOT(SetDpos()));
    connect(ui->tpos, SIGNAL(clicked()), this, SLOT(SetTpos()));
    ui->Bdemarrage->setDisabled(true);
    ui->NbCycles->addItem("1");
    ui->NbCycles->addItem("2");
    ui->NbCycles->addItem("5");
    ui->NbCycles->addItem("10");
    ui->NbCycles->addItem("20");
}

void IhmAuto::asetRefGDA(GestionDonneesAsi *igda)
{
    arefgda = igda;
}

void IhmAuto::SetDpos()
{
   acq->setDpos(true);
   ui->Bdemarrage->setEnabled(true);
   connect(ui->Bdemarrage, SIGNAL(clicked()), this, SLOT(demarrage()));
}


void IhmAuto::SetTpos()
{
     acq->setDpos(false);
     ui->Bdemarrage->setEnabled(true);
    connect(ui->Bdemarrage, SIGNAL(clicked()), this, SLOT(demarrage()));
}

void IhmAuto::setNbCycles()
{

}

IhmAuto::~IhmAuto()
{
    delete ui;
    delete acq;
}

void IhmAuto::on_BoutonQuitAuto_clicked()
{
    acq->terminate();
    ui->dpos->setEnabled(true);
    ui->tpos->setEnabled(true);
    close();
}

void IhmAuto::demarrage()
{
    //qDebug() << Q_FUNC_INFO;
    //qDebug()<<ui->NbCycles->currentText().toInt();
    acq->setNbCycles(ui->NbCycles->currentText().toInt());  //récupérer la valeur saisie dans l'IHM à faire SetCycles

    acq->setAddress(arefgda->getAddress());
    acq->setIndice(arefgda->getIndice());
    acq->setProfil(arefgda->getProfil());
    acq->setSensorPos(arefgda->getSensorPos());

    acq->start();
    ui->dpos->setEnabled(false);
    ui->tpos->setEnabled(false);
}

void IhmAuto::on_Bdemarrage_clicked()
{

}

void IhmAuto::on_arretQt_clicked()
{
    acq->terminate();
    ui->dpos->setEnabled(true);
    ui->tpos->setEnabled(true);
}
