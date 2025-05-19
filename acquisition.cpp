#include "acquisition.h"
#include "QDebug"



acquisition::acquisition()
{
    acasi = new ControllerASi;
}

void acquisition::setNbCycles(int icycles)
{
    nbCycles = icycles;
}

int acquisition::getIndice()
{
    return indice;
}

void acquisition::setIndice(int iindice)
{
    indice = iindice;
}

int acquisition::getAddress()
{
    return address;
}

void acquisition::setAddress(int iaddress)
{
    address = iaddress;
}

QString acquisition::getProfil()
{
    return profil;
}

void acquisition::setProfil(QString iprofil)
{
    profil = iprofil;
}

int acquisition::getSensorPos()
{
    return sensorPos;
}

void acquisition::setSensorPos(int isensor)
{
    sensorPos = isensor;
}

void acquisition::setDpos(bool ipos)
{
    dPos = ipos;
}

int acquisition::getdPos()
{
    return dPosCmd;
}

void acquisition::setdPos(int idPos)
{
    dPosCmd = idPos;
}

int acquisition::gettPos()
{
    return tPosCmd;
}

void acquisition::settPos(int itPos)
{
    tPosCmd = itPos;
}

int acquisition::getposInter()
{
    return posInterCmd;
}

void acquisition::setposInter(int iposInter)
{
    posInterCmd = iposInter;
}

void acquisition::run()
{
    //qDebug() << Q_FUNC_INFO;
    while(nbCycles > 0 && dPos == true)
    {
        //qDebug() << "Debut d'un cycle";
        acasi->openDistributor(indice, dPosCmd);
        sleep(3);
        nbCycles--;
        acasi->closeDistributor(indice);
        sleep(3);
        //qDebug() << "Fin d'un cycle";
        //qDebug() << "nbCy : " << nbCycles;
    }

    while(nbCycles > 0 && dPos == false)
    {
        //qDebug() << "Debut du cycle 3 pos";
        acasi->openDistributor(indice, acasi->startBits(profil, 3));

        sleep(3);

        acasi->getPosDistributor(indice);
        acasi->closeDistributor(indice);
        int pos = 0;
        do
        {
            pos = acasi->getPosDistributor(sensorPos);
            //qDebug() << pos;
        }
        while (pos == 0);
        acasi->openDistributor(indice, 4);

        sleep(3);

        acasi->closeDistributor(indice);
        sleep(3);
        nbCycles--;
        //qDebug() << "Fin d'un cycle";
        //qDebug() << "nbCy=" << nbCycles;
    }
}


acquisition::~acquisition()
{
    delete acasi;
}

