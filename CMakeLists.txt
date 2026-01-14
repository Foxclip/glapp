cmake_minimum_required(VERSION 3.10)

project(glapp LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)

add_subdirectory(glvis)
add_subdirectory(glapp_tests)

add_library(${PROJECT_NAME})
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

target_sources(${PROJECT_NAME} PRIVATE
    ${SRC_DIR}/app.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE glvis)
