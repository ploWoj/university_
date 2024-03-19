cmake_minimum_required(VERSION 3.10)

project(university_)

set(SOURCE Person.cpp Student.cpp)
set(FLAG -Wall -Wextra -O3)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCE})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
set_target_properties(${PROJECT_NAME}-lib PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)