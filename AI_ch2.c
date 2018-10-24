// 第2章 盲目搜索
#include "tool.c"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define SIZE 8

// 初始化
int queens[SIZE][SIZE];  // 皇后布置棋盘，一维数组表示  0:无 1:有
int queens_cover[SIZE][SIZE];  // 该位置是否已被皇后辐射 0:否 >=1:是
int col_result[SIZE]; // 存储结果，-1:未放 >=0: 皇后所在行
void init(void) {
    for (int col = 0; col < SIZE; col++) {
        for (int row = 0; row < SIZE; row++) {
            queens[row][col] = 0; //  0:无 1:有
            queens_cover[row][col] = 0; //  0:否 >=1:1个及以上皇后覆盖此位置
        }
        col_result[col] = -1; // -1:未放 >=0: 皇后所在行
    }
}

//字符串输出
char * queens_str(int queens[SIZE][SIZE])
{
    int row, col, len = 2;
    sprintf(str, "  ");
    for (col = 0; col < SIZE; col++) {
        sprintf(str + len, " %d ", col + 1);
        len += 3;
    }
    
    for (row = SIZE - 1; row >= 0; row--) {
        sprintf(str + len, "\n %d", row + 1);
        len += 3;
        for (int col = 0; col < SIZE; col++) {
            sprintf(str + len, " %s ", queens[row][col] ? "Q" : " ");
            //sprintf(str + len, " %d ", queens[row][col]);
            len += 3;
        }
    }
    sprintf(str + len, "\n");
    return str;
}

// 根据皇后位置，更新辐射位置
void update_queens(int update_row, int update_col, int update_value)
{
    int row, col, cover_count;
    queens[update_row][update_col] = update_value; // 皇后布置棋盘 1:插入皇后 0:取出皇后
    col_result[update_col] = update_value ? update_row : -1; // 更新皇后结果数组  -1:未放 >=0: 皇后所在行
    // 更新皇后覆盖位置
    cover_count = update_value ? 1 : -1; // 增减皇后覆盖的数量
    // 所在列
    for (row = 0; row < SIZE; row++) {
        queens_cover[row][update_col] += cover_count;
    }
    // 所在行
    for (col = 0; col < SIZE; col++) {
        queens_cover[update_row][col] += cover_count;
    }
    // 所在左下斜
    for (row = update_row - 1, col = update_col - 1; row >= 0 && col >= 0; row--, col--) {
        queens_cover[row][col] += cover_count;
    }
    // 所在右上斜
    for (row = update_row + 1, col = update_col + 1; row < SIZE && col < SIZE; row++, col++) {
        queens_cover[row][col] += cover_count;
    }
    // 所在右下斜
    for (row = update_row - 1, col = update_col + 1; row >= 0 && col < SIZE; row--, col++) {
        queens_cover[row][col] += cover_count;
    }
    // 所在左上斜
    for (row = update_row + 1, col = update_col - 1; row < SIZE && col >= 0; row++, col--) {
        queens_cover[row][col] += cover_count;
    }
}

// 生成与测试 （只生成了8个解）
int gen_test(void) {
    int n, row, col, inserted, backed, last_row_ok;
    n = 0;
    last_row_ok = -1; // 最近一个成功结果的第0列行值
    while (last_row_ok < SIZE) {
        init(); 
        inserted = 0; // 插入标志
        backed = 0; // 回退标志
        col_result[0] = last_row_ok;  // 
        for (col = 0; col < SIZE; col ++) {
            inserted = 0; // 重置插入标志
            row = col_result[col] + 1; // 应在可能取出皇后的操作之前
            if (backed && col_result[col] >= 0) {
                update_queens(col_result[col], col, 0); // 取出皇后
                /*
                printf("backed: (%d %d):\n%s", col_result[col], col, queens_str(queens));
                printf("%s", queens_str(queens_cover));
                printf(" %s\n\n", arr_str(col_result, SIZE));
                */
            }
            for ( ; row < SIZE; row++) {
                if (queens_cover[row][col] == 0) {
                    update_queens(row, col, 1); // 插入皇后
                    inserted = 1; // 插入标志
                    /*
                    printf("(%d %d):\n%s", row, col, queens_str(queens));
                    printf("%s", queens_str(queens_cover));
                    printf(" %s\n\n", arr_str(col_result, SIZE));
                    */
                    break;
                }
            }
            if (inserted == 0) { // 本列插入不成功
                if (col == 0) { // 不可回退
                    break;
                }
                col -= 2; // 回退一列, 与for循环的col++抵消一个1
                backed = 1; // 回退标志     
            } else {
                backed = 0; // 重置回退标志
            }
        }
        if (col == SIZE && inserted == 1) { // 最后一列且是插入状态，则皇后数量已满，达到目标
            n++;
            printf("No.%d:\n%s", n, queens_str(queens));
            printf(" %s\n\n", arr_str(col_result, SIZE));
            last_row_ok = col_result[0];
        } else {
            break; // 结束搜索，退出
        }
    }
}

/*
// 网上复制得来，可能是c++
#include <iostream>
#include <math.h>
using namespace std;

int n = 8;
int total = 0;
int* c = new int(n); // 当前列数组

bool is_ok(int row) // 检查row行col列能不能摆皇后
{
    for (int j = 0; j != row; j++) {
        if (c[row] == c[j] || row - c[row] == j - c[j] || row + c[row] == j + c[j])
            return false;
    }
    return true;
}

void queen(int row)
{
    if (row == n)
        total++;
    else
        for (int col = 0; col != n; col++) {
            c[row] = col;
            if (is_ok(row))
                queen(row + 1);
        }
}

int main()
{
    queen(0);
    cout << total;
    return 1;
}
*/

// 参考以上网摘写的递归回溯算法
int count = 0;
int col[SIZE]; // 皇后所在列

// 判断是否可放入
int is_ok(int row) {
    for (int c = 0; c != row; c++) {
        if (col[row] == col[c] || row - col[row] == c - col[c] || row + col[row] == c + col[c]) {
            // 参数row 待插入行值，始终大于所有已插入行值 —— 满足不能属于同一行
            // col[row] == col[c] 待插入行的列值 是否等于 已插入所有行的列值？—— 满足不能属于同一列
            // row - col[row] == col - col[c] 待插入行列之差 是否等于 已插入所有的行列之差？—— 满足不能属于同一左斜对角线
            // row + col[row] == col + col[c] 待插入行列之和 是否等于 已插入所有的行列之和？—— 满足不能属于同一右斜对角线
            return 0; // 该row行的col[row]列不能放入皇后
        }
    }
    return 1; // 可以放入
}

// 在row行的col列插入皇后
void insert_queen(int row) {
    if (row == SIZE) {
        count++;
        printf("No.%d: %s\n", count, arr_str(col, SIZE));
    } else {
        for (int c = 0; c != SIZE; c++) {
            col[row] = c;
            if (is_ok(row)) {  // 如不可则进下一col列
                insert_queen(row + 1); // 递归调用下一行
            }
        }        
    }
}


int main(void)
{
    // gen_test(); // 自己写的，笨重且功能不完整

    insert_queen(0); // 参考网上的驱动递归函数，从0行起
    printf("total: %d", count);

}