#ifndef IHMAUTO_H
#define IHMAUTO_H

#include <QDialog>
#include <QtWidgets>
#include "acquisition.h"

namespace Ui
{
    class IhmAuto;
}

class IhmAuto : public QDialog
{
    Q_OBJECT

    private:
        Ui::IhmAuto *ui;
        acquisition *acq;
        GestionDonneesAsi *arefgda;

    private slots:

        void on_BoutonQuitAuto_clicked();
        void demarrage();
        void SetDpos();
        void SetTpos();
        void setNbCycles();
        void on_Bdemarrage_clicked();
        void on_arretQt_clicked();

    public:
        explicit IhmAuto(QWidget *parent = nullptr);
        ~IhmAuto();
        void asetRefGDA(GestionDonneesAsi *);
};

#endif // IHMAUTO_H
