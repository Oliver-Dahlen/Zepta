QT -= gui
QT += widgets
QT += network
QMAKE_CXXFLAGS += -DNDEBUG -g2 -O3

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += console
CONFIG += x86
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        client.cpp \
        loginscreen.cpp \
        main.cpp \
        rsa.cpp

TRANSLATIONS += \
    MoonShine_sv_SE.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    client.h \
    loginscreen.h \
    rsa.h

RESOURCES += \
    Resource.qrc




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Skrivbord/openssl/arm64-v8a/lib/ -lcrypto
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Skrivbord/openssl/arm64-v8a/lib/ -lcryptod
else:unix: LIBS += -L$$PWD/../../Skrivbord/openssl/arm64-v8a/lib/ -lcrypto

INCLUDEPATH += $$PWD/../../Skrivbord/openssl/arm64-v8a/include
DEPENDPATH += $$PWD/../../Skrivbord/openssl/arm64-v8a/include



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../Skrivbord/openssl/x86_64/lib/ -lcrypto
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../Skrivbord/openssl/x86_64/lib/ -lcryptod
else:unix: LIBS += -L$$PWD/../../Skrivbord/openssl/x86_64/lib/ -lcrypto

INCLUDEPATH += $$PWD/../../Skrivbord/openssl/x86_64/include
DEPENDPATH += $$PWD/../../Skrivbord/openssl/x86_64/include
