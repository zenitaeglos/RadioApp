cmake_minimum_required(VERSION 3.1)

project(RadMag LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(RadMag_VERSION_MAJOR 0)
set(RadMag_VERSION_MINOR 1)
set(RadMag_VERSION_PATCH 1)

find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

set (MYSOURCES "${PROJECT_SOURCE_DIR}/gui/mainwindow.h"
    "${PROJECT_SOURCE_DIR}/gui/mainwindow.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.h"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguiheader.h"
    "${PROJECT_SOURCE_DIR}/gui/controlsguiheader.cpp"
    "${PROJECT_SOURCE_DIR}/requests/requestsdata.h"
    "${PROJECT_SOURCE_DIR}/requests/requestsdata.cpp"
    "${PROJECT_SOURCE_DIR}/models/requestsmodel.h"
    "${PROJECT_SOURCE_DIR}/models/requestsmodel.cpp")


add_executable(${PROJECT_NAME} "main.cpp" ${MYSOURCES})


target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Network)



if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alejandro Martinez, Sebastian Niedworok")
    set(CPACK_PACKAGE_VERSION_MAJOR ${RadMag_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${RadMag_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${RadMag_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Internet Radio Station")
    include(CPack)

endif()

