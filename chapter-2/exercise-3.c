#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct vector {
    int dimension;
    double* data;
};

struct vector* new(unsigned int n);
struct vector* add(struct vector* v, struct vector* w);
struct vector* smul(double s, struct vector* v);

struct vector* new(unsigned int n) {

    struct vector* newVector = calloc(1, sizeof(struct vector));

    newVector->dimension = n;
    newVector->data = calloc(n, sizeof(double));

    return newVector;
}

struct vector* add(struct vector* v, struct vector* w) {

    struct vector* finalVector = NULL;

    if (v->dimension == w->dimension) {
        int dimension = v->dimension;
        finalVector = new(dimension);

        for (int i = 0; i < dimension; i++) {
            finalVector->data[i] = v->data[i] + w->data[i];
        }
    }

    return finalVector;
}

struct vector* smul(double s, struct vector* v) {

    int dimension = v->dimension;
    struct vector* finalVector = new(dimension);

    for (int i = 0; i < dimension; i++) {
        finalVector->data[i] = v->data[i] * s;
    }

    return finalVector;
}

void print(struct vector* v) {
    printf("Vector(%d) { \n", v->dimension);
    for (int i = 0; i < v->dimension; i++) {
        printf("\t [%d] = %f\n", i, v->data[i]);
    }
    printf("}\n");
}

int main() {

    struct vector* v1 = new(5);

    v1->data[0] = 10;
    v1->data[1] = 11;
    v1->data[2] = 14;
    v1->data[3] = 17;
    v1->data[4] = 19;

    struct vector* v2 = add(v1, v1);
    struct vector* v3 = smul(5, v1);

    print(v1);
    print(v2);
    print(v3);

    free(v1);
    free(v2);
    free(v3);

    return EXIT_SUCCESS;
}
