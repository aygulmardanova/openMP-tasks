#include <iostream>
#include <omp.h>

using namespace std;

//Объявить и присвоить начальные значения параметрам a,b.
//Две параллельные области: первая - с числом нитей 2, вторая - с числом нитей 4.
//Для первой области переменные a,b объявить защищенными, с режимом доступа private и firstprivate.
//Внутри области определить номер нити и выполнить увеличение значения переменных на эту величину.
//Выдать на экран значения переменных до входа, внутри паралл области и после выхода из паралл области.
//Для второй области переменную а объявить общей, b - защищенной, с режимом доступа private.
//Определеить номер нити и выполнить уменьшение значения переменных на эту величину.
//Выдать на экран значения переменных до входа, внутри и после выхода.

int main() {
    int a = 3, b = 3;

    printf("----------------------\n");
    printf("Parameters values before 1 block: a - %d, b - %d\n", a, b);

#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        a = 0;
        int num = omp_get_thread_num();
        a += num;
        b += num;
        printf("Hello from 1 block, %d thread, values: a - %d, b - %d\n", num, a, b);
    }
    printf("Parameters values after 1 block: a - %d, b - %d\n", a, b);

    printf("----------------------\n");

    printf("Parameters values before 2 block: a - %d, b - %d\n", a, b);
#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        b = 0;
        int num = omp_get_thread_num();
        a -= num;
        b -= num;
        printf("Hello from 2 block, %d thread, values: a - %d, b - %d\n", num, a, b);
    }
    printf("Parameters values after 2 block: a - %d, b - %d\n", a, b);
    printf("----------------------\n");

    return 0;
}