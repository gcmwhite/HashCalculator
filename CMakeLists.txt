cmake_minimum_required(VERSION 3.14)

project(HashCalculator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Concurrent REQUIRED)

add_executable(HashCalculator
    main.cxx
    qml.qrc
    HashTool.hxx
    HashTool.cxx
)

target_compile_definitions(HashCalculator
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(HashCalculator
  PRIVATE Qt5::Core Qt5::Quick Qt5::Concurrent)
