QT       += core widgets gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LilouCalc
TEMPLATE = app
INCLUDEPATH += .


unix:!macx {
    LIBS += -lgsl -lgslcblas
}
win32 {
#    LIBS += -L"C:\Program Files\GnuWin32\lib" -lgsl -lgslcblas
    LIBS += -L"C:\Program Files (x86)\GnuWin32\lib" -lgsl -lgslcblas
    INCLUDEPATH += "C:\Program Files (x86)\GnuWin32\include"
}

include(common.pri)
RESOURCES = RCalc.qrc

SOURCES += src/main.cpp\
    src/history.cpp \
    src/AboutDialog.cpp \
    src/mainwindow.cpp \
    src/skin.cpp \
    src/solve.cpp \
    src/dsettings.cpp \
    src/utils.cpp

HEADERS  += \
    src/Constants.h \
    src/history.h \
    src/AboutDialog.h \
    src/mainwindow.h \
    src/skin.h \
    src/solve.h \
    src/dsettings.h \
    math/cmath.h \
    math/cnumberparser.h \
    math/quantity.h \
    src/utils.h

FORMS    += \
    src/AboutDialog.ui \
    src/mainwindow.ui \
    src/solve.ui

DISTFILES += \
    .appveyor.yml \
    .gitignore \
    .travis.yml \
    LICENSE \
    README.md \
    liloucalc.png \
    setup_appveyor.bat
