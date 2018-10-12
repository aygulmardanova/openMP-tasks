#include <iostream>
#include <omp.h>

using namespace std;

//Написать программу, в которой присвоить начальные занчения массивам a[10], b[10]
//Определить паралл область, кол-во нитей задать 2, выделить код для основной нити (номер 0) и нити с номером 1.
//Основная нить должна искать min значение массива a
//Нить с номером 1 - искать max массива b
//Результат выдать на экран.

int main() {
    int n = 10;

    int a[n], b[n];
    //Arrays initialization
    printf("-------------------\n");
    printf("array a[%d]:\n", n);
    srand((unsigned int) time(0));
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }

    printf("\n-------------------\n");
    printf("array b[%d]\n", n);
    srand((unsigned int) time(0) + 1000);
    for (int i = 0; i < n; i++) {
        b[i] = rand() % 100;
        printf("%d ", b[i]);
    }
    printf("\n-------------------\n");

    int num;
#pragma omp parallel num_threads(2)
    {
        num = omp_get_thread_num();
        if (num == 0) { //master, search for min a
            int min = a[0];
            for (int i = 1; i < n; i++) {
                if (a[i] < min)
                    min = a[i];
            }
            printf("Min for array a[%d] - %d\n", n, min);
        } else { //2 thread, search for max b
            int max = b[0];
            for (int i = 1; i < n; i++) {
                if (b[i] > max)
                    max = b[i];
            }
            printf("Max for array b[%d] - %d\n", n, max);
        }
    }

    return 0;
}


