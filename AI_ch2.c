// 第2章 盲目搜索
#include "tool.c"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define SIZE 8
// 初始化
int queens[SIZE][SIZE];  // 皇后布置棋盘，一维数组表示  0:无 1:有
int queens_cover[SIZE][SIZE];  // 该位置是否已被皇后辐射 0:否 >=1:是
int queens_result[SIZE]; // 存储结果，-1:未放 >=0: 皇后所在行
void init(void) {
    for (int col = 0; col < SIZE; col++) {
        for (int row = 0; row < SIZE; row++) {
            queens[row][col] = 0; //  0:无 1:有
            queens_cover[row][col] = 0; //  0:否 >=1:1个及以上皇后覆盖此位置
        }
        queens_result[col] = -1; // -1:未放 >=0: 皇后所在行
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
    queens_result[update_col] = update_value ? update_row : -1; // 更新皇后结果数组  -1:未放 >=0: 皇后所在行
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

// 生成与测试
int gen_test(void) {
    int n, row, col, inserted, backed, last_row_ok;
    n = 0;
    last_row_ok = -1; // 最近一个成功结果的第0列行值
    while (last_row_ok < SIZE) {
        init(); 
        inserted = 0; // 插入标志
        backed = 0; // 回退标志
        queens_result[0] = last_row_ok;  // 
        for (col = 0; col < SIZE; col ++) {
            inserted = 0; // 重置插入标志
            row = queens_result[col] + 1; // 应在可能取出皇后的操作之前
            if (backed && queens_result[col] >= 0) {
                update_queens(queens_result[col], col, 0); // 取出皇后
                /*
                printf("backed: (%d %d):\n%s", queens_result[col], col, queens_str(queens));
                printf("%s", queens_str(queens_cover));
                printf(" %s\n\n", arr_str(queens_result, SIZE));
                */
            }
            for ( ; row < SIZE; row++) {
                if (queens_cover[row][col] == 0) {
                    update_queens(row, col, 1); // 插入皇后
                    inserted = 1; // 插入标志
                    /*
                    printf("(%d %d):\n%s", row, col, queens_str(queens));
                    printf("%s", queens_str(queens_cover));
                    printf(" %s\n\n", arr_str(queens_result, SIZE));
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
            printf(" %s\n\n", arr_str(queens_result, SIZE));
            last_row_ok = queens_result[0];
        } else {
            break; // 结束搜索，退出
        }
    }
}

int main(void)
{
    gen_test();

}