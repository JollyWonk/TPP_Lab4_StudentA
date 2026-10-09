#include "MatrixAnalysis.h"
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>

extern "C" {

    double determinant(const double* matrix, int n) {
        if (!matrix || n <= 0) return std::numeric_limits<double>::quiet_NaN();
        if (n == 1) return matrix[0];

        std::vector<double> a(matrix, matrix + n * n);
        double det = 1.0;
        const double EPS = 1e-9;

        for (int i = 0; i < n; ++i) {
            int pivot = i;
            for (int j = i + 1; j < n; ++j) {
                if (std::fabs(a[j * n + i]) > std::fabs(a[pivot * n + i])) {
                    pivot = j;
                }
            }

            if (std::fabs(a[pivot * n + i]) < EPS) return 0.0;

            if (i != pivot) {
                for (int k = 0; k < n; ++k) {
                    std::swap(a[i * n + k], a[pivot * n + k]);
                }
                det = -det;
            }

            det *= a[i * n + i];

            for (int j = i + 1; j < n; ++j) {
                double factor = a[j * n + i] / a[i * n + i];
                for (int k = i + 1; k < n; ++k) {
                    a[j * n + k] -= factor * a[i * n + k];
                }
            }
        }
        return det;
    }

    int isSingular(const double* matrix, int n) {
        if (!matrix || n <= 0) return -1;
        double det = determinant(matrix, n);
        if (std::isnan(det)) return -1;
        return (std::fabs(det) < 1e-9) ? 1 : 0;
    }

    int rank(const double* matrix, int rows, int cols) {
        if (!matrix || rows <= 0 || cols <= 0) return -1;

        std::vector<double> a(matrix, matrix + rows * cols);
        const double EPS = 1e-9;
        int rankVal = 0;
        std::vector<bool> rowSelected(rows, false);

        for (int i = 0; i < cols; ++i) {
            int j;
            for (j = 0; j < rows; ++j) {
                if (!rowSelected[j] && std::fabs(a[j * cols + i]) > EPS) break;
            }
            if (j != rows) {
                ++rankVal;
                rowSelected[j] = true;
                for (int p = i + 1; p < cols; ++p) a[j * cols + p] /= a[j * cols + i];
                for (int k = 0; k < rows; ++k) {
                    if (k != j && std::fabs(a[k * cols + i]) > EPS) {
                        for (int p = i + 1; p < cols; ++p) {
                            a[k * cols + p] -= a[j * cols + p] * a[k * cols + i];
                        }
                    }
                }
            }
        }
        return rankVal;
    }

    int inverse(const double* matrix, int n, double* outMatrix) {
        if (!matrix || !outMatrix || n <= 0) return -1;
        if (isSingular(matrix, n) == 1) return 0;

        const double EPS = 1e-9;
        std::vector<double> aug(n * 2 * n, 0.0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) aug[i * (2 * n) + j] = matrix[i * n + j];
            aug[i * (2 * n) + (n + i)] = 1.0;
        }

        for (int i = 0; i < n; ++i) {
            int pivot = i;
            for (int j = i + 1; j < n; ++j) {
                if (std::fabs(aug[j * (2 * n) + i]) > std::fabs(aug[pivot * (2 * n) + i])) {
                    pivot = j;
                }
            }

            if (std::fabs(aug[pivot * (2 * n) + i]) < EPS) return 0;

            if (i != pivot) {
                for (int k = 0; k < 2 * n; ++k) {
                    std::swap(aug[i * (2 * n) + k], aug[pivot * (2 * n) + k]);
                }
            }

            double div = aug[i * (2 * n) + i];
            for (int k = 0; k < 2 * n; ++k) aug[i * (2 * n) + k] /= div;

            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    double factor = aug[j * (2 * n) + i];
                    for (int k = 0; k < 2 * n; ++k) {
                        aug[j * (2 * n) + k] -= factor * aug[i * (2 * n) + k];
                    }
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                outMatrix[i * n + j] = aug[i * (2 * n) + (n + j)];
            }
        }
        return 1;
    }

}