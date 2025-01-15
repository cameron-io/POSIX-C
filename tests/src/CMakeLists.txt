include_directories(${CPosix_SOURCE_DIR}/lib/include)
link_directories(${CPosix_SOURCE_DIR}/lib/src)

# LinkedLists

add_executable(doubly_linked_test linked_lists/doubly_linked_test.c)
target_link_libraries(doubly_linked_test linked_list_lib)
add_test(NAME doubly_linked_test COMMAND doubly_linked_test)

add_executable(queue_test linked_lists/queue_test.c)
target_link_libraries(queue_test linked_list_lib)
add_test(NAME queue_test COMMAND queue_test)

add_executable(stack_test linked_lists/stack_test.c)
target_link_libraries(stack_test linked_list_lib)
add_test(NAME stack_test COMMAND stack_test)

# Searching

add_executable(binary_search_test searching/binary_search_test.c)
target_link_libraries(binary_search_test search_lib)
add_test(NAME binary_search_test COMMAND binary_search_test)

# Sorting

add_executable(quick_sort_test sorting/quick_sort_test.c)
target_link_libraries(quick_sort_test sorting_lib)
add_test(NAME quick_sort_test COMMAND quick_sort_test)

add_executable(bubble_sort_test sorting/bubble_sort_test.c)
target_link_libraries(bubble_sort_test sorting_lib)
add_test(NAME bubble_sort_test COMMAND bubble_sort_test)
