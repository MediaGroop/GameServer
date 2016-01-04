cmake_minimum_required(VERSION 2.6)
project(rakgameserver)
set(CMAKE_CXX_FLAGS "-D_ELPP_THREAD_SAFE=1 -D_ELPP_DEBUG_ERRORS=1 -D_ELPP_STACKTRACE_ON_CRASH=1 -D_ELPP_FORCE_USE_STD_THREAD=1 -D_ELPP_LOGGING_FLAGS_FROM_ARG=1 -std=gnu++11 -lpthread -lrt")

include_directories ("Deps/Rak-Net/Source/")
file(GLOB files "*.cpp" "*.c")

add_executable(rakgameserver ${files})

target_link_libraries(rakgameserver ${CMAKE_SOURCE_DIR}/libraknet.a)

install(TARGETS rakgameserver RUNTIME DESTINATION bin)