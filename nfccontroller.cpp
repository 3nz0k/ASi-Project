#include "nfccontroller.h"
#include "winscard.h"
#include <iostream>
#include <vector>
#include <QString>

NfcController::NfcController()
{
    // Initialisation de la taille
    responseLen = sizeof(response);

    // Initialisation du contexte PC/SC
    err = SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &hContext);
    if (err != SCARD_S_SUCCESS)
    {
        std::cerr << "Echec de SCardEstablishContext: " << err << std::endl;
    }

    // Connexion au lecteur
    DWORD reader = sizeof(readers);
    err = SCardListReadersA(hContext, NULL, readers, &reader);
    if (err != SCARD_S_SUCCESS)
    {
        std::cerr << "Echec de SCardListReaders: " << err << std::endl;
    }
    else
    {
        std::cout << "Lecteur detecte : " << readers << std::endl;
    }
}

NfcController::~NfcController()
{
    // Liberation des ressources
    SCardDisconnect(hCard, SCARD_LEAVE_CARD);
    SCardReleaseContext(hContext);
}

int NfcController::connectCard()
{
    err = SCardConnectA(hContext, readers, SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &hCard, &activeProtocol);
    if (err != SCARD_S_SUCCESS)
    {
        std::cerr << "Echec de SCardConnect: " << err << std::endl;
        return -1;
    }
    else
    {
        std::cout << "Connexion reussie avec la carte !" << std::endl;
        return 0;
    }
}

BYTE* NfcController::getUID()
{
    BYTE apduGetUID[] = {0xff, 0xCA, 0x00, 0x00, 0x00}; // Commande APDU pour recuperer l'UID

    SCardTransmit(hCard, SCARD_PCI_T1, apduGetUID, sizeof(apduGetUID), NULL, response, &responseLen);

    if(response[responseLen-2] == 0x90 && response[responseLen-1] == 0x00)
    {
        std::cout << "UID de la carte : ";
        for (DWORD i = 0; i < responseLen - 2; i++) // On exclut SW1 SW2
        {
            //uid[i] += response[i];
        }
        return response;
    }
    else
    {
        std::cerr << "Echec lors de la lecture de l'UID de la carte !" << std::endl;
        return response;
    }
}

int NfcController::loadKey()
{
    BYTE loadKeyAPDU[] = {0xff,0x82,0x00,0x00,0x06,0xff,0xff,0xff,0xff,0xff,0xff};

    SCardTransmit(hCard, SCARD_PCI_T1, loadKeyAPDU, sizeof(loadKeyAPDU), NULL, response, &responseLen);

    if(response[0] == 0x90 && response[1] == 0x00)
    {
        std::cout << "Chargement de la clef reussi !" << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Echec lors du chargement de la clef !" << std::endl;
        return -1;
    }
}

int NfcController::auth(uint8_t blockNumber)
{
    BYTE authAPDU[] = {0xff, 0x86, 0x00, 0x00, 0x05, 0x01, 0x00, blockNumber, 0x60, 0x00};

    SCardTransmit(hCard, SCARD_PCI_T1, authAPDU, sizeof(authAPDU), nullptr, response, &responseLen);

    if(response[0] == 0x90 && response[1] == 0x00)
    {
        std::cout << "Authentification sur le bloc " << int(blockNumber) << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Echech de l'Authentification !" << std::endl;
        return -1;
    }
}

QString NfcController::getData(uint8_t blockNumber)
{
    BYTE readAPDU[] = {0xff, 0xb0, 0x00, blockNumber, 0x10};
    cleanResponse = "";

    responseLen = sizeof (response);
    DWORD adpuSize = sizeof(readAPDU);

    SCardTransmit(hCard, SCARD_PCI_T1, readAPDU, adpuSize, nullptr, response, &responseLen);

    if(response[responseLen-2] == 0x90 && response[responseLen-1] == 0x00)
    {
        std::cout << "--- LECTURE ---" << std::endl;
        printf("Code Bon : %02X %02X \n", response[responseLen-2], response[responseLen-1]);

        //std::cout << "Lecture du bloc " << int(blockNumber) << " : ";
        for (DWORD i = 0; i < responseLen - 2; i++)// On exclut SW1 SW2 donc on fait - 2
        {
            if(response[i] == 0x00) break;
            cleanResponse += response[i];
        }
        return cleanResponse;
    }
    else
    {
        std::cerr << "Erreur de lecture" << std::endl;
        cleanResponse = "NULL";
        return cleanResponse;
    }
}

int NfcController::setData(BYTE blockNumber, BYTE* value, int valueLength)
{
    if (valueLength > 16)
    {
        std::cerr << "La chaine de caractere est trop grande" << std::endl;
        return -1;
    }
    else
    {
        BYTE writeCommand[] = {0xFF, 0xD6, 0x00, blockNumber, 0x10};
        int respLen = sizeof(writeCommand) + valueLength;
        BYTE* fullWriteCommand = new BYTE[respLen];
        responseLen = sizeof (response);

        //memcpy(dest, source, taille);
        // Copier les 5 premiers octets de writeCommand dans fullWriteCommand
        memcpy(fullWriteCommand, writeCommand, sizeof(writeCommand));
        // Copier les octets de value dans fullWriteCommand après writeCommand
        memcpy(fullWriteCommand + sizeof(writeCommand), value, valueLength);

        // Envoyer la commande APDU
        SCardTransmit(hCard, SCARD_PCI_T1, fullWriteCommand, responseLen, nullptr, response, &responseLen);
        if(response[0] != 0x90 && response[1] != 0x00)
        {
            std::cerr << "Erreur lors de l'ecriture des donnes" << std::endl;
            return -1;
        }
        else
        {
            std::cout << "Ecriture des donnees sur le bloc " << std::endl;
            return 0;
        }
    }
}
