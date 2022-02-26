cmake_minimum_required(VERSION 3.21)
project(Engine CXX)

set(SFML_STATIC_LIBRARIES TRUE)

if(WIN32)
    set(SFML_DIR C:/Libs/SFML/lib/cmake/SFML)
endif()

find_package(OpenGL REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS audio network graphics window system)

set(SOURCE_FILES
        External/ImGui/imgui.cpp
        External/ImGui/imgui_widgets.cpp
        External/ImGui/imgui_draw.cpp
        External/ImGui/imgui_tables.cpp
        External/ImGui/imgui-SFML.cpp
        Source/Core/Game.cpp
        Source/Core/Level.cpp
        Source/Core/EventDelegate.cpp
        Source/State/GameState.cpp
        Source/Objects/SerializedTypes.h
        Source/Objects/LBGEObject.cpp
        Source/Objects/ObjectManager.cpp
        Source/UserInterface/Fonts.cpp
        Source/UserInterface/TextBlock.cpp
        Source/Audio/Audio.cpp
        Source/Audio/Sound.cpp
        Source/Shader/Shader.cpp
        Source/Editor/ImGuiLayer.cpp
        Source/Core/Logger.cpp
        Source/Objects/Components/ObjectComponent.cpp
        Source/Objects/Components/DefaultComponents/CppScriptComponent.cpp
        Source/Objects/Components/DefaultComponents/LuaScriptComponent.cpp
        Source/Objects/Components/DefaultComponents/PhysicsComponent.cpp)

add_library(Engine STATIC ${SOURCE_FILES})
target_link_libraries(Engine PUBLIC sfml-system sfml-window sfml-graphics sfml-audio sfml-network ${OPENGL_LIBRARY})
target_link_libraries(Engine PUBLIC ${PROJECT_SOURCE_DIR}/External/nativefiledialog/nfd.lib)
target_compile_features(Engine PUBLIC cxx_std_20)

target_include_directories(Engine PUBLIC External/)
