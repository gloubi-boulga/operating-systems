#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct matrix {
    int row;
    int column;
    double **data;
};

struct matrix* new(unsigned int m, unsigned int n);
struct matrix* mul(struct matrix* m1, struct matrix* m2);

struct matrix* new(unsigned int m, unsigned int n) {
    struct matrix* newMatrix = calloc(1, sizeof(struct matrix));
    newMatrix->row = m;
    newMatrix->column = n;
    newMatrix->data = calloc(m, sizeof(double *)); // Allocate memory for rows
    for (int i = 0; i < m; i++) {
        newMatrix->data[i] = calloc(n, sizeof(double)); // Allocate memory for columns
    }
    return newMatrix;
}

struct matrix* mul(struct matrix* m1, struct matrix* m2) {
    struct matrix* finalMatrix = NULL;
    if (m1->column == m2->row) {
        finalMatrix = new(m1->row, m2->column);
        for (int i = 0; i < m1->row; i++) {
            for (int j = 0; j < m2->column; j++) {
                for (int k = 0; k < m1->column; k++) {
                    finalMatrix->data[i][j] += m1->data[i][k] * m2->data[k][j];
                }
            }
        }
    }
    return finalMatrix;
}

void print(struct matrix* m) {
    for (int i = 0; i < m->row; i++) {
        for (int j = 0; j < m->column; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {

    struct matrix* m1 = new(1, 3);
    struct matrix* m2 = new(3, 4);

    m1->data[0][0] = 3;
    m1->data[0][1] = 4;
    m1->data[0][2] = 2;

    m2->data[0][0] = 13;
    m2->data[0][1] = 9;
    m2->data[0][2] = 7;
    m2->data[0][3] = 15;

    m2->data[1][0] = 8;
    m2->data[1][1] = 7;
    m2->data[1][2] = 4;
    m2->data[1][3] = 6;

    m2->data[2][0] = 6;
    m2->data[2][1] = 4;
    m2->data[2][2] = 0;
    m2->data[2][3] = 3;

    struct matrix* m3 = mul(m1, m2);

    print(m1);
    print(m2);
    print(m3);

    free(m1);
    free(m2);
    free(m3);

    return EXIT_SUCCESS;
}
