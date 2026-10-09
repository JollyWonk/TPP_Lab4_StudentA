add_library(MatrixLib SHARED src/MatrixAnalysis.cpp)

target_compile_definitions(MatrixLib PRIVATE MATRIX_EXPORTS)

target_include_directories(MatrixLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(MatrixLib PUBLIC cxx_std_20)