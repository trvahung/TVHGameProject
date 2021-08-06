// Lesson1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

void RefSwap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void PointerSwap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a, b;
    printf("Nhap so thu nhat: a=");
    scanf("%d", &a);
    printf("Nhap so thu hai: b=");
    scanf("%d", &b);
    //RefSwap(a, b);
    PointerSwap(&a, &b);
    printf("Ket qua sau khi hoan doi: a=%d va b=%d", a, b);
}

