#ifndef NFCCONTROLLER_H
#define NFCCONTROLLER_H
#include "winscard.h"
#include <iostream>
#include <vector>
#include <QString>


class NfcController
{
private:
    SCARDCONTEXT hContext;
    SCARDHANDLE hCard;
    DWORD activeProtocol;
    LONG err;
    char readers[256];
    BYTE response[18];
    DWORD responseLen;
    QString cleanResponse;
    BYTE uid[4];

public:
    NfcController();
    ~NfcController();
    QString getData(uint8_t blockNumber);
    int setData(BYTE blockNumber, BYTE* value, int valueLength);
    int connectCard();
    BYTE* getUID();
    int loadKey();
    int auth(uint8_t blockNumber);

};

#endif // NFCCONTROLLER_H
