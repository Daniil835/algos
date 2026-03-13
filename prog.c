#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-12  

double** get_matrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void free_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void swap_rows(double** matrix, int row1, int row2, int n) {
    if (row1 == row2) return;
    for (int j = 0; j < n; j++) {
        double temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}


double determinant_gauss(double** matrix, int n) {
    double det = 1.0;      
    int sign = 1;          

    double** a = get_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = matrix[i][j];
        }
    }
    for (int k = 0; k < n; k++) {
       
        int max_row = k;
        double max_val = fabs(a[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(a[i][k]) > max_val) {
                max_val = fabs(a[i][k]);
                max_row = i;
            }
        }
        if (max_val < EPS) {
            free_matrix(a, n);
            return 0.0;
        }

        if (max_row != k) {
            swap_rows(a, max_row, k, n);
            sign = -sign;   
        }

        for (int i = k + 1; i < n; i++) {
            double factor = a[i][k] / a[k][k];
          
            for (int j = k; j < n; j++) {
                a[i][j] -= factor * a[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        det *= a[i][i];
    }
    det *= sign;
    free_matrix(a, n);
    return det;
}

int main() {
    int n;
    scanf("%d", &n);
    double** matrix = get_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
    double det = determinant_gauss(matrix, n);
    printf("%lf", det);
    free_matrix(matrix, n);
    return 0;
}