#pragma once

#ifndef HEAD_H
#define HEAD_H
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
//STL容器头文件的包含
#include <queue>
#include <vector>
#include <map>
//时间记录的头文件
#include <time.h>
using namespace std;
#endif // HEAD_H

//宏定义
#define MATRIX_N 3  //3*3的格子

/**************************************************************
Item是每个状态节点信息记录的结构体
    matrix是每个状态的数字分布矩阵，其中有1-8，0代表空格子
    pre是父节点在path中的下标(path的说明在下面)
    f_n,g_n,h_n即f(n),g(n),h(n)		f(n)=g(n)+h(n),g(n)=n,h(n)有两种选取方法
**************************************************************/

struct Item
{
    int matrix[MATRIX_N][MATRIX_N];
    int pre;
    int f_n, g_n, h_n;
    //Item的定义见上
    Item(int matrix[MATRIX_N][MATRIX_N], int pre, int g_n, int h_n);//带参的构造函数
    bool operator <(const Item temp) const;//通过f_n比较大小，应用于优先队列的排序
    bool operator ==(const Item temp) const;//比较两个数组是否一样（每个元素）

};
