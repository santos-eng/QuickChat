cmake_minimum_required(VERSION 3.19)
project(QCNetwork)

set(CMAKE_CXX_STANDARD 20)

cmake_policy(SET CMP0167 NEW)

find_package(Boost 1.90.0 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        Boost::headers
)