cmake_minimum_required(VERSION 3.16)
project(transaction_service C)

set(CMAKE_C_STANDARD 99)
include(CTest)
enable_testing()

add_executable(transaction_service main.c
        app/config.h
        app/config.c
        app/database.c
        app/database.h
        app/transaction.c
        app/transaction.h
        app/global.h app/queue.c app/queue.h app/application.c app/application.h)
target_link_libraries(transaction_service PUBLIC m pq jsonparser zmq)
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(transaction_service PUBLIC
        "${PROJECT_BINARY_DIR}"
        "/usr/local/include/json-parser/")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)