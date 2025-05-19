#include "nfccontroller.h"
#include <windows.h>
#include <winscard.h>
#include <iostream>
#include <string>
#include <QApplication>
#include "ihmprincipal.h"

int main(int argc,char* argv[])
{
    QApplication a(argc, argv);
    IhmPrincipal w;
    w.show();
    return a.exec();

}
