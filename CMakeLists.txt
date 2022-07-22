cmake_minimum_required(VERSION 3.10)

project("server")

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories("/home/nima/local-libs/boost" "include")
link_directories("/home/nima/local-libs/boost/stage/lib")

add_executable(${PROJECT_NAME} "src/main.cpp")
