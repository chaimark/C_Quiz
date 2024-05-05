#include "../C_MyLib/array.h"
#include <stdio.h>

int UserSrand() {
    int sum = 0;
    srand((unsigned)time(0));
    sum = 1 + (rand() % 10);
    return sum;
}

int main() {
    do {
        system("cls");
        int Len = UserSrand();
        int *AA = (int *)malloc(sizeof(int) * Len);
        for (int i = 0; i < Len; i++) {
            AA[i] = i;
        }
        strnew A;  // 声明别名结构体变量A
        A = NEW_NAME(AA);
        A.Len = Len;
        printf("Len = %d\n", A.Len);
        for (int i = 0; i < A.Len; i++) {
            printf("%d\n", A.Name._int[i]);
        }
        printf("按任意键继续");
        getchar();
        free(AA);
    } while (1);
    return 0;
}