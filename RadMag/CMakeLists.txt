cmake_minimum_required(VERSION 3.1)

project(RadMag LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(RadMag_VERSION_MAJOR 0)
set(RadMag_VERSION_MINOR 16)
set(RadMag_VERSION_PATCH 0)

find_package(Qt5 COMPONENTS Core Widgets Network Multimedia Svg DBus REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/share)

qt5_add_resources(RESOURCE_FILES "files.qrc"
    "translations.qrc")

set (MYSOURCES "${PROJECT_SOURCE_DIR}/gui/mainwindow.h"
    "${PROJECT_SOURCE_DIR}/gui/mainwindow.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.h"
    "${PROJECT_SOURCE_DIR}/gui/controlsguibottom.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguiheader.h"
    "${PROJECT_SOURCE_DIR}/gui/custom/radioappbutton.h"
    "${PROJECT_SOURCE_DIR}/gui/custom/radioappbutton.cpp"
    "${PROJECT_SOURCE_DIR}/gui/controlsguiheader.cpp"
    "${PROJECT_SOURCE_DIR}/requests/radiostation.h"
    "${PROJECT_SOURCE_DIR}/requests/radiostation.cpp"
    "${PROJECT_SOURCE_DIR}/models/radiostationsmodel.h"
    "${PROJECT_SOURCE_DIR}/models/radiostationsmodel.cpp"
    "${PROJECT_SOURCE_DIR}/models/radiostationdelegate.h"
    "${PROJECT_SOURCE_DIR}/models/radiostationdelegate.cpp"
    "${PROJECT_SOURCE_DIR}/models/favouritesmodel.h"
    "${PROJECT_SOURCE_DIR}/models/favouritesmodel.cpp"
    "${PROJECT_SOURCE_DIR}/models/favouritesdelegate.h"
    "${PROJECT_SOURCE_DIR}/models/favouritesdelegate.cpp"
    "${PROJECT_SOURCE_DIR}/logic/radioplayer.h"
    "${PROJECT_SOURCE_DIR}/logic/radioplayer.cpp"
    "${PROJECT_SOURCE_DIR}/logic/favouritesjson.h"
    "${PROJECT_SOURCE_DIR}/logic/favouritesjson.cpp"
    "${PROJECT_SOURCE_DIR}/logic/comparemodels.h"
    "${PROJECT_SOURCE_DIR}/logic/comparemodels.cpp"
    "${PROJECT_SOURCE_DIR}/notifications/popupnotifications.h"
    "${PROJECT_SOURCE_DIR}/notifications/popupnotifications.cpp"
    "${PROJECT_SOURCE_DIR}/datasource/datasource.h"
    "${PROJECT_SOURCE_DIR}/datasource/datasource.cpp"
    "${PROJECT_SOURCE_DIR}/network/networkdatamanager.h"
    "${PROJECT_SOURCE_DIR}/network/networkdatamanager.cpp"
    "${PROJECT_SOURCE_DIR}/network/networkdelegate.h"
    "${PROJECT_SOURCE_DIR}/network/networkdelegate.cpp")

add_executable(${PROJECT_NAME} "main.cpp" ${RESOURCE_FILES} ${MYSOURCES})


target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Network Qt5::Multimedia Qt5::Svg Qt5::DBus)



if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    install(TARGETS RadMag DESTINATION bin)
    install(FILES share/radmag.desktop DESTINATION /usr/share/applications
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        )
    install(FILES share/radiow48.png DESTINATION /usr/share/pixmaps)
    install(FILES share/radiow48.png
             DESTINATION share/icons/hicolor/256x256/apps/
             PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
             )
         install(FILES share/radiow48.png
             DESTINATION share/icons/gnome/256x256/apps/
             PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
             )


    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Alejandro Martinez, Sebastian Niedworok")
    set(CPACK_PACKAGE_VERSION_MAJOR ${RadMag_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${RadMag_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${RadMag_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Internet Radio Station. Listening to thousands of radio stations")

    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    set(CPACK_PACKAGE_ICON share/radio.png)
    include(CPack)

endif()

