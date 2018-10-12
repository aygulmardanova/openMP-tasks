#include <stdio.h>
#include <iostream>
#include <omp.h>

using namespace std;

//Написать программу, в которой объявить и присвоить начальные значения целочисленным массивам a[10] и b[10].
//Используя конструкцию parallel for и reduction вычислить средние арифметические значения элементов массивов a и b,
//сравнить полученные значения, результат выдать на экран.

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

    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0; i < n; i++) {
        sum1 += a[i];
        sum2 += b[i];
    }
    printf("sum1: %d\nsum2: %d\n", sum1, sum2);

    int sumA = 0;
    int sumB = 0;
    double avgA, avgB;
#pragma omp parallel reduction(+:sumA) reduction(+:sumB)
        {
            for (int i = 0; i < n; i++) {
                sumA += a[i];
                sumB += b[i];

            }
        }
    avgA = (double) sumA / (double) n;
    printf("Avg for a: %.2f\n", avgA);
    avgB = (double) sumB / (double) n;
    printf("Avg for b: %.2f\n", avgB);

    if (avgA > avgB) {
        printf("Average for a is bigger: %.2f > %.2f\n", avgA, avgB);
    } else if (avgA < avgB) {
        printf("Average for b is bigger: %.2f < %.2f\n", avgA, avgB);
    } else {
        printf("Averages are equivalent for a and b: %.2f = %.2f\n", avgA, avgB);
    }
    return 0;
}