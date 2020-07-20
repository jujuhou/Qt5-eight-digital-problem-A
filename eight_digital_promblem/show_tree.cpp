#include "show_tree.h"
#include "ui_show_tree.h"
#include <math.h>

#define Left_Distance 60//左边的预留距离
#define Up_Distance 50//上边的预留距离
#define D_matrix 20//格子之间的单位距离
#define A_matrix 42//格子的大小
#define S_matrix 10//字体大小


Show_tree::Show_tree(vector<Item> eight_digital_path,QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Show_tree)
{
    ui->setupUi(this);
    path=eight_digital_path;//将path复制进来
}

Show_tree::~Show_tree()
{
    delete ui;
}

void Show_tree::done_button_clicked()//按done即可关闭本窗口
{
    this->close();
}

void draw_one_matrix(int matrix[3][3],Qt::GlobalColor color,long long int center_x,long long int center_y, QPainter &painter, QPen &pen)
{
    //设置颜色
    pen.setColor(color);
    painter.setPen(pen);
    //画矩形
    painter.drawRect(center_x-A_matrix/2,center_y-A_matrix/2,A_matrix,A_matrix);
    //填数字
    int x_deviation=-3;
    int y_deviation=-6;//反正就有偏差，咱也不想算，试出来就这个数了

    painter.drawText(center_x-A_matrix/3+x_deviation,center_y+y_deviation,QString::number(matrix[0][0]));
    painter.drawText(center_x+x_deviation,center_y+y_deviation,QString::number(matrix[0][1]));
    painter.drawText(center_x+A_matrix/3+x_deviation,center_y+y_deviation,QString::number(matrix[0][2]));
    painter.drawText(center_x-A_matrix/3+x_deviation,center_y+A_matrix/3+y_deviation,QString::number(matrix[1][0]));
    painter.drawText(center_x+x_deviation,center_y+A_matrix/3+y_deviation,QString::number(matrix[1][1]));
    painter.drawText(center_x+A_matrix/3+x_deviation,center_y+A_matrix/3+y_deviation,QString::number(matrix[1][2]));
    painter.drawText(center_x-A_matrix/3+x_deviation,center_y+A_matrix*2/3+y_deviation,QString::number(matrix[2][0]));
    painter.drawText(center_x+x_deviation,center_y+A_matrix*2/3+y_deviation,QString::number(matrix[2][1]));
    painter.drawText(center_x+A_matrix/3+x_deviation,center_y+A_matrix*2/3+y_deviation,QString::number(matrix[2][2]));

}

//递归画图 node_num:当前在画的node在form中的标号
void Show_tree::draw_tree(vector<int> &present_draw_of_each_depth,int depth,int total_depth, vector<node> &form, QPainter& painter, QPen &pen,int node_num,long long int center_x,long long int center_y)
{
    //画出当前的格子
    present_draw_of_each_depth[depth]++;
    draw_one_matrix(path[node_num].matrix,(form[node_num].is_final_path==true)?Qt::red:Qt::black,center_x,center_y,painter,pen);

    //没有子节点则return
    if(form[node_num].children[0]==-1)
        return;

    //找到子节点的坐标
    long long int child_x,child_y;
    child_x=present_draw_of_each_depth[depth+1]*(A_matrix+D_matrix)+Left_Distance+A_matrix/2;
    child_y=(depth+1)*(A_matrix+D_matrix)+Up_Distance+A_matrix/2;

    int i;
    for(i=0;i<4&&form[node_num].children[i]!=-1;i++){
        //递归
        draw_tree(present_draw_of_each_depth,depth+1,total_depth, form, painter, pen,form[node_num].children[i],child_x+(D_matrix+A_matrix)*i,child_y);
        //画枝子
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawLine(center_x,center_y+A_matrix/2,child_x+(D_matrix+A_matrix)*i,child_y-A_matrix/2);
    }
}

void Show_tree::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    int i,j;
    int total_depth=0;
    //建立 父节点|子节点1|子节点2|子节点3|子节点4 的结点表格
    vector<node> form(path.size());
    for(i=0;i<int(path.size());i++)//为什么不在一开始赋父节点的时候就写好捏？可能因为当时觉得四个结点就很烦......结果现在更烦了
        form.at(i) = node{{-1,-1,-1,-1},false};

    for(i=int(path.size()-1);i>0;i--){
        //只要i不等于0，一定是有pre结点的
        for(j=0;j<4;j++){
            if(form[path[i].pre].children[j]==-1)//找到还未赋值的结点
                break;
        }
        form[path[i].pre].children[j]=i;
    }
    //给最短路径的is_final_path赋值为true
    for(i=int(path.size()-1);i>=0;){
        form[i].is_final_path=true;
        i=path[i].pre;
        total_depth++;
    }

    //现在表格就建好了

    //接下来创立一个表格记录每层画了几个格子了
    vector<int> present_draw_of_each_depth(total_depth);
    for(i=0;i<total_depth;i++)
        present_draw_of_each_depth.at(i)=0;

    //递归画图
    QPainter painter(this);
    QPen pen;
    draw_tree(present_draw_of_each_depth,0,total_depth, form, painter, pen,0,Left_Distance+A_matrix/2,Up_Distance+A_matrix/2);

}
