#include "CsvSplit.h"
#include <stdio.h>  

int csvSplit(int argc, char *argv[]) {  
    printf("程序名: %s\n", argv[0]);  
    printf("共接收到 %d 个参数。\n", argc - 1); // 减1是因为argv[0]是程序名  
  
    for(int i = 1; i < argc; i++) {  
        printf("参数 %d: %s\n", i, argv[i]);  
    }  
  
    return 0;  
}