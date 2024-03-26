cmake_minimum_required(VERSION 3.10)

project(university_)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE src/Person.cpp src/Student.cpp src/Employee.cpp src/db.cpp src/University.cpp)
set(FLAGS -Wall -Wextra -Wpedantic -Wno-conversion -g -O0)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}/usr/lib/x86_64-linux-gnu/libmysqlclient.so)

set(INPUT_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/db.txt)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR})
configure_file(${INPUT_FILE} ${OUTPUT_DIR}/db.txt COPYONLY)

add_library(${PROJECT_NAME}-lib STATIC ${SOURCE})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})

include_directories(/usr/include/mysql)
link_directories(CMKAE_LIBRARY_PATH)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib mysqlclient)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
# preson-test
add_executable (${PROJECT_NAME}-person-ut tests/test-person.cpp tests/catch_amalgamated.cpp)
target_include_directories(${PROJECT_NAME}-person-ut PUBLIC src )

target_compile_options (${PROJECT_NAME}-person-ut PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME}-person-ut PRIVATE ${PROJECT_NAME}-lib)
# emloyee-test
add_executable (${PROJECT_NAME}-employee-ut tests/test-employee.cpp tests/catch_amalgamated.cpp)
target_include_directories(${PROJECT_NAME}-employee-ut PUBLIC src )

target_compile_options (${PROJECT_NAME}-employee-ut PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME}-employee-ut PRIVATE ${PROJECT_NAME}-lib)