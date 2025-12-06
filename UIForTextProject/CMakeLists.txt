cmake_minimum_required(VERSION 3.16)

project(UIForTextProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "D:/Qt/6.10.1/mingw_64")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt with Widgets + Network
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        GhostTextEdit.cpp
        GhostTextEdit.h
        ../TrieConcordance.cpp
        ../TrieConcordance.h
        ../map.cpp
        ../map.h
        ../WordNetSynonyms_qt.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UIForTextProject
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(UIForTextProject SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(UIForTextProject
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(UIForTextProject
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
)

# Make sure generated ui_mainwindow.h can find GhostTextEdit.h in the source dir
target_include_directories(UIForTextProject
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Bundle / executable settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.UIForTextProject)
endif()
set_target_properties(UIForTextProject PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS UIForTextProject
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UIForTextProject)
endif()
