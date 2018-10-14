// 第2章 算法基础
#include <stdio.h>

void printf_arr(int arr[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
}

void insert_sort(int arr[], int length) {
    printf("Old: ");
    printf_arr(arr, length);
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
        printf("\n%3d: ", step);
        printf_arr(arr, length);        
    }
    //printf("\nNew: ");
    //printf_arr(arr, length);
}

int search_arr(int arr[], int length, int value) {
    int i;
    for (i = 0; i < length; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

int main(void) {
    int input0[6] = {5, 2, 4, 6, 1, 3};
    int input1[6] = {31, 41, 59, 26, 41, 58};

    printf("Index: %d\n", search_arr(input1, 6, 26));
    insert_sort(input1, 6);
    
}