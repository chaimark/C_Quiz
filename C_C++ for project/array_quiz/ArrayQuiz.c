#include "../C_MyLib/StrLib.h"
#include "ArrayQuiz.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>

int UserSrand() {
    int sum = 0;
    srand((unsigned)time(0));
    sum = 1 + (rand() % 10);
    return sum;
}

int arrayQuiz() {
    do {
        system("cls");
        int Len = UserSrand();
        int *AA = (int *)malloc(sizeof(int) * Len);
        for (int i = 0; i < Len; i++) {
            AA[i] = i;
        }
        strnew A;  // 声明别名结构体变量A
        A = NEW_NAME(AA);
        A.MaxLen = Len;
        printf("Len = %d\n", A.MaxLen);
        for (int i = 0; i < A.MaxLen; i++) {
            printf("%d\n", A.Name._int[i]);
        }
        printf("按任意键继续");
        getchar();
        free(AA);
    } while (1);
    return 0;
}