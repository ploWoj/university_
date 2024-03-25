cmake_minimum_required(VERSION 3.10)

project(university_)

set(SOURCE Person.cpp Student.cpp Employee.cpp db.cpp University.cpp)
set(FLAG -Wall -Wextra -O3 )
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}/usr/lib/x86_64-linux-gnu/libmysqlclient.so)

set(INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/db.txt)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR})
configure_file(${INPUT_FILE} ${OUTPUT_DIR}/db.txt COPYONLY)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCE})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
set_target_properties(${PROJECT_NAME}-lib  PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

include_directories(/usr/include/mysql)
link_directories(CMKAE_LIBRARY_PATH)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib mysqlclient)