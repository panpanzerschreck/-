// Підключимо бібліотеки
#include <iostream>
#include <chrono>
#include <random>

#include "Strassen.h"

void luDecomposition(Matrix mat, Matrix lower, Matrix upper, int n)
{


    // Decomposing matrix into Upper and Lower
    // triangular matrix
    for (int i = 0; i < n; i++)
    {
        // Upper Triangular
        for (int k = i; k < n; k++)
        {
            // Summation of L(i, j) * U(j, k)
            int sum = 0;
            for (int j = 0; j < i; j++)
                sum += (lower[i][j] * upper[j][k]);

            // Evaluating U(i, k)
            upper[i][k] = mat[i][k] - sum;
        }

        // Lower Triangular
        for (int k = i; k < n; k++)
        {
            if (i == k)
                lower[i][i] = 1; // Diagonal as 1
            else
            {
                // Summation of L(k, j) * U(j, i)
                int sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (lower[k][j] * upper[j][i]);

                // Evaluating L(k, i)

                    lower[k][i]
                        = (mat[k][i] - sum) / upper[i][i];
                
            }
        }
    }

}



void getCofactor(Matrix A, Matrix temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q) {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
int determinant(Matrix A, int n)
{
    int D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

     Matrix temp=createMatrix(n); // To store cofactors

    int sign = 1; // To store sign multiplier

    // Iterate for each element of first row
    for (int f = 0; f < n; f++) {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

// Function to get adjoint of A[N][N] in adj[N][N].
void adjoint(Matrix A, Matrix adj, int N)
{
    if (N == 1) {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1; Matrix temp=createMatrix(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign) * (determinant(temp, N - 1));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
bool inverse(Matrix A, Matrix inverse, int N)
{
    // Find determinant of A[][]
    int det = determinant(A, N);
    if (det == 0) {
        std::cout << "Singular matrix, can't find its inverse";
        return false;
    }

    // Find adjoint
    Matrix adj= createMatrix(N);
    adjoint(A, adj, N);

    // Find Inverse using formula "inverse(A) =
    // adj(A)/det(A)"
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverse[i][j] = adj[i][j] / int(det);

    return true;
}



// Основна частина
int main() {

    // Розмір матриці
    size N = 9;

    // Матриці
    Matrix A = createMatrix(N), B = createMatrix(N), C = createMatrix(N), D = createMatrix(N), E = createMatrix(N), rly=createMatrix(N);

    randomize(A, N);

    // Виведемо значення
    std::cout << "Matrix A:\n";
    print(A, N);
    std::cout << "\n\nMatrix B:\n";
    print(B, N);
    std::cout << "\n\nMatrix C:\n";
    print(C, N);


    luDecomposition(A, B, C, N);
    // Виведемо результат
    std::cout << "\n\nResult with LU decomposition:\n";
    std::cout << "\n\nThe matrix:\n";
    print(A, N);
    std::cout << "\n\nThe lower matrix:\n";
    print(B, N);
    std::cout << "\n\nThe upper matrix:\n";
    print(C, N);

    if (inverse(B,D,N)&&inverse(C,E,N))
    {
        print(strassen(D, E, N),N);
        print(sq_matrix_multiply(sq_matrix_multiply(D, E, N),A, N), N);
    }

  /*  if (inverse (A,rly,N))
    {
        print(rly, N);
    }
    std::cout << "\n\n\n\n\n\n";*/

    return 0;
}
