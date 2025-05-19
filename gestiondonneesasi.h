#ifndef GESTIONDONNEESASI_H
#define GESTIONDONNEESASI_H
#include <QString>


class GestionDonneesAsi
{
    private:
        QString profil;
        int address;
        int sensorPos;
        int indice;

        int dPos;
        int tPos;
        int posInter;

    public:
        GestionDonneesAsi();
        QString getProfil();
        void setProfil(QString);
        int getAddress();
        void setAddress(int);
        int getSensorPos();
        void setSensorPos(int);
        int getIndice();
        void setIndice(int);

        int getdPos();
        void setdPos(int);
        int gettPos();
        void settPos(int);
        int getposInter();
        void setposInter(int);

};

#endif // GESTIONDONNEESASI_H
