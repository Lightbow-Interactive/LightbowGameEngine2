cmake_minimum_required(VERSION 3.21)
project(Engine)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        Source/Core/Game.cpp
        Source/Core/Level.cpp
        Source/State/GameState.cpp
        Source/Objects/LBGEObject.cpp
        Source/Objects/ObjectManager.cpp
        Source/UserInterface/Fonts.cpp)

add_library(Engine STATIC ${SOURCE_FILES})

if(APPLE)
    include_directories(/usr/local/include)

    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    include_directories(${SFML_INCLUDE_DIRS})

    target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
endif()
