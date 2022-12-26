#ifndef SECONDARY_HPP
#define SECONDARY_HPP

// Підключимо бібліотеки
#include <iostream>
#include <chrono>
#include <random>

// Додамо імена
using type = int;
using Matrix = type**;
using size = std:: size_t;


// Сам код для надання матрицям випадкових значеннь

    void randomize(Matrix & A, size N) {  // O(n^2)

        for (unsigned int i = 0; i < N; i++) {
            for (unsigned int j = 0; j < N; j++) {
                A[i][j] = rand()%110;
            }
        }
    }


// Виведемо функцію
void print(Matrix A, size N) {  // O(n^2)
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


// Повернемо нову матрицю NxN
Matrix createMatrix(size N) {
    Matrix newMatrix = new type * [N];
    for (unsigned int i = 0; i < N; i++) {
        newMatrix[i] = new type[N];
        for (unsigned int j = 0; j < N; j++) {
            newMatrix[i][j] = 0;
        }
    }

    return newMatrix;
}


/*////////////////////////////////////////////////////////////////
/                                                                /
/                      Операції з матрицями                      /
/                                                                /
////////////////////////////////////////////////////////////////*/


// Додамо дві матриці
Matrix add(Matrix A, Matrix B, size N) {

    Matrix C = createMatrix(N);

    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

// Віднімемо дві матриці
Matrix subtract(Matrix A, Matrix B, size N) {
    Matrix C = createMatrix(N);

    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}


#endif // !SECONDARY_HPP