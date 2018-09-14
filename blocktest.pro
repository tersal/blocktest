TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    src/utils/types.cpp \
    main.cpp

DISTFILES += \
    README.md \
    Makefile \
    README.md

SUBDIRS += \
    blocktest.pro

HEADERS += \
    src/base/transaction.h \
    src/utils/serialize.h \
    src/utils/types.h

INCLUDEPATH += \
    /usr/local/boost/include
