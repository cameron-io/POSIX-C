include_directories(${CPosix_SOURCE_DIR}/lib/include)
link_directories(${CPosix_SOURCE_DIR}/lib/src)

add_executable(echo_server server/echo_server.c)

add_executable(web_server server/web_server.c)
target_link_libraries(web_server web_server_lib)
