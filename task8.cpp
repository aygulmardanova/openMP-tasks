#include <stdio.h>
#include <iostream>
#include <ctime>
#include <omp.h>

using namespace std;

// Написать программу, в которой объявлен массив из 16000 элементов и инициализирован так,
// что значение элемента массива равно его порядковому номеру.
// Затем создайте результирующий массив, в котором (за исключением крайних элементов) будут средние значения исходного массива:
// b[i] = (a[i-1] + a[i] + a[i+1])/3.0
// Запустите программу с 8-ю процессами при различных типах распределения работ и посмотреть время.

int main() {
    int n = 16000;
    int a[n];
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    unsigned int start_time;
    unsigned int end_time;
    double b[n];
    
    start_time = clock();
#pragma omp parallel for num_threads(8)

        for (int i = 1; i < n-1; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
        }

    end_time = clock();
    printf("1. Without scheduling: %d\n", (int) (end_time - start_time));

    start_time = clock();
#pragma omp parallel num_threads(8)
    {
#pragma omp for schedule(static, 4)
        for (int i = 1; i < n-1; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
        }
    }
    end_time = clock();
    printf("2. Static scheduling: %d\n", (int) (end_time - start_time));

    start_time = clock();
#pragma omp parallel num_threads(8)
    {
#pragma omp for schedule(dynamic, 4)
        for (int i = 1; i < n-1; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
        }
    }
    end_time = clock();
    printf("3. Dynamic scheduling: %d\n", (int) (end_time - start_time));

    start_time = clock();
#pragma omp parallel num_threads(8)
    {
#pragma omp for schedule(guided, 4)
        for (int i = 1; i < n-1; i++) {
            b[i] = (a[i-1] + a[i] + a[i+1])/3.0;
        }
    }
    end_time = clock();
    printf("4. Guided scheduling: %d\n", (int) (end_time - start_time));

    return 0;
}