cmake_minimum_required(VERSION 3.21)
project(Engine)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        Source/Core/Game.cpp
        Source/Core/Level.cpp
        Source/Core/EventDelegate.cpp
        Source/State/GameState.cpp
        Source/Objects/LBGEObject.cpp
        Source/Objects/ObjectManager.cpp
        Source/UserInterface/Fonts.cpp
        Source/UserInterface/TextBlock.cpp
        Source/Audio/Audio.cpp
        Source/Audio/Sound.cpp)

add_library(Engine STATIC ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")

if(WIN32)
    set(SFML_ROOT C:/Libs/SFML)

    # Copy dlls to build
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

find_package(SFML REQUIRED audio network graphics)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
include_directories(${SFML_INCLUDE_DIRS})