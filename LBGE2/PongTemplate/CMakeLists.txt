cmake_minimum_required(VERSION 3.21)
project(PongTemplate)

set(CMAKE_CXX_STANDARD 23)

add_executable(PongTemplate main.cpp Source/Levels/PongMenuLevel.cpp Source/Levels/PongMenuLevel.h Source/States/PongMenuState.cpp Source/States/PongMenuState.h Source/Levels/PongPlayingLevel.cpp Source/Levels/PongPlayingLevel.h Source/Objects/Player.cpp Source/Objects/Player.h Source/Objects/Ball.cpp Source/Objects/Ball.h)

set(LBGE_PATH ../Engine)

target_include_directories(${PROJECT_NAME} PUBLIC ${LBGE_PATH}/Include)
target_link_libraries(${PROJECT_NAME} Engine)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
