QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Product.cpp \
    addsalerecorddialog.cpp \
    changesalesrecorddialog.cpp \
    deletedialog.cpp \
    informationdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    managewidget.cpp \
    salesrecord.cpp \
    salewidget.cpp \
    updatedialog.cpp \
    widget.cpp

HEADERS += \
    Product.h \
    addsalerecorddialog.h \
    changesalesrecorddialog.h \
    deletedialog.h \
    informationdialog.h \
    mainwindow.h \
    managewidget.h \
    salesrecord.h \
    salewidget.h \
    updatedialog.h \
    widget.h

FORMS += \
    addsalerecorddialog.ui \
    changesalesrecorddialog.ui \
    deletedialog.ui \
    informationdialog.ui \
    mainwindow.ui \
    managewidget.ui \
    salewidget.ui \
    updatedialog.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    images.qrc
