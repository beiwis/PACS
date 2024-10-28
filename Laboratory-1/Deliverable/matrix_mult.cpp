#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <size_of_matrix>" << endl;
        return 1;
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        cerr << "Size of matrix must be a positive integer." << endl;
        return 1;
    }

    // srand(time(0));

    vector<vector<int>> matrix1(size, vector<int>(size));
    vector<vector<int>> matrix2(size, vector<int>(size));

    generateMatrix(matrix1, size);
    generateMatrix(matrix2, size);

    cout << "Matrix 1:" << endl;
    printMatrix(matrix1, size);

    cout << "Matrix 2:" << endl;
    printMatrix(matrix2, size);

    vector<vector<int>> result = multiplyMatrices(matrix1, matrix2, size);

    cout << "Resultant Matrix:" << endl;
    printMatrix(result, size);

    return 0;
}