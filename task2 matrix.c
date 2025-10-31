#include <stdio.h>
#include <stdlib.h>
#define ROWS 3
#define COLS 3
void readMatrix(int matrix[][COLS], int rows, int cols, int num) {
    int i, j;
    printf("\nEnter elements for Matrix %d (%dx%d):\n", num, rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nMatrix %d entered:\n", num);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void displayMatrix(int matrix[][COLS], int rows, int cols) {
    int i, j;
    printf("Matrix (%dx%d):\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void addMatrices(int a[][COLS], int b[][COLS], int result[][COLS], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}
void multiplyMatrices(int a[][COLS], int b[][COLS], int result[][COLS], int rowsA, int colsA, int colsB) {
    int i, j, k;
    // Initialize result matrix with 0
    for (i = 0; i < rowsA; i++) {
        for (j = 0; j < colsB; j++) {
            result[i][j] = 0;
        }
    }
    for (i = 0; i < rowsA; i++) {
        for (j = 0; j < colsB; j++) {
            for (k = 0; k < colsA; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
void transposeMatrix(int matrix[][COLS], int result[][COLS], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}
int main() {
    int choice;
    int matrix1[ROWS][COLS], matrix2[ROWS][COLS], result[ROWS][COLS];
    printf("Matrix Operations Menu:\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("\n+++++ Matrix Addition +++++\n");
            readMatrix(matrix1, ROWS, COLS, 1);
            readMatrix(matrix2, ROWS, COLS, 2);
            addMatrices(matrix1, matrix2, result, ROWS, COLS);
            printf("Result of Addition:\n");
            displayMatrix(result, ROWS, COLS);
            break;
        case 2:
            printf("\n+++++ Matrix Multiplication +++++\n");
            readMatrix(matrix1, ROWS, COLS, 1);
            readMatrix(matrix2, ROWS, COLS, 2);
            multiplyMatrices(matrix1, matrix2, result, ROWS, COLS, COLS);
            printf("Result of Multiplication:\n");
            displayMatrix(result, ROWS, COLS);
            break;
        case 3:
            printf("\n+++++ Matrix Transpose +++++\n");
            readMatrix(matrix1, ROWS, COLS, 1);
            transposeMatrix(matrix1, result, ROWS, COLS);
            printf("Transpose of the Matrix:\n");
            displayMatrix(result, COLS, ROWS);
            break;
        default:
            printf("Invalid choice. Please select 1, 2, or 3.\n");
            break;
    }
    return 0;
}

