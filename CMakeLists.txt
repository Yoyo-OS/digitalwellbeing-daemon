cmake_minimum_required(VERSION 3.14)

project(yoyo-digitalwellbeing-daemon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt5 Qt6 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core DBus Sql REQUIRED)
find_package(DtkCore REQUIRED)
#include(FindPkgConfig)
#pkg_check_modules(XCB xcb REQUIRED)
#pkg_check_modules(DCore REQUIRED I.MPORTED_TARGET dtkcore)
#pkg_check_modules(DWidget REQUIRED IMPORTED_TARGET dtkwidget)

file(GLOB PROJECT_SOURCES
        "src/*.cpp" "src/*.h"
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(yoyo-digitalwellbeing-daemon
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(yoyo-digitalwellbeing-daemon SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(yoyo-digitalwellbeing-daemon
          ${PROJECT_SOURCES}
        )
    endif()
endif()

message(${QT_VERSION_MAJOR})

target_compile_definitions(yoyo-digitalwellbeing-daemon
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(yoyo-digitalwellbeing-daemon
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::DBus Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(yoyo-digitalwellbeing-daemon PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

set(CMAKE_INSTALL_PREFIX "/usr")
install(FILES src/dbusservices/org.deepin.dde.digitalWellbeing.service
        DESTINATION /usr/share/dbus-1/services)
install(TARGETS yoyo-digitalwellbeing-daemon DESTINATION bin)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(yoyo-digitalwellbeing-daemon)
    qt_finalize_executable(yoyo-digitalwellbeing-daemon)
endif()
