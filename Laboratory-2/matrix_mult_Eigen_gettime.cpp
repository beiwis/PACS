#include <iostream>
#include <Eigen/Dense>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

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
  
  struct timeval start1, start2,  end;
    gettimeofday(&start1, NULL);
    
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size_of_matrix>" << endl;
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        cerr << "Size of matrix must be a positive integer." << endl;
        return 1;
    }

    MatrixXi matrix1(size, size);
    MatrixXi matrix2(size, size);

    generateMatrix(matrix1, size);
    generateMatrix(matrix2, size);

    gettimeofday(&start2, NULL);
    MatrixXi result = matrix1 * matrix2;

    gettimeofday(&end, NULL);
    double secondsAll = (start2.tv_sec+start2.tv_usec*0.000001) - (start1.tv_sec+start1.tv_usec*0.000001);
    double secondsMult = (end.tv_sec+end.tv_usec*0.000001) - (start2.tv_sec+start2.tv_usec*0.000001); 
    cout << "Seconds Allocation: " << secondsAll << endl;
    cout << "Seconds Multiplication: " << secondsMult << endl;
    
    return 0;
}
