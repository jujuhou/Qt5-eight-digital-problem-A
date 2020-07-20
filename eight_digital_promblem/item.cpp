#include "head.h"
Item::Item(int matrix[MATRIX_N][MATRIX_N], int pre, int g_n, int h_n)
{
    //将信息全部复制
    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
            this->matrix[i][j] = matrix[i][j];
    this->pre = pre;
    this->g_n = g_n;
    this->h_n = h_n;
    this->f_n = g_n + h_n;
}

bool Item::operator <(const Item temp) const//比较两个item的fn的大小
{
    return f_n > temp.f_n;
}

bool Item::operator ==(const Item temp) const//判断两个结点是否相等
{
    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
            if (matrix[i][j] != temp.matrix[i][j])
                return false;
    return true;
}
