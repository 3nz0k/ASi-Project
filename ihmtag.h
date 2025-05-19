#ifndef IHMTAG_H
#define IHMTAG_H

#include <QDialog>
#include "nfccontroller.h"

namespace Ui {
class ihmTag;
}

class ihmTag : public QDialog
{
    Q_OBJECT

public:
    explicit ihmTag(QWidget *parent = nullptr);
    ~ihmTag();


private slots:
    void LireTag();



private:
    Ui::ihmTag *ui;
    NfcController *nfc;
};

#endif // IHMTAG_H
