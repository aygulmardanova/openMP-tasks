#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <zconf.h>

using namespace std;

// Модифицируйте задачу 1 так, чтобы потоки распечатывали свои идентификаторы в обратном порядке.
// Существует как минимум 5 способов решения.

void first(), second(), third(), loop(int);

int n = 8;

int main() {

    omp_set_num_threads(n);

    first();
    second();
    third();

//    loop(n);

    return 0;
}

void first() {
    printf("First:\n");
    int thread = n - 1;
#pragma omp parallel for schedule(static,1)
    for (int i = 0; i < n; i++) {
        while (thread != omp_get_thread_num()) {
        }
        printf("%d, ", omp_get_thread_num());
        thread--;
    }
    printf("\n");
}

void second() {
    printf("Second:\n");
    for (int i = n - 1; i >= 0; i--) {
#pragma omp parallel
        if (omp_get_thread_num() == i) {
            printf("%d, ", omp_get_thread_num());
        }
    }
    printf("\n");
}

void third()
{
    printf("Third:\n");
    int num = 7;

#pragma omp parallel num_threads(n)
    {
        int rank = omp_get_thread_num();
        bool f = true;
        while (f) {
#pragma omp critical
            {
                if (rank == num) {
                    printf("%d, ", rank);
                    num--;
                    f = false;
                }
            }
        }
    }
    printf("\n");
}

void loop(int bound) {
    omp_set_num_threads(bound);
#pragma omp parallel for schedule(static,1)
        for (int i = 0; i < bound; i++) {
                int th = omp_get_thread_num();
//        printf("thr:%d bound:%d,", th, bound);
                if (th == bound - 1) {
                    printf("-----'%d'\n", th);
                    loop(bound - 1);
                }
        }

    printf("\n");
}
