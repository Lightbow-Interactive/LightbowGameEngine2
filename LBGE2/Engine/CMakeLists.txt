cmake_minimum_required(VERSION 3.21)
project(Engine CXX)

#set(SFML_STATIC_LIBRARIES TRUE)

if(WIN32)
    set(SFML_DIR C:/Libs/SFML/lib/cmake/SFML)
endif()

find_package(OpenGL REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS audio network graphics window system)

file(GLOB_RECURSE SOURCE_CORE 
            ${PROJECT_SOURCE_DIR}/Source/Core/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Core/*.cpp)
file(GLOB_RECURSE SOURCE_AUDIO 
            ${PROJECT_SOURCE_DIR}/Source/Audio/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Audio/*.cpp)
file(GLOB_RECURSE SOURCE_EDITOR 
            ${PROJECT_SOURCE_DIR}/Source/Editor/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Editor/*.cpp)
file(GLOB SOURCE_OBJECTS 
            ${PROJECT_SOURCE_DIR}/Source/Objects/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Objects/*.cpp)
file(GLOB_RECURSE SOURCE_OBJECTS_COMPONENTS 
            ${PROJECT_SOURCE_DIR}/Source/Objects/Components/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Objects/Components/*.cpp)
file(GLOB_RECURSE SOURCE_SHADER 
            ${PROJECT_SOURCE_DIR}/Source/Shader/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Shader/*.cpp)
file(GLOB_RECURSE SOURCE_STATE 
            ${PROJECT_SOURCE_DIR}/Source/State/*.h 
            ${PROJECT_SOURCE_DIR}/Source/State/*.cpp)
file(GLOB_RECURSE SOURCE_TYPES 
            ${PROJECT_SOURCE_DIR}/Source/Types/*.h 
            ${PROJECT_SOURCE_DIR}/Source/Types/*.cpp)
file(GLOB_RECURSE SOURCE_UI
            ${PROJECT_SOURCE_DIR}/Source/UserInterface/*.h 
            ${PROJECT_SOURCE_DIR}/Source/UserInterface/*.cpp)

file(GLOB_RECURSE SOURCE_EXTERNAL 
            ${PROJECT_SOURCE_DIR}/External/*.h 
            ${PROJECT_SOURCE_DIR}/External/*.cpp
            ${PROJECT_SOURCE_DIR}/External/*.hpp
            ${PROJECT_SOURCE_DIR}/External/*.c)

add_library(Engine STATIC ${SOURCE_CORE} ${SOURCE_AUDIO} ${SOURCE_EDITOR} ${SOURCE_OBJECTS} ${SOURCE_OBJECTS_COMPONENTS} ${SOURCE_SHADER} ${SOURCE_STATE} ${SOURCE_TYPES} ${SOURCE_UI} ${SOURCE_EXTERNAL})

target_link_libraries(Engine PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${OPENGL_LIBRARY})
target_compile_features(Engine PUBLIC cxx_std_20)

target_include_directories(Engine PUBLIC External/ External/tmxlite/include)

source_group("Source/Core" FILES ${SOURCE_CORE})
source_group("Source/Audio" FILES ${SOURCE_AUDIO})
source_group("Source/Editor" FILES ${SOURCE_EDITOR})
source_group("Source/Objects" FILES ${SOURCE_OBJECTS})
source_group("Source/Objects/Components" FILES ${SOURCE_OBJECTS_COMPONENTS})
source_group("Source/Shader" FILES ${SOURCE_SHADER})
source_group("Source/State" FILES ${SOURCE_STATE})
source_group("Source/Types" FILES ${SOURCE_TYPES})
source_group("Source/UserInterface" FILES ${SOURCE_UI})
source_group("External" FILES ${SOURCE_EXTERNAL})



