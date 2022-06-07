TEMPLATE = subdirs

SUBDIRS += lib
SUBDIRS += test
SUBDIRS += app

CONFIG += ordered

test.depends = lib
app.depends = lib
