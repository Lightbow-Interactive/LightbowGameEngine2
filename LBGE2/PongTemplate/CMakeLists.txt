cmake_minimum_required(VERSION 3.21)
project(PongTemplate)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES 
            ${PROJECT_SOURCE_DIR}/*.h 
            ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(PongTemplate ${SOURCE_FILES})

set(LBGE_PATH ../Engine)

target_include_directories(${PROJECT_NAME} PUBLIC ${LBGE_PATH}/Include)
target_link_libraries(${PROJECT_NAME} Engine)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
