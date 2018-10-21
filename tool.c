// 工具函数库
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INTSIZE 30
#define STRSIZE 1024

char str[STRSIZE];

// 生产一个随机的整型数组
int* rand_arr(int arr[], int length, int max)
{
    srand((unsigned)time(0)); // 设置随机数生成器种子
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % max;
    }
}

// 整型数组转换成字符串
char * arr_str(int arr[], int length)
{
    int i, len = 1;
    sprintf(str, "[");
    for (i = 0; i < length; i++) {
        sprintf(str + len, "%2d, ", arr[i]);
        len = strlen(str);
    }
    sprintf(str + len - 2, "%s", "]");
    return str;
}