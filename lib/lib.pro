TEMPLATE = lib

TARGET = AmazingAPI

CONFIG += staticlib

#Input
HEADERS += $$PWD/file_reader/IFileReader.h
HEADERS += $$PWD/file_reader/CsvReader.h
HEADERS += $$PWD/objects/IObjects.h
HEADERS += $$PWD/objects/Items.h
HEADERS += $$PWD/objects/Discounts.h
HEADERS += $$PWD/objects/Orders.h
HEADERS += $$PWD/objects/ProcessedOrders.h

SOURCES += $$PWD/file_reader/IFileReader.cc
SOURCES += $$PWD/file_reader/CsvReader.cc
SOURCES += $$PWD/objects/Items.cc
SOURCES += $$PWD/objects/Discounts.cc
SOURCES += $$PWD/objects/Orders.cc
SOURCES += $$PWD/objects/ProcessedOrders.cc
