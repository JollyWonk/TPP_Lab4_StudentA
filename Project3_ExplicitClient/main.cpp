#include <iostream>
#include <iomanip>
#include <windows.h>

typedef bool (*PowerMethodFunc)(const double* A, int n, double* outEigenvalue, double* outEigenvector, double tol, int maxIter);
typedef bool (*EigenvalueFunc)(const double* A, int n, double* outEigenvalue);
typedef bool (*EigenvectorFunc)(const double* A, int n, double* outEigenvector);
typedef double (*ResidualFunc)(const double* A, double lambda, const double* v, int n);

int main() {
    std::cout << "=========================================================" << std::endl;
    std::cout << "  Student A: Testing Partner's Library (Explicit Linking)" << std::endl;
    std::cout << "  Variant 5: Eigenvalues & Eigenvectors via WinAPI" << std::endl;
    std::cout << "=========================================================\n" << std::endl;

    std::cout << "[Step 1] Loading DLL via LoadLibrary()..." << std::endl;
    HMODULE hLib = LoadLibrary(TEXT("EigenLib.dll"));

    if (!hLib) {
        std::cerr << "[-] Error: Failed to load EigenLib.dll! Check if the DLL is located near the exe." << std::endl;
        return 1;
    }
    std::cout << "[+] DLL loaded successfully into process memory!\n" << std::endl;

    std::cout << "[Step 2] Resolving function addresses via GetProcAddress()..." << std::endl;
    auto powerMethod = reinterpret_cast<PowerMethodFunc>(GetProcAddress(hLib, "powerMethod"));
    auto eigenvalue = reinterpret_cast<EigenvalueFunc>(GetProcAddress(hLib, "eigenvalue"));
    auto eigenvector = reinterpret_cast<EigenvectorFunc>(GetProcAddress(hLib, "eigenvector"));
    auto residual = reinterpret_cast<ResidualFunc>(GetProcAddress(hLib, "residual"));

    if (!powerMethod || !eigenvalue || !eigenvector || !residual) {
        std::cerr << "[-] Error: One or more functions could not be found in DLL export table!" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }
    std::cout << "[+] All 4 functions found and resolved successfully!\n" << std::endl;

    const int n = 2;
    double A[4] = {
        2.0, 1.0,
        1.0, 2.0
    };

    double lambda = 0.0;
    double v[2] = { 0.0, 0.0 };

    std::cout << "[Step 3] Executing functions:" << std::endl;

    if (eigenvalue(A, n, &lambda)) {
        std::cout << " -> eigenvalue(): SUCCESS | Dominant Eigenvalue = "
            << std::fixed << std::setprecision(4) << lambda
            << " (Expected: ~3.0000)" << std::endl;
    }

    if (eigenvector(A, n, v)) {
        std::cout << " -> eigenvector(): SUCCESS | Eigenvector = [ "
            << v[0] << ", " << v[1] << " ]" << std::endl;
    }

    double res = residual(A, lambda, v, n);
    std::cout << " -> residual():    SUCCESS | Residual norm = "
        << std::scientific << res << std::endl;

    std::cout << "\n[Step 4] Testing Edge Cases & Stability (Nullptr tests):" << std::endl;
    bool nullCheck = eigenvalue(nullptr, n, &lambda);
    std::cout << " -> Passing nullptr matrix: "
        << (!nullCheck ? "SAFE (Returned false, no crash)" : "Unexpected") << std::endl;

    std::cout << "\n[Step 5] Unloading DLL via FreeLibrary()..." << std::endl;
    FreeLibrary(hLib);
    std::cout << "[+] DLL successfully unloaded from memory." << std::endl;

    return 0;
}