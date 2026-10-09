#pragma once

#ifdef EIGENLIB_EXPORTS
#define EIGENLIB_API extern "C" __declspec(dllexport)
#else
#define EIGENLIB_API extern "C" __declspec(dllimport)
#endif

// 1. Степенной метод для поиска наибольшего собственного значения и вектора
EIGENLIB_API bool powerMethod(const double* A, int n, double* outEigenvalue, double* outEigenvector, double tol, int maxIter);

// 2. Вычисление собственного значения
EIGENLIB_API bool eigenvalue(const double* A, int n, double* outEigenvalue);

// 3. Вычисление собственного вектора
EIGENLIB_API bool eigenvector(const double* A, int n, double* outEigenvector);

// 4. Расчет невязки R = ||A*v - lambda*v||
EIGENLIB_API double residual(const double* A, double lambda, const double* v, int n);