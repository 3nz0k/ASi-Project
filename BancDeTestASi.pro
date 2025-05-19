QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport xml

CONFIG += c++11
LIBS += -lwinscard
unix|win32: LIBS += -L$$PWD/./ -lAsidrv32

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acquisition.cpp \
    controllerasi.cpp \
    ihmauto.cpp \
    ihmexporter.cpp \
    ihmmanuel.cpp \
    ihmprofilrfid.cpp \
    ihmtag.cpp \
    main.cpp \
    ihmprincipal.cpp \
    nfccontroller.cpp \
    gestiondonneesasi.cpp

HEADERS += \
    acquisition.h \
    controllerasi.h \
    ihmauto.h \
    ihmexporter.h \
    ihmmanuel.h \
    ihmprincipal.h \
    ihmprofilrfid.h \
    ihmtag.h \
    nfccontroller.h \
    gestiondonneesasi.h

FORMS += \
    ihmauto.ui \
    ihmexporter.ui \
    ihmmanuel.ui \
    ihmprincipal.ui \
    ihmprofilrfid.ui \
    ihmtag.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icones.qrc

DISTFILES += Asidrv32.lib \
            asipci2.dll \
    asidrv32.dll \
    asipci.dll \
    asidrv32.ini
