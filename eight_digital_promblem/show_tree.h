#pragma once
#ifndef SHOW_TREE_H
#define SHOW_TREE_H

#include <QWidget>
#include <QMainWindow>
#include <QPainter>//绘制图案头文件
#include <QPen>
#include "head.h"


struct node//父节点|子节点1|子节点2|子节点3|子节点4 的表格中的一行（还包含是否为最终路径）
{
    int children[4];
    bool is_final_path;
};


namespace Ui {
class Show_tree;
}

class Show_tree : public QMainWindow
{
    Q_OBJECT

public:
    explicit Show_tree(vector<Item> eight_digital_path,QMainWindow *parent = nullptr);
    ~Show_tree();

protected:
    void paintEvent(QPaintEvent *event);
    void draw_tree(vector<int> &present_draw_of_each_depth,int depth,int total_depth, vector<node> &form,QPainter &painter, QPen &pen,int node_num,long long int center_x,long long int center_y);

private slots:
    void done_button_clicked();


private:
    Ui::Show_tree *ui;
    vector<Item> path;

};


#endif // SHOW_TREE_H
