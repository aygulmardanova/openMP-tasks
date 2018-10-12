#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

//Определить две паралл области, каждая из которых содержит итерационную конструкцию for,
//выполняющую инициализацию элементов одномерных массивов целых чисел a[12], b[12], c[12].
//Число нитей перед первой областью задать равным 3, перед второй - 4.
//Первая паралл область выполняет инициализацию элементов массивов a, b с использованием статического распределения итераций,
//размер порции итераций выбрать самостоятельно,
//вторая паралл область выполняет инициализацию элементов массива c по следующему правилу c[i] = a[i] + b[i],
//с использованием динамического распределения итераций, размер порции итераций выбрать самостоятельно.
//В каждой области определить и выдать на экран количество нитей, номер нити и результат выполнения цикла.

int main() {
    int n = 12;
    int a[n], b[n], c[n];

#pragma omp parallel num_threads(3)
    {
#pragma omp for schedule(static,2)
        for (int i = 0; i < n; i++) {
            a[i] = i * i;
            printf("A. %d thread. total: %d. a[%d]=%d\n", omp_get_thread_num(), omp_get_num_threads(), i, a[i]);
            b[i] = i * i;
            printf("B. %d thread. total: %d. b[%d]=%d\n", omp_get_thread_num(), omp_get_num_threads(), i, b[i]);
        }
    }

    printf("-------------------\n");
#pragma omp parallel num_threads(4)
    {
#pragma omp for schedule(dynamic,3)
        for (int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
            printf("C. %d thread. total: %d. c[%d]=%d\n", omp_get_thread_num(), omp_get_num_threads(), i, c[i]);
        }
    }

    printf("Array a[%d]:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\nArray b[%d]:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("\nArray c[%d]:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}
