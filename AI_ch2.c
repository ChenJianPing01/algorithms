// 第2章 盲目搜索
#include "tool.c"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define size 4
int queens[size * size];  // 皇后布置棋盘，一维数组表示
int queens_cover[size * size];  // 该位置是否已被皇后辐射 1:是 0:否
// 初始化
void queens_init(void) {
    for (int i = 0; i < size * size; i++) {
        queens[i] = 0;
    }
}
void queens_cover_init(void) {
    for (int i = 0; i < size * size; i++) {
        queens_cover[i] = 0;
    }
}

//字符串输出
char * queens_str()
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
void update_cover(int row, int col)
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

// 生成中间状态。在某列放入皇后，放入前判断是否被辐射
int insert_queen(int col) {
    for (int r = 0; r < size; r++) {
        if (queens_cover[r * size + col] == 0) {
            queens[r * size + col] = 1;
            return 1;
        }
    }
    return 0;
}

// 判断皇后是否达到数量
int isok() {
    int count = 0;
    for (int i = 0; i < size * size; i++) {
        count += queens[i];
    }
    return count == size ? 1 : 0;
}

// 生成与测试
int genner(int queens[], int size) { 
    int row = 0, col = 0;   
    queens_init();
    queens_cover_init();    
    while (!isok() && col < size) {
        while (row < size) {
            if (insert_queen(col)) {  // 插入皇后
                update_cover(row, col); // 更新覆盖范围                
            } else {
                break;
            }
        }
        col++;
    }
    if (isok()) {
        return 1;
    }
}

int main(void)
{
    queens_init();
    queens_cover_init();
    printf("queens:\n%s", queens_str(queens, size));
    printf("cover:\n%s\n\n", queens_str(queens_cover, size));

    /*
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            gen_queen_rc(queens_cover, size, r, c);
            printf("(%d, %d)cover:\n%s\n", r + 1, c + 1, queens_str(queens_cover, size));
            queens_cover_init();
        }
    }
    */

}