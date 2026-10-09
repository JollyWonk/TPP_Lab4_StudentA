#include <iostream>
#include <iomanip>
#include "MatrixAnalysis.h"

int main() {
    std::cout << "=== Student A: Variant 5 - Matrix Analysis (Static Lib) ===" << std::endl;

    const int n = 3;

    double A[9] = {
         2.0,  1.0, -1.0,
        -3.0, -1.0,  2.0,
        -2.0,  1.0,  2.0
    };
    double invA[9] = { 0.0 };

    double det = MatrixAnalysis::determinant(A, n);
    bool singular = MatrixAnalysis::isSingular(A, n);
    int r = MatrixAnalysis::rank(A, n, n);

    std::cout << "Determinant: " << det << " (Expected: -1.0)" << std::endl;
    std::cout << "Is Singular: " << (singular ? "Yes" : "No") << std::endl;
    std::cout << "Rank:        " << r << " (Expected: 3)" << std::endl;

    if (MatrixAnalysis::inverse(A, n, invA)) {
        std::cout << "\nInverse Matrix:" << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        for (int i = 0; i < n; ++i) {
            std::cout << "[ ";
            for (int j = 0; j < n; ++j) {
                std::cout << std::setw(6) << invA[i * n + j] << " ";
            }
            std::cout << "]" << std::endl;
        }
    }

    return 0;
}