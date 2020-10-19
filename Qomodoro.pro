QT += core gui widgets charts
TARGET = Qomodoro
CONFIG += c++14
VERSION = 0.2.1

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
            src/TopBarTitle.cpp \
            src/Pomodoro.cpp \
            src/DataIO.cpp \
            src/StatsWindow.cpp \
            src/OptionsWindow.cpp \
            src/CircularTimer.cpp \
            src/charts/WeekChart.cpp \
            src/charts/DayChart.cpp
	
HEADERS  += include/MainWindow.h \
            include/TopBarTitle.h \
            include/Pomodoro.h \
            include/DataIO.h \
            include/StatsWindow.h \
            include/OptionsWindow.h \
            include/CircularTimer.h \
            include/charts/WeekChart.h \
            include/charts/DayChart.h \
            include/nlohmann/json.hpp

FORMS    += ui/MainWindow.ui \
            ui/StatsWindow.ui \
            ui/OptionsWindow.ui \
            ui/CircularTimer.ui

RESOURCES += resources.qrc


RC_ICONS = images/icon.ico

target.path = ./install
INSTALLS += target








