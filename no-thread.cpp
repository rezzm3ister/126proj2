#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void matrixMult(int **A, int **B, int rowA, int colA, int rowB, int colB, float duration) // modeled after comparch lab
{
    int **matA;
    int **matB;
    int **product;
    int tempA, tempB;
    int passesA, passesB;

    auto start = steady_clock::now();
    while (duration_cast<seconds>(steady_clock::now() - start).count() < duration)
    {
        for (int i = 0; i < rowA; i++) // first matrix
        {
            for (int j = 0; j < colA; j++)
            {
                tempA = rand() % 100000;
                matA[i][j] = tempA;
                // passesA++;
            }
        }

        for (int k = 0; k < rowB; k++) // second matrix
        {
            for (int l = 0; l < colB; l++)
            {
                tempB = rand() % 100000;
                matB[k][l] = tempB;
                // passesB++;
            }
        }
        // cout << passesA << ", " << passesB << endl;

        for (int m = 0; m < rowA; m++) // multiply
        {
            for (int n = 0; n < colB; n++)
            {
                for (int o = 0; o < colA; o++)
                {
                    // dot product
                    product[m][n] += matA[m][o] * matB[o][n];
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    const double duration = 5.0;
    int tempA, tempB, passes;
    int row1, col1, row2, col2;

    int **mat1, **mat2;

    cout << "Enter first matrix row ---: ";
    cin >> row1;
    cout << "Enter first matrix column |||: ";
    cin >> col1;
    cout << "Enter second matrix row ---: ";
    cin >> row2;
    cout << "Enter second matrix column |||: ";
    cin >> col2;

    // can't function kasi mawawala row and col values
    while (col1 != row2)
    {
        cout << "Column 1 and Row 2 should have the same dimensions." << endl;
        cout << "Enter first matrix row ---: ";
        cin >> row1;
        cout << "Enter first matrix column |||: ";
        cin >> col1;
        cout << "Enter second matrix row ---: ";
        cin >> row2;
        cout << "Enter second matrix column |||: ";
        cin >> col2;
    }

    matrixMult(mat1, mat2, row1, col1, row2, col2, duration);

    /*
    auto start = steady_clock::now();
    while (duration_cast<seconds>(steady_clock::now() - start).count() < duration)
    {
        for (int i = 0; i < 10; i++)
        {
            tempA = rand() % 100000;
            tempB = rand() % 100000;
            // matrixMult(tempA, tempB);
            passes++;
        }
    }

    cout << passes << endl;
    */

    return 0;
}