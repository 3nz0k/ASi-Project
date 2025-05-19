#ifndef IHMEXPORTER_H
#define IHMEXPORTER_H

#include <QDialog>
#include <QtPrintSupport/QPrinter>
#include <QCoreApplication>
#include <QFileDialog>
#include <QApplication>
#include <QMessageBox>


namespace Ui {
class IhmExporter;
}

class IhmExporter : public QDialog
{
    Q_OBJECT

public:
    explicit IhmExporter(QWidget *parent = nullptr);
    ~IhmExporter();
    void printer();

private slots:
    void ouvrirPdf();

private:
    Ui::IhmExporter *ui;
    QPrinter *pdf;
   // QString *filename;
};

#endif // IHMEXPORTER_H
