#include <iostream>
#include <iomanip>
#include <vector>
#include "EigenAnalysis.h"

int main() {
    std::cout << "=========================================================" << std::endl;
    std::cout << "  Student A: Testing Partner's Library (Implicit Linking)" << std::endl;
    std::cout << "  Variant 5: Eigenvalues & Eigenvectors" << std::endl;
    std::cout << "=========================================================\n" << std::endl;

    const int n = 2;
    double A[4] = {
        2.0, 1.0,
        1.0, 2.0
    };

    double lambda = 0.0;
    double v[2] = { 0.0, 0.0 };

    std::cout << "[1] Testing Standard Cases:" << std::endl;

    if (eigenvalue(A, n, &lambda)) {
        std::cout << " -> eigenvalue(): SUCCESS | Dominant Eigenvalue = "
            << std::fixed << std::setprecision(4) << lambda
            << " (Expected: ~3.0000)" << std::endl;
    }
    else {
        std::cout << " -> eigenvalue(): FAILED" << std::endl;
    }

    if (eigenvector(A, n, v)) {
        std::cout << " -> eigenvector(): SUCCESS | Eigenvector = [ "
            << v[0] << ", " << v[1] << " ]" << std::endl;
    }
    else {
        std::cout << " -> eigenvector(): FAILED" << std::endl;
    }

    double pmLambda = 0.0;
    double pmVector[2] = { 0.0, 0.0 };
    if (powerMethod(A, n, &pmLambda, pmVector, 1e-6, 1000)) {
        std::cout << " -> powerMethod(): SUCCESS | Lambda = " << pmLambda
            << " | Vector = [ " << pmVector[0] << ", " << pmVector[1] << " ]" << std::endl;
    }
    else {
        std::cout << " -> powerMethod(): FAILED" << std::endl;
    }

    double res = residual(A, lambda, v, n);
    std::cout << " -> residual():    SUCCESS | Residual norm = "
        << std::scientific << res << " (Near 0.0)" << std::endl;

    std::cout << "\n[2] Testing Edge Cases & Stability:" << std::endl;

    bool testNullptr = eigenvalue(nullptr, n, &lambda);
    std::cout << " -> Call with nullptr matrix: "
        << (!testNullptr ? "HANDLED SAFELY (Returned false)" : "UNEXPECTED") << std::endl;

    bool testInvalidDim = eigenvalue(A, -1, &lambda);
    std::cout << " -> Call with invalid dimension (n = -1): "
        << (!testInvalidDim ? "HANDLED SAFELY (Returned false)" : "UNEXPECTED") << std::endl;

    bool testNullOut = eigenvalue(A, n, nullptr);
    std::cout << " -> Call with nullptr output buffer: "
        << (!testNullOut ? "HANDLED SAFELY (Returned false)" : "UNEXPECTED") << std::endl;

    std::cout << "\nAll implicit tests finished without crashes!" << std::endl;
    return 0;
}