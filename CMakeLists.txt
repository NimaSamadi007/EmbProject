cmake_minimum_required(VERSION 3.10)

project("server")

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(PAHO_MQTT_ROOT "/home/nima/local-libs/paho-mqtt")

find_package(OpenCV REQUIRED)
execute_process(COMMAND mysql_config --cflags
		OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs
		OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)


include_directories(${MySQL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include ${PAHO_MQTT_ROOT}/include)        
include_directories("/home/nima/local-libs/boost" "include")
link_directories("/home/nima/local-libs/boost/stage/lib")
link_directories(${PAHO_MQTT_ROOT}/lib)


add_executable(${PROJECT_NAME} "src/main.cpp" "src/Camera.cpp")
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} paho-mqtt3c)
