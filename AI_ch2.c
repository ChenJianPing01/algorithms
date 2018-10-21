// 第2章 盲目搜索
#include "tool.c"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define QUEENSIZE 4

int queens[QUEENSIZE * QUEENSIZE];  // 皇后布置棋盘，一维数组表示
int queens_cover[QUEENSIZE * QUEENSIZE];  // 该位置是否已被皇后辐射 1:是 0:否
// 初始化
void queens_init(void) {
    for (int i = 0; i < QUEENSIZE * QUEENSIZE; i++) {
        queens[i] = 0;
    }
}
void queens_cover_init(void) {
    for (int i = 0; i < QUEENSIZE * QUEENSIZE; i++) {
        queens_cover[i] = 0;
    }
}

//字符串输出
char * queens_str(int queens[], int size)
{
    int i, r, c, len = 2;
    sprintf(str, "  ");
    for (c = 0; c < size; c++) {
        sprintf(str + len, " %d ", c + 1);
        len += 3;
    }

    for (r = size; r > 0; r--) {
        sprintf(str + len, "\n %d", r);
        len += 3;
        for (c = 0; c < size; c++) {
            sprintf(str + len, " %s ", queens[(r - 1) * size + c] ? "Q" : " ");
            len += 3;
        }
    }
    sprintf(str + len, "\n");
    return str;
}

// 根据皇后放入的位置，更新辐射位置数组
void gen_queen_rc(int queens_cover[], int size, int row, int col)
{
    int r, c;
    // 所在列
    for (r = 0; r < size; r++) {
        queens_cover[r * size + col] = 1;
    }
    // 所在行
    for (c = 0; c < size; c++) {
        queens_cover[row * size + c] = 1;
    }
    // 所在左下斜
    for (r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--) {
        queens_cover[r * size + c] = 1;
    }
    // 所在右上斜
    for (r = row + 1, c = col + 1; r < size && c < size; r++, c++) {
        queens_cover[r * size + c] = 1;
    }
    // 所在右下斜
    for (r = row - 1, c = col + 1; r >= 0 && c < size; r--, c++) {
        queens_cover[r * size + c] = 1;
    }
    // 所在左上斜
    for (r = row + 1, c = col - 1; r < size && c >= 0; r++, c--) {
        queens_cover[r * size + c] = 1;
    }
}

int main(void)
{
    queens_init();
    queens_cover_init();
    printf("queens:\n%s", queens_str(queens, QUEENSIZE));
    printf("cover:\n%s\n\n", queens_str(queens_cover, QUEENSIZE));

    /*
    for (int r = 0; r < QUEENSIZE; r++) {
        for (int c = 0; c < QUEENSIZE; c++) {
            gen_queen_rc(queens_cover, QUEENSIZE, r, c);
            printf("(%d, %d)cover:\n%s\n", r + 1, c + 1, queens_str(queens_cover, QUEENSIZE));
            queens_cover_init();
        }
    }
    */

}