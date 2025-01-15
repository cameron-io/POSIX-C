include_directories(${CPosix_SOURCE_DIR}/lib/include)
link_directories(${CPosix_SOURCE_DIR}/lib/src)

add_executable(server server/server.c)
target_link_libraries(server server_lib)

add_executable(web_server server/web_server.c)
