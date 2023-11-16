QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
        ../libreria/encabezados.h\
        ../libreria/libreria_global.h\
        ../libreria/archivos.h\
        ../libreria/clases.h\
        ../libreria/clientes.h\
        ../libreria/libreria.h\
        ../libreria/musculito.h

SOURCES += \
        main.cpp\
        ../libreria/archivos.cpp\
        ../libreria/clases.cpp\
        ../libreria/clientes.cpp\
        ../libreria/libreria.cpp\
        ../libreria/musculito.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libreria/release/ -llibreria
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libreria/debug/ -llibreria
else:unix: LIBS += -L$$OUT_PWD/../libreria/ -llibreria

INCLUDEPATH += $$PWD/../libreria
DEPENDPATH += $$PWD/../libreria
