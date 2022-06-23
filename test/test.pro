TEMPLATE = app

TARGET = AmazingTests

SOURCES += test.cc
SOURCES += CsvReaderTest.cc
SOURCES += ItemsTest.cc
SOURCES += ProcessedOrdersTest.cc

LIBS += -L$$OUT_PWD/../lib -lAmazingAPI
LIBS += -lgtest -lgtest_main

INCLUDEPATH += $$PWD/../lib
