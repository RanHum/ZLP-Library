QT += core gui widgets network

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bigwindow.cpp \
    doska.cpp \
    form.cpp \
    full.cpp \
    main.cpp \
    mainwindow.cpp \
    requests.cpp

HEADERS += \
    bigwindow.h \
    doska.h \
    form.h \
    full.h \
    mainwindow.h \
    requests.h \
    api_utils.h

FORMS += \
    bigwindow.ui \
    doska.ui \
    form.ui \
    full.ui \
    mainwindow.ui

TRANSLATIONS += \
    FirstTry_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
