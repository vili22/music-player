PROJECT(Player)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(QT_QMAKE_EXECUTABLE /usr/bin/qmake-qt4)
SET(QT_MIN_VERSION "4.8.0")


INCLUDE(FindQt4)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#QT4_AUTOMOC(MainWindow.cpp)
set(CMAKE_AUTOMOC TRUE)

#LINK_LIBRARIES(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} boost_system boost_filesystem)

ADD_EXECUTABLE(music_player MainWindow.cpp style.cpp)
SET_TARGET_PROPERTIES(music_player PROPERTIES COMPILE_FLAGS "-O2 -fno-inline-functions -Wall -Wextra -Wno-unused-parameter")
TARGET_LINK_LIBRARIES(music_player ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} boost_system boost_filesystem /usr/local/lib/libsfml-audio.so.2  /usr/local/lib/libsfml-system.so.2)





