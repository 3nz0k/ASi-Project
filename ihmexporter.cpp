#include "ihmexporter.h"
#include "ui_ihmexporter.h"
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>

IhmExporter::IhmExporter(QWidget *parent) : QDialog(parent), ui(new Ui::IhmExporter)
{
    ui->setupUi(this);
    pdf = new QPrinter;
    setWindowTitle("Exporter le fichier");

    connect(ui->exporter, SIGNAL(clicked()),this, SLOT(ouvrirPdf()));
}


void IhmExporter::ouvrirPdf()
{
    /*QPdfWriter writer;
    writer.setPageSize(QPagedPaintDevice::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 12));

    painter.drawText(r, Qt::AlignRight, "Bonjour");
    painter.end();



    QString pdf = QFileDialog::getSaveFileName(nullptr, ("Enregistrer sous"), "", "Fichier PDF (*.pdf)Tous les fichiers");

    //if (!filename->isEmpty())
    {
        // QMessageBox::information(nullptr, "Fichier Sélectionné", "Vous avez choisi : " + pdf);
        //else QMessageBox::information(nullptr,"")
    }*/

}


IhmExporter::~IhmExporter()
{
    delete ui;
    delete pdf;
    //delete filename;
}
