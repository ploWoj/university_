cmake_minimum_required(VERSION 3.10)

project(university_)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE Person.cpp Student.cpp Employee.cpp db.cpp University.cpp)
set(FLAGS -Wall -Wextra -Wpedantic -Wno-conversion -Werror -g -O0)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}/usr/lib/x86_64-linux-gnu/libmysqlclient.so)

set(INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/db.txt)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR})
configure_file(${INPUT_FILE} ${OUTPUT_DIR}/db.txt COPYONLY)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCE})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})

include_directories(/usr/include/mysql)
link_directories(CMKAE_LIBRARY_PATH)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib mysqlclient)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})