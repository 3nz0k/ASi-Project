#include "ihmtag.h"
#include "ui_ihmtag.h"
#include "nfccontroller.h"
#include <QtDebug>
#include <iostream>

ihmTag::ihmTag(QWidget *parent) : QDialog(parent), ui(new Ui::ihmTag)
{
    ui->setupUi(this);
    nfc = new NfcController;
    connect(ui->LireTag, SIGNAL(clicked()),this, SLOT(LireTag()));
}

ihmTag::~ihmTag()
{
    delete nfc;
    delete ui;
}

void ihmTag::LireTag()
{
    uint8_t profilBlock = 0x04;
    uint8_t posBlock = 0x05;
    uint8_t desBlock = 0x06;

    nfc->connectCard();
    nfc->loadKey();
    nfc->auth(profilBlock);
    ui->Profil->setText(nfc->getData(profilBlock));
    nfc->auth(posBlock);
    ui->Type->setText(nfc->getData(posBlock));
    nfc->auth(desBlock);
    ui->Adresse->setText(nfc->getData(desBlock));
}

