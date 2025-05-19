#include "controllerasi.h"
#include <iostream>

ControllerASi::ControllerASi()
{
    ODI[32] = {0};
    IDI[32] = {0};

    errorCode = AASiRegisterMaster(&masterId);
    if (errorCode != 0)
    {
        std::cerr << "Erreur : Impossible d'enregistrer le Master ASi" << std::endl; //Afficher l'erreur
    }

    std::cout << "Master enregistre avec l'ID : " << masterId << std::endl;//Afficher l'id du master

    errorCode = AASiInit(masterId, NULL);
    if (errorCode != 0)
    {
        std::cerr << "Erreur : Impossible d'initialiser le driver AS-i." << std::endl;
        AASiExit(masterId);
    }

    errorCode = AASiGetDriverName(masterId, &driverName, TRUE);
    if (errorCode != 0)
    {
        std::cerr << "Erreur : Aucun driver ASi selectionne." << std::endl;
        AASiExit(masterId);
    }
    else
    {
        std::cout << "Driver AS-Interface actif : " << driverName << std::endl;
    }
}

std::string ControllerASi::decToBin(int nombre)
{
    std::string reponse = "";
    // Si le nombre est 0, on renvoie 0
    if (nombre == 0)
    {
        return "0";
    }
    // Division par 2 jusqu'à ce que le nombre devienne 0
    while (nombre > 0)
    {
        reponse = std::to_string(nombre % 2) + reponse;  // Ajouter le reste de la division dans reponse
        nombre = nombre / 2;  // Diviser par 2
    }
    return reponse;
}

std::string ControllerASi::decToHexa(int nombre)
{
    std::string reponse = "";

    while (nombre != 0)
    {
        int reste = 0;
        char ch;
        reste = nombre % 16;
        if (reste < 10) ch = reste + 48;
        else
        {
            ch = reste + 55;
        }
        reponse += ch;
        nombre = nombre / 16;
    }
    return reponse;
}

std::vector <AASiSlaveList> ControllerASi::getSlave()
{
    AASiSlaveList lds;
    std::string bitsSlave;
    errorCode = AASiReadLDS(masterId, &lds);

    if (errorCode == 0)
    {
        bitsSlave = decToBin(lds);
        bitsSlave = "0" + bitsSlave.substr(0, bitsSlave.size() - 1);
        int j = 0;

        for (int i = bitsSlave.size(); i >= 0; i--)
        {
            if (bitsSlave[i] == '1') vecSlaveList.push_back(j);
            j++;
        }
        std::cout << vecSlaveList.size() << std::endl;
    }
    return vecSlaveList;
}

std::string ControllerASi::getProfil(std::vector <AASiSlaveList> vecSlaveList, int num)
{
    AASiConfigData FAR CDI;
    AASiReadCDI(masterId, vecSlaveList[num], &CDI);
    profil = decToHexa(CDI);
    profil = profil[0];
    return profil;
}

void ControllerASi::openDistributor(int indice, int cmd)
{
    ODI[indice] = cmd;
    std::cout<< "Ouverture des vannes"<<std::endl;
    AASiWriteODI(masterId, ODI, 0, 64);
}

void ControllerASi::closeDistributor(int indice)
{
    ODI[indice] = 0x0;
    std::cout << "Fermeture des vannes" << std::endl;
    AASiWriteODI(masterId, ODI, 0, 64);

}

int ControllerASi::calculIndice(std::vector <AASiSlaveList> vecSlaveList, int num)
{
    std::cout << "Calcul de l'indice du distributeur : " << vecSlaveList[num] << std::endl;

    int div = vecSlaveList[num] / 2;

    //std::cout << "Le resultat de la division est : " << div << std::endl;
    if ((vecSlaveList[num] % 2) == 0)
    {
        int indice = div;
        std::cout << "Le total est : " << indice << std::endl;
        return indice;
    }
    else
    {
        int mod = vecSlaveList[num] % 2;
        //std::cout << "Le resultat du modulo est : " << mod << std::endl;
        int indice = div + mod - 1;
        std::cout << "Le total est : " << indice << std::endl;
        return indice;
    }
}

unsigned char ControllerASi::getPosDistributor(int indice)
{
    AASiEcFlags EcFlags;
    AASiReadIDI(masterId, IDI, 0, 62, &EcFlags);
    position = IDI[indice];
    return position;
}

void ControllerASi::changeAddress(int num, AASiSlaveList newAddress)
{
    AASiAddressSlave(masterId, vecSlaveList[num], newAddress);

    vecSlaveList[num] = newAddress;

    std::cout << "La nouvelle adresse est : " << vecSlaveList[num] << std::endl;

    std::cout<<"Les adresses des esclaves sont : ";
    for (unsigned int i = 0; i < vecSlaveList.size(); i++)
    {
        std::cout << std::dec << vecSlaveList[i] << " ";
    }
    std::cout << std::endl;
}

int ControllerASi::startBits(QString qprofil, int pos)
{
    if (qprofil == "3")
    {
        if (pos == 2) return 8;
        else if (pos == 3) return 12;
    }
    if (qprofil == "7")
    {
        if (pos == 2) return 1;
    }
    return 0;
}

ControllerASi::~ControllerASi()
{
    AASiExit(masterId);
    std::cout << "AS-Interface Deconnecte." << std::endl;
}
