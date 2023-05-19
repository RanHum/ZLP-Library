QT += core gui widgets network

CONFIG += c++17 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bigwindow.cpp \
    book_container.cpp \
    book_form.cpp \
    doska.cpp \
    form.cpp \
    full.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    requests.cpp \
    api_utils.cpp

HEADERS += \
    bigwindow.h \
    book_container.h \
    book_form.h \
    doska.h \
    form.h \
    full.h \
    mainwindow.h \
    profile.h \
    requests.h \
    api_utils.h

FORMS += \
    bigwindow.ui \
    book_container.ui \
    book_form.ui \
    desk.ui \
    doska.ui \
    form.ui \
    full.ui \
    mainwindow.ui \
    profile.ui

TRANSLATIONS += \
    FirstTry_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
