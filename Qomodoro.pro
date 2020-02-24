QT += core gui widgets charts
TARGET = Qomodoro
CONFIG += c++14

# This flag is to make sure ubuntu creates an executable and not a shared object
QMAKE_LFLAGS += -no-pie

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES  += src/main.cpp \
            src/MainWindow.cpp \
            src/Pomodoro.cpp \
            src/DataIO.cpp \
            src/TimeLabel.cpp \
            src/StatsWindow.cpp \
            src/TimerWindow.cpp \
            src/charts/WeekChart.cpp \
            src/charts/DayChart.cpp
	
HEADERS  += include/main.h \
            include/MainWindow.h \
            include/Pomodoro.h \
            include/DataIO.h \
            include/TimeLabel.h \
            include/StatsWindow.h \
            include/TimerWindow.h \
            include/charts/WeekChart.h \
            include/charts/DayChart.h \
            include/nlohmann/json.hpp

FORMS    += ui/mainwindow.ui \
            ui/StatsWindow.ui \
            ui/TimerWindow.ui

RC_ICONS = images/icon.ico

target.path = ./install
INSTALLS += target








