#include "ihmprofilrfid.h"
#include "ui_ihmprofilrfid.h"

IhmProfilRFID::IhmProfilRFID(QWidget *parent) : QDialog(parent), ui(new Ui::IhmProfilRFID)
{
    ui->setupUi(this);
    nfc = new NfcController;

    setWindowTitle("Création d'un tag RFID");
    connect(ui->Ctag, SIGNAL(clicked()),this, SLOT(Ctag()));
}

void IhmProfilRFID::Ctag()
{
    uint8_t profilBlock = 0x04;
    QString qprofil = ui->lineEditProfil->text();
    std::string profil = qprofil.toStdString();
    BYTE valProfil[16] = {0}; // Initialiser un tableau de 16 bytes (taille d'un bloc NFC)
    std::copy(profil.begin(), profil.end(), valProfil); // Copier la chaîne dans le tableau

    uint8_t posBlock = 0x05;
    QString qpos = ui->lineEditPos->text();
    std::string pos = qpos.toStdString();
    BYTE valPos[16] = {0}; // Initialiser un tableau de 16 bytes (taille d'un bloc NFC)
    std::copy(pos.begin(), pos.end(), valPos); // Copier la chaîne dans le tableau

    uint8_t desBlock = 0x06;
    QString qdes = ui->lineEditDes->text();
    std::string des = qdes.toStdString();
    BYTE valDes[16] = {0}; // Initialiser un tableau de 16 bytes (taille d'un bloc NFC)
    std::copy(des.begin(), des.end(), valDes); // Copier la chaîne dans le tableau

    nfc->connectCard();
    nfc->loadKey();
    nfc->auth(profilBlock);
    nfc->setData(profilBlock, valProfil, sizeof (valProfil));

    nfc->auth(posBlock);
    nfc->setData(posBlock, valPos, sizeof (valPos));

    nfc->auth(desBlock);
    nfc->setData(desBlock, valDes, sizeof (valDes));
}

IhmProfilRFID::~IhmProfilRFID()
{
    delete ui;
    delete nfc;
}
