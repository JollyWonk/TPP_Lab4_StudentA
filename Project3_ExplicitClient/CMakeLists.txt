cmake_minimum_required(VERSION 3.20)
project(ExplicitClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ExplicitApp main.cpp)

add_custom_command(TARGET ExplicitApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/EigenLib.dll"
    "$<TARGET_FILE_DIR:ExplicitApp>"
)