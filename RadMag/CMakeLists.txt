cmake_minimum_required(VERSION 3.1)

project(RadMag LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set (MYSOURCES "${PROJECT_SOURCE_DIR}/gui/mainwindow.h"
    "${PROJECT_SOURCE_DIR}/gui/mainwindow.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.h"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.cpp")


add_executable(${PROJECT_NAME} "main.cpp" ${MYSOURCES})


target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
