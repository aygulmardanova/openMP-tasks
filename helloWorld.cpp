#include <iostream>
#include <omp.h>

using namespace std;

// Task 1
// Каждый поток печатает id потока, кол-во потоков всего и строчку Hello world. Запустить программу с 8 потоками.
int main() {
    int size;

#pragma omp parallel num_threads(8)
    {
//        int k = 5;
#pragma omp for
        for (int i = 0; i < 8; i++) {
            size = omp_get_num_threads();
            int rank = omp_get_thread_num();

            printf("Hello world! Threads count: %d. Thread %d\n", size, rank);
        }
    }
    return 0;
}