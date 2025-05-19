#ifndef IHMPROFILRFID_H
#define IHMPROFILRFID_H

#include <QDialog>
#include "nfccontroller.h"

namespace Ui {
class IhmProfilRFID;
}

class IhmProfilRFID : public QDialog
{
    Q_OBJECT

public:
    explicit IhmProfilRFID(QWidget *parent = nullptr);
    ~IhmProfilRFID();

private slots:
    void Ctag();

private:
    Ui::IhmProfilRFID *ui;
    NfcController *nfc;
};


#endif // IHMPROFILRFID_H
