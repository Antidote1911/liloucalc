cmake_minimum_required(VERSION 3.16)

project(LilouCalc VERSION 1.1.3 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Svg)
find_package(GSL REQUIRED)

set(CORE_SOURCES
    core/book.cpp
    core/constants.cpp
    core/evaluator.cpp
    core/functions.cpp
    core/mathdsl.cpp
    core/numberformatter.cpp
    core/pageserver.cpp
    core/settings.cpp
    core/session.cpp
    core/sessionhistory.cpp
    core/startupdefinitions.cpp
    core/unitdisplayformat.cpp
    core/units.cpp
    core/variable.cpp
    core/userfunction.cpp
    core/userunit.cpp
    core/opcode.cpp
)

set(MATH_SOURCES
    math/floatnum/floatcommon.c
    math/floatnum/floatconst.c
    math/floatnum/floatconvert.c
    math/floatnum/floaterf.c
    math/floatnum/floatexp.c
    math/floatnum/floatgamma.c
    math/floatnum/floathmath.c
    math/floatnum/floatio.c
    math/floatnum/floatipower.c
    math/floatnum/floatlog.c
    math/floatnum/floatlogic.c
    math/floatnum/floatlong.c
    math/floatnum/floatnum.c
    math/floatnum/floatpower.c
    math/floatnum/floatseries.c
    math/floatnum/floattrig.c
    math/floatnum/floatincgamma.c
    math/hmath.cpp
    math/number.c
    math/cmath.cpp
    math/cnumberparser.cpp
    math/quantity.cpp
    math/rational.cpp
)

set(APP_SOURCES
    src/main.cpp
    src/history.cpp
    src/AboutDialog.cpp
    src/mainwindow.cpp
    src/skin.cpp
    src/solve.cpp
    src/dsettings.cpp
    src/utils.cpp
    src/AboutDialog.ui
    src/mainwindow.ui
    src/solve.ui
    RCalc.qrc
)

if(NOT MSVC)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set_source_files_properties(math/number.c PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-non-prototype")
    else()
        set_source_files_properties(math/number.c PROPERTIES COMPILE_OPTIONS "-Wno-old-style-definition")
    endif()
endif()

qt_add_executable(LilouCalc
    ${APP_SOURCES}
    ${CORE_SOURCES}
    ${MATH_SOURCES}
)

target_compile_definitions(LilouCalc PRIVATE
    SPEEDCRUNCH_VERSION="${PROJECT_VERSION}"
    APP_VERSION_STR="${PROJECT_VERSION}"
)

target_include_directories(LilouCalc PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/math
    ${CMAKE_SOURCE_DIR}/math/floatnum
)

target_link_libraries(LilouCalc PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Svg
    GSL::gsl
    GSL::gslcblas
)

set_target_properties(LilouCalc PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
