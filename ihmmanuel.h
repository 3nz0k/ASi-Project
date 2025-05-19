#ifndef IHMMANUEL_H
#define IHMMANUEL_H

#include <QDialog>
#include "controllerasi.h"
#include "gestiondonneesasi.h"

namespace Ui
{
    class IhmManuel;
}

class IhmManuel : public QDialog
{
    Q_OBJECT

    private:
        Ui::IhmManuel *ui;
        ControllerASi *mcasi;
        GestionDonneesAsi *mrefgda;
        int position;

    private slots:
        void Dposition();
        void Fermeture();
        void Ouverture();
        void TrPos();

    public:
        explicit IhmManuel(QWidget *parent = nullptr);
        ~IhmManuel();
        void msetRefGDA(GestionDonneesAsi *);



};

#endif // IHMMANUEL_H
