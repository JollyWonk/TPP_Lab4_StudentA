#pragma once

namespace MatrixAnalysis {

double determinant(const double* matrix, int n);
bool isSingular(const double* matrix, int n);
int rank(const double* matrix, int rows, int cols);
bool inverse(const double* matrix, int n, double* outMatrix);

}