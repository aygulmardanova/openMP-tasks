#include <stdio.h>
#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

//Используя возможности OpenMP написать программу умножения матрицы на вектор.
//Сравнить время выполнения последовательной и параллельных программ.

int main() {

    int n = 10000, k = 10000;
//    printf("Enter n and k values: \n");
//    cin >> n >> k;

    int b[k], c[k];
    int **a = new int *[n];
    for (int l = 0; l < n; ++l) {
        a[l] = new int[k];
    }
    double start_time;
    double end_time;

    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++)
            a[i][j] = rand() % 1000;
    }
    srand(time(0) + 1000);
    for (int i = 0; i < k; i++)
        b[i] = rand() % 1000;

    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }

    start_time = omp_get_wtime();
    //multiplying arrays
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            c[i] += a[i][j] * b[j];
        }
    }
    end_time = omp_get_wtime();

    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }
    double t1 = end_time - start_time;
    printf("Without pragma omp: %f s.\n", t1);

    start_time = omp_get_wtime();
//    multiplying arrays
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
#pragma omp parallel for
        for (int j = 0; j < k; j++) {
            c[i] += a[i][j] * b[j];
        }
    }
    end_time = omp_get_wtime();
    double t2 = end_time - start_time;

    printf("pragma omp for: %f s.\n", t2);

    if (t1 > t2) {
        printf("\nPragma omp is faster\n");
    } else {
        printf("\nWithout pragma omp is faster\n");
    }
    for (int l = 0; l < n; ++l) {
        delete (a[l]);
    }
    delete[] a;
    return 0;

}