#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>  // for strtol

// matrix should be n x n
// This function creates a n x n matrix with random integers
int** createMatrix(int n){
    int** matrix = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        matrix[i] = malloc(5 * sizeof(int));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            matrix[i][j] = rand() + 1;
        }
    }

    return matrix;
}

int* createVector(int n){
    int* vector = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        vector[i] = ((rand() % 10) + 1);
    }

    return vector;
}

int** testMatrix(int n){
    int** matrix = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        matrix[i] = malloc(5 * sizeof(int));
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            matrix[i][j] = i+1;
        }
    }

    return matrix;
}

int* testVector(int n){
    int* vector = (int*)malloc(n * sizeof(int));
    for(int i = n; i > 0; i--){
        vector[i] = i;
    }

    return vector;
}

void finalVector(float* vector, int n){
    for(int i = 0; i < n; i++){
        printf("%f ", vector[i]);
    }
    printf("\n");
}

// For debugging
void printMatrix(int** matrix, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printVector(int* vector, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int xj (int** matrix, int* vector, int j, int m){
    int sum = 0;
    for(int i = 0; i < m; i++){
        sum += matrix[i][j];
    }
    return sum;
}

int x2j (int** matrix, int* vector, int j, int m) {
    int sum = 0;
    for(int i = 0; i < m; i++){
        // square
        sum += (matrix[i][j] * matrix[i][j]);
    }
    return sum;
}

int y (int** matrix, int* vector, int j, int m) {
    int sum = 0;
    for(int i = 0; i < m; i++){
        // square
        sum += (vector[i]);
    }
    return sum;
}

int y2 (int** matrix, int* vector, int j, int m) {
    int sum = 0;
    for(int i = 0; i < m; i++){
        // square
        sum += (vector[i] * vector[i]);
    }
    return sum;
}

int x2y (int** matrix, int* vector, int j, int m) {
    int sum = 0;
    for(int i = 0; i < m; i++){
        // square
        sum += (matrix[i][j] * vector[i]);
    }
    return sum;
}


// pearson coefficient function
float* pearson_cor(int** matrix, int* vector, int m){
    // define v(n) as a vector
    float* v = (float*)malloc(sizeof(float)*m);
    // for i:=1 to n
    for (int i = 0; i < m; i++){
        // begin
        // Summations
        float x = (float) xj(matrix, vector, i, m);
        float x2 = (float) x2j(matrix, vector, i, m);
        float yj = (float) y(matrix, vector, i, m);
        float y2j = (float) y2(matrix, vector, i, m);
        float x2yj = (float) x2y(matrix, vector, i, m);

        // whole formula
        v[i] = ( ((m*(x2yj)-(x*yj))) / sqrt(((m*x2)-(x*x))*((m*y2j) - (yj*yj))) );
    }
    return v;
}

int main(int argc, char* argv[]){
    clock_t t;

    // For random number generator
    srand(time(NULL));

    int n = strtol(argv[1], NULL, 10);

    int** matrix = createMatrix(n);

    int* vector = createVector(n);


    // For debugging purposes
    // int** matrix = testMatrix(3);
    // int* vector = testVector(3);

    // time start
    t = clock();

    // Create a vector which will contain all of the answers
    float* r = pearson_cor(matrix, vector, n);

    t = clock() - t;

    double time_taken = ((double)t) / CLOCKS_PER_SEC; // Calculate the elapsed time

    printf("time elapsed: %f seconds\n", time_taken);

    // Free the memory
    free(vector);

    for(int i = 0; i < n; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
