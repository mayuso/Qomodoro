cmake_minimum_required(VERSION 3.5)

project(Qomodoro VERSION 0.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(QtCommon)
fix_project_version()
add_project_meta(META_FILES_TO_INCLUDE)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

include_directories(include)

set(SOURCE_FILES
        src/main.cpp
        src/MainWindow.cpp
        src/TopBarTitle.cpp
        src/Pomodoro.cpp
        src/DataIO.cpp
        src/StatsWindow.cpp
        src/OptionsWindow.cpp
        src/TimerWindow.cpp
        src/SlidingStackedWidget.cpp
        src/charts/WeekChart.cpp
        src/charts/DayChart.cpp
        include/MainWindow.h
        include/TopBarTitle.h
        include/Pomodoro.h
        include/DataIO.h
        include/StatsWindow.h
        include/OptionsWindow.h
        include/TimerWindow.h
        include/SlidingStackedWidget.h
        include/charts/WeekChart.h
        include/charts/DayChart.h
        vendor/json/include/nlohmann/json.hpp
        ui/MainWindow.ui
        ui/StatsWindow.ui
        ui/OptionsWindow.ui
        ui/TimerWindow.ui
)

set(RESOURCE_FILES resources.qrc)
set(RC_ICONS images/icon.ico)

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Charts)
