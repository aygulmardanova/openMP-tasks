#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

// Написать программу, в которой, объявить и заполнить случайными значениями массив целых чисел.
// Используя возможности OpenMP найти максимальное числовое значение элементов массива, кратное 7.
// Длину массива и количество потоков определить самостоятельно. Результат выдать на экран.
// Для синхронизации числовых значений максимума используется механизм критических секций.

int main() {

    int n = 30;
    int a[n];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    int max_7 = -1;
    unsigned int start;
    unsigned int end;

    start = clock();
#pragma omp parallel shared(max_7)
    {
        for (int i = 0; i < n; i++) {
#pragma omp flush(max_7)
            if ((max_7 != -1) &&(a[i] % 7 == 0) && (a[i] > max_7)) {
#pragma omp critical
                max_7 = a[i];
            } else if (a[i] % 7 == 0)
#pragma omp critical
                max_7 = a[i];
        }
    }
    end = clock();
    printf("%d ms\n", end - start);

    printf("max: %d", max_7);
    return 0;
}
