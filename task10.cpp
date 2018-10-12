#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

// Написать программу, в которой объявить и присвоить начальные значения элементам двумерного массива d[6][8],
// для инициализации значений использовать генератор случайных чисел.
// Используя конструкцию директивы omp parallel for и omp critical определить
// минимальное и максимальное значения элементов двумерного массива.
// Количество нитей задать самостоятельно. Результат выдать на экран.

int main() {

    int n = 6, k = 8;
    int d[n][k];
    unsigned int start;
    unsigned int end;

    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            d[i][j] = rand() % 100;
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

    int min = d[0][0];
    int max = d[0][0];

//    start = clock();
//#pragma omp critical
//    {
//        for (int i = 0; i < n; i++)
//            for (int j = 0; j < k; j++) {
//                if (d[i][j] > max) {
//                    max = d[i][j];
//                } else if (d[i][j] < min) {
//                    min = d[i][j];
//                }
//            }
//    }
//    end = clock();
//    printf("time: %d.\n", end - start);
//    
    //second type
    start = clock();
#pragma omp parallel for
    for (int i = 0; i < n; i++)
#pragma omp parallel for
            for (int j = 0; j < k; j++) {
#pragma omp critical
                    {
                        if (d[i][j] > max) {
                            max = d[i][j];
                        }
                    }
#pragma omp critical
                    {
                        if (d[i][j] < min) {
                            min = d[i][j];
                        }
                    }
                }
    end = clock();
    printf("2 time: %d.\n", end - start);

    printf("max: %d, min: %d.", max, min);
    return 0;
}
