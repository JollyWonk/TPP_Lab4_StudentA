add_library(MatrixLib STATIC src/MatrixAnalysis.cpp)
target_include_directories(MatrixLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(MatrixLib PUBLIC cxx_std_20)