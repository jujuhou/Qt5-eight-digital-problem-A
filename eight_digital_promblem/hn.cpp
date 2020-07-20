#include "mainwindow.h"
#include "ui_mainwindow.h"


//不在位置的棋子个数
int calculate_h_n_1(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N])
{
    int h_n = 0;
    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
            if (present[i][j] != end[i][j])
                h_n++;
    return h_n;
}

//曼哈顿距离
int calculate_h_n_2(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N])
{
    int h_n = 0;

    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
        {
            if (present[i][j] == 0)
                continue;
            else if (present[i][j] != end[i][j])
            {
                for (int k = 0; k < 3; k++)
                    for (int w = 0; w < 3; w++)
                        if (present[i][j] == end[k][w])
                            h_n = h_n + fabs(i - k * 1.0) + fabs(j - w * 1.0);
            }
        }

    return h_n;
}

//欧几里得距离
int calculate_h_n_3(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N])
{
    int h_n = 0;

    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
        {
            if (present[i][j] != end[i][j])
            {
                for (int k = 0; k < 3; k++)
                    for (int w = 0; w < 3; w++)
                        if (present[i][j] == end[k][w])//平方根运算耗费时间，此方法速度较慢
                            h_n = h_n +sqrt((i - k * 1.0)*(i - k * 1.0) + (j - w * 1.0)*(j - w * 1.0));
            }
        }

    return h_n;
}

//对角线距离
int calculate_h_n_4(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N])
{
    double h_n = 0;

    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
        {
            if (present[i][j] != end[i][j])
            {
                for (int k = 0; k < 3; k++)
                    for (int w = 0; w < 3; w++)
                        if (present[i][j] == end[k][w])
                        {
                            int h_diagonal = (fabs(i - k) > fabs(j - w)) ? fabs(j - w) : fabs(i - k);
                            int h_straight = fabs(i - k * 1.0) + fabs(j - w * 1.0);
                            h_n = h_n + sqrt(2)*h_diagonal+(h_straight-2*h_diagonal);
                        }
            }
        }

    return (int)(h_n);
}
