#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

using Matrix = vector<vector<int>>;

void printMatrix(const Matrix& matrix)
{
    for (const auto& row : matrix)
    {
        for (int value : row)
        {
            cout << setw(4) << value;
        }
        cout << endl;
    }
    cout << endl;
}

bool loadMatrices(const string& filename, Matrix& A, Matrix& B)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error: could not open file." << endl;
        return false;
    }

    int N;
    if (!(file >> N) || N <= 0)
    {
        cerr << "Error: invalid matrix size." << endl;
        return false;
    }

    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!(file >> A[i][j]))
            {
                cerr << "Error: not enough values for Matrix A." << endl;
                return false;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!(file >> B[i][j]))
            {
                cerr << "Error: not enough values for Matrix B." << endl;
                return false;
            }
        }
    }

    return true;
}

Matrix addMatrices(const Matrix& A, const Matrix& B)
{
    int N = A.size();
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }

    return result;
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B)
{
    int N = A.size();
    Matrix result(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

void printDiagonalSums(const Matrix& matrix)
{
    int N = matrix.size();
    int mainSum = 0;
    int secondarySum = 0;

    for (int i = 0; i < N; i++)
    {
        mainSum += matrix[i][i];
        secondarySum += matrix[i][N - 1 - i];
    }

    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
    cout << endl;
}

bool swapRows(Matrix& matrix, int row1, int row2)
{
    int N = matrix.size();

    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N)
    {
        cerr << "Error: invalid row index." << endl;
        return false;
    }

    swap(matrix[row1], matrix[row2]);
    return true;
}

bool swapColumns(Matrix& matrix, int col1, int col2)
{
    int N = matrix.size();

    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N)
    {
        cerr << "Error: invalid column index." << endl;
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        swap(matrix[i][col1], matrix[i][col2]);
    }

    return true;
}

bool updateElement(Matrix& matrix, int row, int col, int newValue)
{
    int N = matrix.size();

    if (row < 0 || row >= N || col < 0 || col >= N)
    {
        cerr << "Error: invalid matrix index." << endl;
        return false;
    }

    matrix[row][col] = newValue;
    return true;
}

int main()
{
    string filename;
    Matrix A;
    Matrix B;

    cout << "Enter input filename: ";
    cin >> filename;

    if (!loadMatrices(filename, A, B))
    {
        return 1;
    }

    cout << "Matrix A:" << endl;
    printMatrix(A);

    cout << "Matrix B:" << endl;
    printMatrix(B);

    cout << "A + B:" << endl;
    Matrix sum = addMatrices(A, B);
    printMatrix(sum);

    cout << "A * B:" << endl;
    Matrix product = multiplyMatrices(A, B);
    printMatrix(product);

    cout << "Diagonal sums for Matrix A:" << endl;
    printDiagonalSums(A);

    Matrix rowSwap = A;
    cout << "Problem 5 - Rows 0 and 2 swapped:" << endl;
    if (swapRows(rowSwap, 0, 2))
    {
        printMatrix(rowSwap);
    }

    Matrix columnSwap = A;
    cout << "Problem 6 - Columns 0 and 2 swapped:" << endl;
    if (swapColumns(columnSwap, 0, 2))
    {
        printMatrix(columnSwap);
    }

    Matrix updated = A;
    cout << "Problem 7 - Updated matrix:" << endl;
    if (updateElement(updated, 1, 2, 99))
    {
        printMatrix(updated);
    }

    return 0;
}
