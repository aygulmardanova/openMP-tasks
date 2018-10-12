#include <iostream>
#include <omp.h>

using namespace std;

//В программе объявить и присвоить начальные значения двумерному массиву d[6][8]
//Для инициализации значений использовать генератор случайных чисел
//Используя конструкцию директивы sections...section определить три секции для выполнения след операций:
//первая секция - выполняет вычисление среднего арифм значения элементов двумерного массива
//вторая секция - выполняет вычисление мин и макс значений элементов двумерного массива
//третья секция - выполняет вычисление количества элементов массива, значения которых кратны 3
//В каждой секции определить и выдать на экран номер исполняющей нити и результат вычислений.

int main() {
    int n = 6, k = 8;
    int d[n][k];
    printf("-------Array d[%d][%d]:\n", n, k);
    srand((unsigned int) time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            d[i][j] = rand() % 100;
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }

#pragma omp parallel sections
    {
#pragma omp section
        {
            double avg = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < k; j++) {
                    if (d[i][j] % 3 == 0) {
                        avg += d[i][j];
                    }
                }
            }
            avg /= (n * k);
            int num = omp_get_thread_num();
            printf("--------1 section--------\n"
                           "%d thread. Arithmetical average for array d[%d][%d]: %f\n"
                           "------------1------------\n\n",
                   num, n, k, avg);
        }
#pragma omp section
        {
            int min = d[0][0];
            int max = d[0][0];
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < k; j++) {
                    if (d[i][j] < min) {
                        min = d[i][j];
                    } else if (d[i][j] > max) {
                        max = d[i][j];
                    }
                }
            }
            int num = omp_get_thread_num();
            printf("--------2 section--------\n"
                           "%d thread. Min for array d[%d][%d]: %d\n"
                           "%d thread. Max for array d[%d][%d]: %d\n"
                           "------------2------------\n\n",
                   num, n, k, min, num, n, k, max);
        }
#pragma omp section
        {
            int count = 0;
            int num = omp_get_thread_num();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < k; j++) {
                    if (d[i][j] % 3 == 0) {
                        count++;
                        printf("%d ", d[i][j]);
                    }
                }
            }
            printf("\n--------3 section--------\n"
                           "%d thread. Multiple of 3 values count for array d[%d][%d]: %d\n"
                           "------------3------------\n",
                   num, n, k, count);
        }

    }
    return 0;
}