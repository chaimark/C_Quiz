#include "array.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int AA[6] = {1, 2, 3, 4, 5, 6};
    strnew A;  // ���������ṹ�����A
    // ����A
    A = NEW_NAME(AA);
    printf("Len = %d\n", A.Len);
    for (int i = 0; i < A.Len; i++) {
        printf("%d\n", A.Name._int[i]);
    }
    getch();
    return 0;
}