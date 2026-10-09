add_executable(MatrixApp main.cpp)
target_link_libraries(MatrixApp PRIVATE MatrixLib)

add_custom_command(TARGET MatrixApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:MatrixLib>"
    "$<TARGET_FILE_DIR:MatrixApp>"
)