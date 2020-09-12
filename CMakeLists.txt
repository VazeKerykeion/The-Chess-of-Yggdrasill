cmake_minimum_required(VERSION 3.8)
project(Chess)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH D:/QT/5.14/5.14.2/mingw73_64) #这里需要填入自己安装的路径

find_package(Qt5 COMPONENTS Core Qml Quick Widgets DBus REQUIRED)
find_package(Qt5Network)


set(UI_FILES connection.ui local_choice.ui mainwindow.ui single_play.ui local_master.ui local_slave.ui)

set(HEAD_FILES mainwindow.h local_choice.h connection.h cell_label.h single_play.h local_master.h local_slave.h)

set(SOURCE_FILES mainwindow.cpp local_choice.cpp connection.cpp cell_label.cpp single_play.cpp local_master.cpp local_slave.cpp)

set(QRC_FILES pic.qrc)

add_executable(Chess WIN32 ${HEAD_FILES} ${SOURCE_FILES} ${UI_FILES} ${QRC_FILES} main.cpp chessBoard.cpp chessBoard.h)

target_link_libraries(Chess Qt5::Widgets)

qt5_use_modules(Chess Core Widgets Gui Network)
