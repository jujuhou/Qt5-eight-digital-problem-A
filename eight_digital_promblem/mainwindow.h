#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QTextList>
#include <QTextBrowser>
#include <QLabel>
#include <QElapsedTimer>
#include <QTime>
#include <ctime>
#include <iostream>
#include "head.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //初始化matrix_start以及matrix_end
    bool init_start_and_end();
    //找到路径并打印
    void find_path();

    int PrintPath(const Item p);

    //path用于保存路径
    vector<Item> path;//设为public因为需要在show_tree中使用

private slots:
    void Go_clicked();
    void About_clicked();
    void Usage_clicked();
    void Show_tree_clicked();

private:
    //Open表：存储已扩展出但是还没有访问的节点，使用优先队列进行排序
    priority_queue<Item> Open;
    //Close表：存储已经访问过的节点，避免重复访问
    map<int, bool> Close;
    //初始和目标状态
    int matrix_start[MATRIX_N][MATRIX_N], matrix_end[MATRIX_N][MATRIX_N];
    //结果输出界面的字符串
    QString result;
    //hn的指针
    int (*calculate_h_n)(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N]);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

int calculate_h_n_1(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N]);
int calculate_h_n_2(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N]);
int calculate_h_n_3(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N]);
int calculate_h_n_4(const int present[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N]);

//hn实现的声明

