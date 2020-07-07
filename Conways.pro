TEMPLATE = app

QT += quick qml

CONFIG += qmltypes
QML_IMPORT_NAME = Conways
QML_IMPORT_MAJOR_VERSION = 1

SOURCES += \
        main.cpp \
    conways.cpp

RESOURCES += \
    main.qml

target.path = C:\Users\Eimantas\Documents\Conways
INSTALLS += target

HEADERS += \
    conways.h
