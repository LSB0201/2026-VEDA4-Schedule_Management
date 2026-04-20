cmake_minimum_required(VERSION 3.19)
project(2026-VEDA4-Schedule_Management LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Gui StateMachine)

set(MATERIAL_WIDGETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qt-material-widgets/components")

file(GLOB_RECURSE MATERIAL_SOURCES
    "${MATERIAL_WIDGETS_DIR}/*.cpp"
    "${MATERIAL_WIDGETS_DIR}/*.h"
)

qt_standard_project_setup()

qt_add_executable(2026-VEDA4-Schedule_Management
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
    ${MATERIAL_SOURCES}
)

target_include_directories(2026-VEDA4-Schedule_Management PRIVATE
    "${MATERIAL_WIDGETS_DIR}"
    "${MATERIAL_WIDGETS_DIR}/lib"
)

target_link_libraries(2026-VEDA4-Schedule_Management
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Gui
        Qt::StateMachine
)

install(TARGETS 2026-VEDA4-Schedule_Management
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET 2026-VEDA4-Schedule_Management
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
