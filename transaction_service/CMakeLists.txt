cmake_minimum_required(VERSION 3.22)
project(c_microservices C)

set(CMAKE_C_STANDARD 99)
include(CTest)
include(ExternalProject)
enable_testing()
add_subdirectory(deps/libzmq)
#add_subdirectory(deps/json-parser)
include_directories(libs)
add_executable(c_microservices main.c libs/config.h libs/config.c libs/database.c libs/database.h)
target_link_libraries(c_microservices pq jsonparser libzmq)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(c_microservices PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/deps")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)