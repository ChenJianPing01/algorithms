// 第2章 算法基础
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "tool.c"

char str[STRSIZE];

// 2.1-1 插入排序
// 2.1-2 只需更改while循环条件的比较符合即可）
void insert_sort(int arr[], int length) {
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
        //printf("%3d: %s\n", step, arr_str(str, arr, length));
    }
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
void add_arr(int result[], int arr1[], int arr2[], int length) {
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
        //printf("%3d: %s\n", step, arr_str(str, arr, length));
    }
}

// 2.3-1 归并排序
int step = 1;
// 使用哨兵的合并子函数
void merge(int arr[], int length, int start, int middle, int last) {
    int i, j, k;
    int mid0 = middle - start + 1;
    int mid1 = last - middle;
    int first_arr[mid0 + 2];
    int last_arr[mid1 + 2];
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
    
    printf("   : %s\n", arr_str(str, arr, length));
}
// 不使用哨兵的合并子函数
void merge1(int arr[], int length, int start, int middle, int last) {
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
    
    i = 0;
    j = 0;
    // 合并两个数组
    for (k = start; k <= last; k++) {
        if (i == mid0) {
            while (j < mid1) {
                arr[k++] = last_arr[j++];
            }
            break;
        } else if (j == mid1) {
            while (i < mid0) {
                arr[k++] = first_arr[i++];
            }
            break;
        } else if (first_arr[i] <= last_arr[j]) {
            arr[k] = first_arr[i++];
        } else {
            arr[k] = last_arr[j++];
        }
    } 
    
    printf("   : %s\n", arr_str(str, arr, length));
}

void merge_sort(int arr[], int length, int start, int last) {
    if (start < last) {        
        int middle = (start + last) / 2;
        merge_sort(arr, length, start, middle);
        merge_sort(arr, length, middle + 1, last);
        merge(arr, length, start, middle, last);  // 可选是否使用哨兵
    }
}

// 逆序对
void inversion(int arr[], int length) {
    int i, j, count = 0, t = 0;
    for (i = 0; i < length - 1; i++) {
        for (j = i + 1; j < length; j++) {
            if (arr[i] > arr[j]) {
                printf("No.%3d : (%2d, %2d)[%2d, %2d]\n", count++, i, j, arr[i], arr[j]);
            }
        }
        t += (length - i - 1);        
    }
    printf("Total: %3d\n", t);
}

int main(void) {     
    int arrlen = 10;
    int arr[arrlen];

    rand_arr(arr, arrlen, 100);
    printf("Old: %s\n", arr_str(str, arr, arrlen));
    // 2.1-3
    printf("Index of %d: %d\n", 26, search_arr(arr, arrlen, 26));
    // 2.1-1
    insert_sort(arr, arrlen);
    printf("New: %s\n\n", arr_str(str, arr, arrlen));
    
    // 2.1-4
    int binarr1[8], binarr2[8]; 
    rand_arr(binarr1, 8, 2);
    rand_arr(binarr2, 8, 2);
    printf("binarr1:    %s\n", arr_str(str, binarr1, 8)); 
    printf("binarr2:    %s\n", arr_str(str, binarr2, 8));
    int result[9];
    add_arr(result, binarr1, binarr2, 8); 
    printf("result :%s\n\n", arr_str(str, result, 9));

    // 2.2-2
    rand_arr(arr, arrlen, 100);
    printf("Old: %s\n", arr_str(str, arr, arrlen));
    select_sort(arr, arrlen);
    printf("New: %s\n\n", arr_str(str, arr, arrlen));

    // 2.3-1, 2.3-2
    rand_arr(arr, arrlen, 100);
    printf("Old: %s\n", arr_str(str, arr, arrlen));
    merge_sort(arr, arrlen, 0, arrlen - 1); 
    printf("New: %s\n\n", arr_str(str, arr, arrlen));

    // 2-4 
    //rand_arr(arr, arrlen, 100);
    for (int i = 0; i < arrlen; i++) { arr[i] = arrlen - i; }
    printf("Old: %s\n", arr_str(str, arr, arrlen));
    inversion(arr, arrlen); 
    printf("New: %s\n\n", arr_str(str, arr, arrlen));

}