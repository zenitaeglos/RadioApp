cmake_minimum_required(VERSION 3.1)

project(RadMag LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(RadMag_VERSION_MAJOR 0)
set(RadMag_VERSION_MINOR 2)
set(RadMag_VERSION_PATCH 0)

find_package(Qt5 COMPONENTS Core Widgets Network Multimedia Svg Sql REQUIRED)

set (MYSOURCES "${PROJECT_SOURCE_DIR}/gui/mainwindow.h"
    "${PROJECT_SOURCE_DIR}/gui/mainwindow.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.h"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguiheader.h"
    "${PROJECT_SOURCE_DIR}/gui/controlsguiheader.cpp"
    "${PROJECT_SOURCE_DIR}/requests/radiostation.h"
    "${PROJECT_SOURCE_DIR}/requests/radiostation.cpp"
    "${PROJECT_SOURCE_DIR}/models/radiostationsmodel.h"
    "${PROJECT_SOURCE_DIR}/models/radiostationsmodel.cpp"
    "${PROJECT_SOURCE_DIR}/models/requestdelegate.h"
    "${PROJECT_SOURCE_DIR}/models/requestdelegate.cpp"
    "${PROJECT_SOURCE_DIR}/models/favouritesmodel.h"
    "${PROJECT_SOURCE_DIR}/models/favouritesmodel.cpp"
    "${PROJECT_SOURCE_DIR}/models/favouritesdelegate.h"
    "${PROJECT_SOURCE_DIR}/models/favouritesdelegate.cpp"
    "${PROJECT_SOURCE_DIR}/logic/radioplayer.h"
    "${PROJECT_SOURCE_DIR}/logic/radioplayer.cpp"
    "${PROJECT_SOURCE_DIR}/logic/favouritesjson.h"
    "${PROJECT_SOURCE_DIR}/logic/favouritesjson.cpp")


add_executable(${PROJECT_NAME} "main.cpp" "files.qrc" ${MYSOURCES})


target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::Svg Qt5::Sql)



if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS RadMag DESTINATION bin)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alejandro Martinez, Sebastian Niedworok")
    set(CPACK_PACKAGE_VERSION_MAJOR ${RadMag_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${RadMag_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${RadMag_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Internet Radio Station")
    set(CPACK_DEBIAN_PACKAGE_DEBUG)
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
    include(CPack)

endif()

