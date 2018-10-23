// 第2章 盲目搜索
#include "tool.c"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define SIZE 4
#define LENGTH (SIZE * SIZE)
int queens[LENGTH];  // 皇后布置棋盘，一维数组表示
int queens_cover[LENGTH];  // 该位置是否已被皇后辐射 1:是 0:否
int result[SIZE]; // 存储结果，皇后在第i列的第result[i]行, -1则未放
// 初始化
void queens_init(void) {
    for (int i = 0; i < LENGTH; i++) {
        queens[i] = 0;
    }
}
void queens_cover_init(void) {
    for (int i = 0; i < LENGTH; i++) {
        queens_cover[i] = 0;
    }
}
void result_init(void) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = -1; // 无皇后
    }
}

//字符串输出
char * queens_str(int queens[])
{
    int row, col, len = 2;
    sprintf(str, "  ");
    for (col = 0; col < SIZE; col++) {
        sprintf(str + len, " %d ", col + 1);
        len += 3;
    }

    for (row = SIZE; row > 0; row--) {
        sprintf(str + len, "\n %d", row);
        len += 3;
        for (col = 0; col < SIZE; col++) {
            sprintf(str + len, " %s ", queens[(row - 1) * SIZE + col] ? "Q" : " ");
            len += 3;
        }
    }
    sprintf(str + len, "\n");
    return str;
}

// 根据皇后位置，更新辐射位置
void update_cover(void)
{
    int row, col, q_row, q_col;
    for (int i = 0; i < LENGTH; i++) {
        if (!queens[i]) {
            continue;
        }
        q_row = i / SIZE;
        q_col = i % SIZE;
        // 所在列
        for (row = 0; row < SIZE; row++) {
            queens_cover[row * SIZE + q_col] = 1;
        }
        // 所在行
        for (col = 0; col < SIZE; col++) {
            queens_cover[q_row * SIZE + col] = 1;
        }
        // 所在左下斜
        for (row = row - 1, col = col - 1; row >= 0 && col >= 0; row--, col--) {
            queens_cover[row * SIZE + col] = 1;
        }
        // 所在右上斜
        for (row = row + 1, col = col + 1; row < SIZE && col < SIZE; row++, col++) {
            queens_cover[row * SIZE + col] = 1;
        }
        // 所在右下斜
        for (row = row - 1, col = col + 1; row >= 0 && col < SIZE; row--, col++) {
            queens_cover[row * SIZE + col] = 1;
        }
        // 所在左上斜
        for (row = row + 1, col = col - 1; row < SIZE && col >= 0; row++, col--) {
            queens_cover[row * SIZE + col] = 1;
        }
    }
}

// 生成与测试
int gen_test(void) { 
    int n, row, col, ins_row, ins_col; // 最近的插入位置
    queens_init();
    queens_cover_init();
    result_init();
    col = 0; 
    while (col < SIZE && col >= 0) {
        row = result[col] + 1; 
        while (row < SIZE) {
            if (queens_cover[row * SIZE + col] == 0) {
                queens[row * SIZE + col] = 1; // 插入皇后
                result[col] = row;
                update_cover(); // 更新覆盖范围
                printf("(%d %d):\n%s", row, col, queens_str(queens));
                printf("%s\n", queens_str(queens_cover));
                break;
            }
            row++;
        }
        if (result[col] < 0) { // 本列插入不成功
            col--; // 回退一列
            result[col] = -1; // 清除该列皇后
        } else { // 本列插入成功
            col++;
        }
    }
    if (col == SIZE && ins_row >= 0) { // 最后一列且是插入状态，则皇后数量已满，达到目标
        printf("finished:\n%s", queens_str(queens));
    }
}

int main(void)
{
    /*
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            gen_queen_rc(queens_cover, SIZE, row, col);
            printf("(%d, %d)cover:\n%s\n", row + 1, col + 1, queens_str(queens_cover, SIZE));
            queens_cover_init();
        }
    }
    */
    gen_test();

}