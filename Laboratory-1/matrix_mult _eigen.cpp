#include <iostream>
#include <Eigen/Dense>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace Eigen;

void generateMatrix(MatrixXi& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix(i, j) = rand() % 10; // Random values between 0 and 9
        }
    }
}

void printMatrix(const MatrixXi& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix(i, j) << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size_of_matrix>" << endl;
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        cerr << "Size of matrix must be a positive integer." << endl;
        return 1;
    }

    srand(time(0));

    MatrixXi matrix1(size, size);
    MatrixXi matrix2(size, size);

    generateMatrix(matrix1, size);
    generateMatrix(matrix2, size);

    cout << "Matrix 1:" << endl;
    printMatrix(matrix1, size);

    cout << "Matrix 2:" << endl;
    printMatrix(matrix2, size);

    MatrixXi result = matrix1 * matrix2;

    cout << "Resultant Matrix:" << endl;
    printMatrix(result, size);

    return 0;
}
