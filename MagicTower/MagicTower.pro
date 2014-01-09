#-------------------------------------------------
#
# Project created by QtCreator 2013-12-10T18:51:05
#
#-------------------------------------------------

QT += core gui
QT += multimedia
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagicTower
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    magicobject.cpp \
    magicsoundobject.cpp \
    magicbacksound.cpp \
    magicmap.cpp \
    MagicExpression/magicexpression.cpp \
    MagicExpression/magicassignment.cpp \
    MagicExpression/magiccondition.cpp \
    MagicExpression/magicvarient.cpp \
    MagicExpression/magicgoto.cpp \
    MagicExpression/magicoperand.cpp \
    MagicExpression/magicoperation.cpp \
    MagicExpression/magicreference.cpp \
    MagicAnimate/magicanimate.cpp \
    MagicDisplayObject/magicdisplayobject.cpp \
    MagicDisplayObject/magicfloor.cpp \
    MagicDisplayObject/magictom.cpp \
    MagicDisplayObject/magicwall.cpp \
    MagicAnimate/magicmove.cpp \
    MagicDisplayObject/magicenemy.cpp \
    MagicDisplayObject/magicstairs.cpp \
    MagicDisplayObject/magicdoor.cpp \
    MagicDisplayObject/magicinventory.cpp \
    MagicDisplayObject/magickey.cpp

HEADERS  += mainwindow.h \
    widget.h \
    magicobject.h \
    magicsoundobject.h \
    magicbacksound.h \
    magicmap.h \
    MagicExpression/magicexpression.h \
    MagicExpression/magicassignment.h \
    MagicExpression/magiccondition.h \
    MagicExpression/magicvarient.h \
    MagicExpression/magicgoto.h \
    MagicExpression/magicoperand.h \
    MagicExpression/magicoperation.h \
    MagicExpression/magicreference.h \
    MagicAnimate/magicanimate.h \
    MagicDisplayObject/magicdisplayobject.h \
    MagicDisplayObject/magicfloor.h \
    MagicDisplayObject/magictom.h \
    MagicDisplayObject/magicwall.h \
    MagicAnimate/magicmove.h \
    MagicDisplayObject/magicenemy.h \
    MagicDisplayObject/magicstairs.h \
    MagicDisplayObject/magicdoor.h \
    MagicDisplayObject/magicinventory.h \
    MagicDisplayObject/magickey.h

RESOURCES += \
    assets.qrc \
    maps.qrc
