cmake_minimum_required(VERSION 3.21)
project(BlankTemplate)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES 
            ${PROJECT_SOURCE_DIR}/*.h 
            ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(BlankTemplate ${SOURCE_FILES})

set(LBGE_PATH ../Engine)

target_include_directories(${PROJECT_NAME} PUBLIC ${LBGE_PATH}/Include)
target_link_libraries(${PROJECT_NAME} Engine)

file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND
                    ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/Resources
                    ${CMAKE_CURRENT_SOURCE_DIR}/Debug/Resources)               