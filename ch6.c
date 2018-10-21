// 第6章 堆排序
#include "tool.c"
#include <limits.h>
#include <stdio.h>
#include <string.h>

// 父节点
int parent(int i)
{
    return (i - 1) / 2;
}

// 左孩子
int left(int i)
{
    return 2 * i + 1;
}

// 右孩子
int right(int i)
{
    return 2 * i + 2;
}

// 最大堆维护子函数
void max_heapify(int arr[], int heapsize, int i)
{
    int l = left(i);
    int r = right(i);
    int largest, temp;  // 序号性质
    if (l < heapsize && arr[l] > arr[i]) {
        largest = l;
    } else {
        largest = i;
    }
    if (r < heapsize && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        max_heapify(arr, heapsize, largest);
    }
}

// 建堆
void build_max_heap(int arr[], int length) {
    int heapsize = length;
    for (int i = length / 2 - 1; i >= 0; i--) {
        max_heapify(arr, heapsize, i);
    }
}

// 堆排序
void heap_sort(int arr[], int length)
{
    int temp;
    int heapsize = length;
    build_max_heap(arr, length);

    printf("ini: %s\n", arr_str(arr, length));
    for (int i = length - 1; i >= 1; i--) {
        temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        heapsize--;
        max_heapify(arr, heapsize, 0);

        printf("   : %s\n", arr_str(arr, length));
    }
}

int main(void)
{
    int length = 10;
    int arr[length];
    char str[STRSIZE];

    rand_arr(arr, length, 100);
    printf("Old: %s\n", arr_str(arr, length));
    // 6.4-1
    heap_sort(arr, length);
    printf("New: %s\n\n", arr_str(arr, length));


}