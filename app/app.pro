TEMPLATE = app

TARGET = AmazingOfflineShop

SOURCES += main.cc

LIBS += -L$$OUT_PWD/../lib -lAmazingAPI

INCLUDEPATH += $$PWD/../lib
