cmake_minimum_required(VERSION 3.21)
project(BlankTemplate)

set(CMAKE_CXX_STANDARD 23)

add_executable(BlankTemplate
        Source/main.cpp
        Source/MainLevel.cpp Source/MainLevel.h)

set(LBGE_PATH ../Engine)

target_include_directories(${PROJECT_NAME} PUBLIC ${LBGE_PATH}/Include)
target_link_libraries(${PROJECT_NAME} Engine)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})