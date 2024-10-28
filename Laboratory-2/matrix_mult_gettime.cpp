#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

using namespace std;

void generateMatrix(vector<vector<int>>& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, int size) {
    vector<vector<int>> result(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
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


    vector<vector<int>> matrix1(size, vector<int>(size));
    vector<vector<int>> matrix2(size, vector<int>(size));

    generateMatrix(matrix1, size);
    generateMatrix(matrix2, size);
    gettimeofday(&start2, NULL);
    vector<vector<int>> result = multiplyMatrices(matrix1, matrix2, size);

    
    gettimeofday(&end, NULL);
    double secondsAll = (start2.tv_sec+start2.tv_usec*0.000001) - (start1.tv_sec+start1.tv_usec*0.000001);
    double secondsMult = (end.tv_sec+end.tv_usec*0.000001) - (start2.tv_sec+start2.tv_usec*0.000001); 
    cout << "Seconds Allocation: " << secondsAll << endl;
    cout << "Seconds Multiplication: " << secondsMult << endl;

    return 0;
}
