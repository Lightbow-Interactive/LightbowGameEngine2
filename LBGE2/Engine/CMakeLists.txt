cmake_minimum_required(VERSION 3.21)
project(Engine CXX)

find_package(SFML 2.5.1 REQUIRED COMPONENTS audio network graphics window system)

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
target_link_libraries(Engine PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_compile_features(Engine PUBLIC cxx_std_20)

if(WIN32)
    set(SFML_ROOT C:/Libs/SFML)

    # Copy dlls to build
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()