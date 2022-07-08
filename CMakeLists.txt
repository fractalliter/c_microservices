cmake_minimum_required(VERSION 3.22)
project(c_microservices C)

set(CMAKE_C_STANDARD 99)
include(CTest)
include(ExternalProject)
enable_testing()

add_executable(c_microservices main.c)
target_link_libraries(c_microservices m zmq pq jsonparser)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)