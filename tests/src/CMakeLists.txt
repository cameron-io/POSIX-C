cmake_minimum_required(VERSION 3.31 FATAL_ERROR)
project(CPosixTests VERSION 0.1.0 LANGUAGES C)

include_directories(${CPosix_SOURCE_DIR}/lib/include)
link_directories(${CPosix_SOURCE_DIR}/lib/src)

### LinkedLists

add_executable(doubly_linked_test linked_lists/doubly_linked_test.c)
target_link_libraries(doubly_linked_test linked_list_lib)
add_test(NAME doubly_linked_test COMMAND doubly_linked_test)

add_executable(queue_test linked_lists/queue_test.c)
target_link_libraries(queue_test linked_list_lib)
add_test(NAME queue_test COMMAND queue_test)

add_executable(stack_test linked_lists/stack_test.c)
target_link_libraries(stack_test linked_list_lib)
add_test(NAME stack_test COMMAND stack_test)

### Server

add_executable(server_test networking/server_test.c)
target_link_libraries(server_test server_lib)
add_test(NAME server_test COMMAND server_test)


###
# CTest
###

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
