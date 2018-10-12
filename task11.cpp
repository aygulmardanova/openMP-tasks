#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

// Написать программу, в которой объявить и присвоить начальные значения массиву целых чисел a[30],
// для инициализации значений использовать генератор случайных чисел.
// Используя конструкцию omp parallel for и omp atomic вычислить количество элементов массива,
// числовые значения которых кратны 9. Количество нитей задать самостоятельно.

int main() {

    int n = 30;
    int a[n];

    //initialization
    srand(time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
    }

    printf("Elements: ");
    int count = 0;
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (a[i] % 9 == 0) {
#pragma omp atomic
            count++;
            printf("%d ", a[i]);
        }
    }

    printf("\nCount: %d", count);
    return 0;
}