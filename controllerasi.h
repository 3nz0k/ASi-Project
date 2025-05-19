#ifndef CONTROLLERASI_H
#define CONTROLLERASI_H

#include <vector>
#include <string>
#include <QString>
#include "Aasidrv.h"
#include "Asidrv32.h"

class ControllerASi
{
    private:
        int masterId;
        int errorCode;
        unsigned char ODI[32];
        unsigned char IDI[32];
        std::vector <AASiSlaveList> vecSlaveList;
        std::string profil;
        LPCSTR driverName;
        unsigned char position;

    public:
        ControllerASi();
        ~ControllerASi();
        std::string decToBin(int);
        std::string decToHexa(int);
        int calculIndice(std::vector <AASiSlaveList>, int);

        std::string getProfil(std::vector <AASiSlaveList>, int);
        std::vector <AASiSlaveList> getSlave();
        void openDistributor(int, int);
        void closeDistributor(int);
        unsigned char getPosDistributor(int);
        void changeAddress(int, AASiSlaveList);
        int startBits(QString, int);
};

#endif // CONTROLLERASI_H
