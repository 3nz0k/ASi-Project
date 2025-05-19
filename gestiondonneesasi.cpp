#include "gestiondonneesasi.h"

GestionDonneesAsi::GestionDonneesAsi()
{

}

QString GestionDonneesAsi::getProfil()
{
    return profil;
}

void GestionDonneesAsi::setProfil(QString iprofil)
{
    profil = iprofil;
}

int GestionDonneesAsi::getAddress()
{
    return address;
}

void GestionDonneesAsi::setAddress(int iaddress)
{
    address = iaddress;
}

int GestionDonneesAsi::getSensorPos()
{
    return sensorPos;
}

void GestionDonneesAsi::setSensorPos(int pos)
{
    sensorPos = pos;
}

int GestionDonneesAsi::getIndice()
{
    return indice;
}

void GestionDonneesAsi::setIndice(int iindice)
{
    indice = iindice;
}

int GestionDonneesAsi::getdPos()
{
    return dPos;
}

void GestionDonneesAsi::setdPos(int idPos)
{
    dPos = idPos;
}

int GestionDonneesAsi::gettPos()
{
    return tPos;
}

void GestionDonneesAsi::settPos(int itPos)
{
    tPos = itPos;
}

int GestionDonneesAsi::getposInter()
{
    return posInter;
}

void GestionDonneesAsi::setposInter(int iposInter)
{
    posInter = iposInter;
}
