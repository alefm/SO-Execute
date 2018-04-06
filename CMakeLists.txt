cmake_minimum_required(VERSION 2.8)

project (SO-Execute)

SET(CMAKE_SYSTEM_NAME Linux)  

include_directories( app/include/ )
file(GLOB headers "app/include/*.h" )
file(GLOB sources "app/src/*.c" )

add_executable(execute ${sources} ${headers})

target_link_libraries( execute )
