#include <omp.h>
#include <iostream>

using namespace std;

// Task 2
// Написать программу, в которой определить две параллельные области,
// выполнение которых зависит от условного оператора #pragma omp parallel if(…),
// если заданное значение числа нитей больше 1, параллельная область выполняется, иначе не выполняется.
// Число нитей перед первой областью задать равным 3, перед второй – равным 1.
// Внутри параллельных областей определить количество нитей и номер каждой нити, результат выдать на экран.

int main() {
    int size1 = 3;
    int size2 = 1;

    omp_set_num_threads(size1);
#pragma omp parallel if (size1 > 1)
    {
#pragma omp if(omp_in_parallel())
        {
            printf("Hello from 1 block, %d thread, altogether: %d threads\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }

    omp_set_num_threads(size2);
#pragma omp parallel if (size2 > 1)
    {
#pragma omp if(omp_in_parallel())
        {
            printf("Hello from 2 block, %d thread, altogether: %d threads\n", omp_get_thread_num(), omp_get_num_threads());
        }
    }

    return 0;
}