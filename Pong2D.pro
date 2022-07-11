greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    src/ball.h \
    src/game.h \
    src/gamescene.h \
    src/paddle.h \
    src/view.h

SOURCES += \
    src/ball.cpp \
    src/game.cpp \
    src/gamescene.cpp \
    src/main.cpp \
    src/paddle.cpp \
    src/view.cpp \


QT += widgets

RESOURCES += \
    resource.qrc
