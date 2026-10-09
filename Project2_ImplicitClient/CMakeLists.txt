cmake_minimum_required(VERSION 3.20)
project(ImplicitClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ImplicitApp main.cpp)

target_include_directories(ImplicitApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/EigenLib/include
)

target_link_libraries(ImplicitApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/EigenLib/lib/EigenLib.lib
)

add_custom_command(TARGET ImplicitApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/EigenLib/bin/EigenLib.dll"
    "$<TARGET_FILE_DIR:ImplicitApp>"
)