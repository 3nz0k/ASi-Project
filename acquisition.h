#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <QObject>
#include <QThread>
#include "controllerasi.h"
#include "gestiondonneesasi.h"

class acquisition : public QThread
{
    Q_OBJECT

    private:
        ControllerASi *acasi;
        bool dPos;
        int nbCycles;

        QString profil;
        int indice;
        int address;
        int sensorPos;

        int dPosCmd;
        int tPosCmd;
        int posInterCmd;

    signals:
        void miseAJIHM();

    public:
        acquisition();
        ~acquisition();
        void run();
        void setDpos(bool);
        void setNbCycles(int);

        int getIndice();
        void setIndice(int);

        int getAddress();
        void setAddress(int);

        QString getProfil();
        void setProfil(QString);

        int getSensorPos();
        void setSensorPos(int);

        int getdPos();
        void setdPos(int);

        int gettPos();
        void settPos(int);

        int getposInter();
        void setposInter(int);

};

#endif // ACQUISITION_H
