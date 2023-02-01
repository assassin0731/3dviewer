QT       += core gui opengl openglwidgets gifimage
include(../src/QtGifImage/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/Qt-files/main.cpp \
    ../src/Qt-files/mainwidget.cpp \
    ../src/C-files/myMain.c \
    ../src/Qt-files/widget.cpp

HEADERS += \
    ../src/Qt-files/mainwidget.h \
    ../src/C-files/myMain.h \
    ../src/Qt-files/static.h \
    ../src/Qt-files/widget.h

FORMS += \
    ../src/Qt-files/widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../src/Resources/MyResource.qrc


