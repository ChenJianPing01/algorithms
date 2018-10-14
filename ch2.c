// 第2章 算法基础
#include <stdio.h>
#include <limits.h>
#include <string.h>
#define STRSIZE 512
char res[STRSIZE];

// 数组转换成字符串
char* arr2str(char * res, int arr[], int length) {
    int i, len;
    char *s;
    res = "[";
    for (i = 0; i < length; i++) {
        sprintf(s, "%d, ", arr[i]);
        strcat(res, s);
    }
    len = strlen(res);
    res[len - 1] = ']';
    res[len] = '\0';
    return res;
}

// 2.1-1 插入排序
// 2.1-2 只需更改while循环条件的比较符合即可）
void insert_sort(int arr[], int length) {
    printf("Old: %s", arr2str(res, arr, length));
    int i, j, key, step = 0; 
    for ( j = 1; j < length; j++ ) {
        key = arr[j];
        i = j - 1;
        while (i >= 0 && arr[i] > key ) {
            arr[i + 1] = arr[i];
            i -= 1;
        }
        arr[i+1] = key;
        
        step++;
        printf("%3d: %s", step, arr2str(res, arr, length));   
    }
    printf("New: %s", arr2str(res, arr, length));
}

// 2.1-3 线性查找
int search_arr(int arr[], int length, int value) {
    int i;
    for (i = 0; i < length; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// 2.1-4 二进制数组加法
void add_arr(int arr1[], int arr2[], int length, int result[]) {
    int i, sum, carry = 0;
    for (i = length - 1; i >= 0; i--) {
        sum = arr1[i] + arr2[i] + carry;
        if (sum >= 2) {
            sum = sum - 2;
            carry = 1;
        } else {
            carry = 0;
        }
        result[i + 1] = sum;
    }
    result[0] = carry;
}

// 2.2-2 选择排序
void select_sort(int arr[], int length) {
    printf("Old: %s", arr2str(res, arr, length));
    int i, j, key, step=0;
    for (i = 0; i < length - 1; i++) {
        for (j = i + 1; j < length; j++) {
            if (arr[i] > arr[j]) {
                key = arr[i];
                arr[i] = arr[j];
                arr[j] = key;
            }
        }

        step++;
        printf("%3d: %s", step, arr2str(res, arr, length));   
    }
    printf("New: %s", arr2str(res, arr, length));
}

// 2.3-1 归并排序
int step = 1;
void merge(int arr[], int length, int start, int middle, int last) {
    int i, j, k;
    int mid0 = middle - start + 1;
    int mid1 = last - middle;
    int first_arr[mid0 + 1];
    int last_arr[mid1 + 1];
    // 分解复制为两个新数组
    for (i = 0; i < mid0; i++) {
        first_arr[i] = arr[start + i];
    }
    for (j = 0; j < mid1; j++) {
        last_arr[j] = arr[middle + j + 1];
    }
    first_arr[mid0] = INT_MAX;  //哨兵
    last_arr[mid1] = INT_MAX;  //哨兵
    
    i = 0;
    j = 0;
    // 合并两个数组
    for (k = start; k <= last; k++) {
        if (first_arr[i] <= last_arr[j]) {
            arr[k] = first_arr[i];
            i++;
        } else {
            arr[k] = last_arr[j];
            j++;
        }
    } 
}

void merge_sort(int arr[], int length, int start, int last) {
    if (start < last) {        
        int middle = (start + last) / 2;
        merge_sort(arr, length, start, middle);
        merge_sort(arr, length, middle + 1, last);
        merge(arr, length, start, middle, last);
    }
}

int main(void) {     

    //*
    int arr0[6] = {5, 2, 4, 6, 1, 3};
    int arr1[6] = {31, 41, 59, 26, 41, 58};
    // 2.1-3
    printf("Index: %d\n", search_arr(arr1, 6, 26));
    // 2.1-1
    insert_sort(arr0, 6);
    insert_sort(arr1, 6);
   
   /*
    // 2.2-2
    int arr2[6] = {5, 2, 4, 6, 1, 3};
    int arr3[6] = {31, 41, 59, 26, 41, 58};
    select_sort(arr2, 6);
    select_sort(arr3, 6);

    // 2.1-4
    int binarr1[8] = {1, 1, 0, 1, 1, 1, 1, 0};
    int binarr2[8] = {1, 0, 1, 1, 1, 1, 0, 1}; 
    printf("binarr1: %s", arr2str(binarr1, 8)); 
    printf("binarr2: %s", arr2str(binarr2, 8));
    int result[9];
    add_arr(binarr1, binarr2, 8, result); 
    printf("result : %s", arr2str(result, 9));

    //
    // 2.3-1
    int arr4[] = {2, 4, 5, 7, 1, 2, 3, 6};
    int arr5[] = {3, 41, 52, 26, 38, 57, 9, 49};
    merge_sort(arr4, 8, 0, 7);    
    merge_sort(arr5, 8, 0, 7);

    */
}