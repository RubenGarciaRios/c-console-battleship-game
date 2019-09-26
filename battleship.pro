TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    utils.c \
    printers.c \
    game.c

HEADERS += \
    definitions.h \
    utils.h \
    printers.h \
    game.h

DISTFILES += \
    templates/main_menu.txt
