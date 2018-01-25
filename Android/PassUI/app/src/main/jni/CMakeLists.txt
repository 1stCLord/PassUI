cmake_minimum_required (VERSION 3.1.0)
project (passssh)

add_subdirectory(libssh-0.7.5)

set (CMAKE_CXX_STANDARD 14)

file( GLOB Source *.cpp )

add_library (passssh SHARED ${Source})

target_link_libraries (passssh ssh_static ssh_threads_static)