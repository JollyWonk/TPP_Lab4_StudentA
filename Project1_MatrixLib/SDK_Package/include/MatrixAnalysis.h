#pragma once

#ifdef MATRIX_EXPORTS
    #define MATRIX_API extern "C" __declspec(dllexport)
#else
    #define MATRIX_API extern "C" __declspec(dllimport)
#endif

MATRIX_API double determinant(const double* matrix, int n);
MATRIX_API int isSingular(const double* matrix, int n);
MATRIX_API int rank(const double* matrix, int rows, int cols);
MATRIX_API int inverse(const double* matrix, int n, double* outMatrix);