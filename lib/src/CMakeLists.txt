include_directories(${CPosix_SOURCE_DIR}/lib/include)

# linked_list_lib

add_library(linked_list_lib SHARED
    linked_lists/doubly_linked.c
    linked_lists/queue.c
    linked_lists/stack.c
)
set_target_properties(linked_list_lib PROPERTIES LINKER_LANGUAGE C)

# server

add_library(server_lib SHARED
    networking/server.c
)
set_target_properties(server_lib PROPERTIES LINKER_LANGUAGE C)

