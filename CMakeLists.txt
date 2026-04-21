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
    WIN32 MACOSX_BUNDLE # 로그 확인하고 싶을 때, 주석처리
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    startwindow.cpp
    startwindow.h
    startwindow.ui
    resources.qrc
    scheduleitem.cpp # 사이드 바 스케쥴 커스텀 위젯
    scheduleitem.h
    scheduleitem.ui
    daycellwidget.cpp # 달력의 날짜 한 칸을 담당하는 커스텀 위젯
    daycellwidget.h
    sidebaropenclose.h # 사이드바 열고 닫기 기능
    sidebaropenclose.cpp
    sidebarcontentmanager.h # 사이드바에 스케줄 커스텀 위젯 삽입
    sidebarcontentmanager.cpp
    scheduleinputview.cpp # 일정 입력 or 수정 위젯
    scheduleinputview.h
    ScheduleInputView.ui
    ${MATERIAL_SOURCES}
)

target_include_directories(2026-VEDA4-Schedule_Management PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"             # 프로젝트 루트, 추가한 코드
    "${MATERIAL_WIDGETS_DIR}"                 # components 폴더
    "${MATERIAL_WIDGETS_DIR}/../"            # components의 상위(lib 등이 포함된 경우), 추가한 코드
    "${MATERIAL_WIDGETS_DIR}/lib"             # 라이브러리 핵심 로직 폴더
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
