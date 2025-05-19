#ifndef IHMPRINCIPAL_H
#define IHMPRINCIPAL_H

#include <QMainWindow>
#include <QThread>
#include <ihmexporter.h>
#include <ihmmanuel.h>
#include <ihmexporter.h>
#include <ihmauto.h>
#include <ihmprofilrfid.h>
#include <QObject>
#include <QtXml/QDomDocument>
#include <ihmtag.h>
#include "controllerasi.h"
#include "gestiondonneesasi.h"

class vanne;
QT_BEGIN_NAMESPACE
namespace Ui { class IhmPrincipal; }
QT_END_NAMESPACE

class IhmPrincipal : public QMainWindow
{
    Q_OBJECT


    private:
        Ui::IhmPrincipal *ui;
        IhmExporter *Ihmex;
        IhmManuel *Ihmmanu;
        IhmAuto *Ihmauto;
        ihmTag *Ihmtag;
        IhmProfilRFID *Ihmprofil;
        QString texte;

        //AS-i
        ControllerASi *casi;
        GestionDonneesAsi *gasi;
        std::vector <AASiSlaveList> vec;


    private slots:
        void ouvrirIhmExporter();
        void ouvrirIhmManuel();
        void ouvrirIhmAuto();
        void ouvrirListe();
        void OuvrirIhmTag();
        void ouvrirCtag();
        void slaveId();


    public:
        IhmPrincipal(QWidget *parent = nullptr);
        ~IhmPrincipal();




};
#endif // IHMPRINCIPAL_H
