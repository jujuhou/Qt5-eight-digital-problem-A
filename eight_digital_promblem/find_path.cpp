#include "mainwindow.h"
#include "ui_mainwindow.h"


//***********具体实现******************

//两者逆序数奇偶性相等,看八数码是否有解
bool solution_exist(const int start[MATRIX_N][MATRIX_N], const int end[MATRIX_N][MATRIX_N])
{
    int s_num = 0, e_num = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < i; j++) {
            if (start[j / MATRIX_N][j % MATRIX_N] != 0 && start[j / MATRIX_N][j % MATRIX_N] < start[i / MATRIX_N][i % MATRIX_N])
                s_num++;
            if (end[j / MATRIX_N][j % MATRIX_N] != 0 && end[j / MATRIX_N][j % MATRIX_N] < end[i / MATRIX_N][i % MATRIX_N])
                e_num++;
        }
    return (s_num & 1) == (e_num & 1);
}
//得到当前表的hash值
int hash_index(const int a[][MATRIX_N])
{
    int t = 0;
    for (int i = 0; i < MATRIX_N; i++)
        for (int j = 0; j < MATRIX_N; j++)
            t = t * 10 + a[i][j];//每格占一位，处在int的范围内，且保证每个状态的hash值不同
    return t;
}
//递归打印路径
int MainWindow::PrintPath(const Item p)
{
    if (p.pre == -1){
        //连接结果字符串
        for (int i = 0; i < MATRIX_N; i++){
            for (int j = 0; j < MATRIX_N; j++)
                result+=" "+QString::number(p.matrix[i][j])+" ";
            result+="\n";
        }
        result+="\n";
        //在动态界面进行显示
        ui->process_0_0->setText(QString::number(p.matrix[0][0]));
        ui->process_0_1->setText(QString::number(p.matrix[0][1]));
        ui->process_0_2->setText(QString::number(p.matrix[0][2]));
        ui->process_1_0->setText(QString::number(p.matrix[1][0]));
        ui->process_1_1->setText(QString::number(p.matrix[1][1]));
        ui->process_1_2->setText(QString::number(p.matrix[1][2]));
        ui->process_2_0->setText(QString::number(p.matrix[2][0]));
        ui->process_2_1->setText(QString::number(p.matrix[2][1]));
        ui->process_2_2->setText(QString::number(p.matrix[2][2]));

        return 0;
    }
    PrintPath(path[p.pre]);

    //连接结果字符串
    result+="step->"+QString::number(p.g_n)+"\n";
    for (int i = 0; i < MATRIX_N; i++){
        for (int j = 0; j < MATRIX_N; j++)
            result+=" "+QString::number(p.matrix[i][j])+" ";
        result+="\n";
    }
    result+="\n";
    //在动态界面进行显示
    ui->process_0_0->setText(QString::number(p.matrix[0][0]));
    ui->process_0_1->setText(QString::number(p.matrix[0][1]));
    ui->process_0_2->setText(QString::number(p.matrix[0][2]));
    ui->process_1_0->setText(QString::number(p.matrix[1][0]));
    ui->process_1_1->setText(QString::number(p.matrix[1][1]));
    ui->process_1_2->setText(QString::number(p.matrix[1][2]));
    ui->process_2_0->setText(QString::number(p.matrix[2][0]));
    ui->process_2_1->setText(QString::number(p.matrix[2][1]));
    ui->process_2_2->setText(QString::number(p.matrix[2][2]));
    //要停一下
    QTime t;
    t.start();
    while(t.elapsed() < 1000) {
    QCoreApplication::processEvents();
    }

    return 0;
}

/***********************************************
1.先将最开始的结点放入Open表
2.将Open表中最小的结点取出放入path中，若已经为目标结点，则找到路径。否则将其放入Close表，并生成扩展集
3.对于每个扩展出的结点，如果不在Close中，就将其放入Open表
4.回到2
***********************************************/
void MainWindow::find_path()
{
    if (!solution_exist(matrix_start, matrix_end)){        //判断是否有解
        QMessageBox::information(NULL, "Waring", "Do not have a path", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }

    //开始计时
    clock_t start_time=clock();

    //程序运行开始
    //首先初始化start和end Item（在已有其矩阵的基础上）
    Item start(matrix_start, -1, 0, calculate_h_n_1(matrix_start, matrix_end));
    Item end(matrix_end, -1, -1, -1);//仅仅作为一个比较用的
    Open.push(start);//将最开始的结点放入Open表
    while (1) {//结束前一直循环
        Item prensent_node = Open.top();
        Open.pop();//提取出最小的结点
        while (!Open.empty() && prensent_node == Open.top())//避免Open表中出现重复元素
            Open.pop();
        path.push_back(prensent_node);//将最小的结点放入path中
        Close[hash_index(prensent_node.matrix)] = 1; //并将这个结点的hash值放入Close表
        int len = path.end() - path.begin() - 1;//得到当前结点在path中的位置，作为其扩展出的结点的pre值
        if (prensent_node == end) {//找到了end
            //计算总时间
            clock_t time=clock()-start_time;
            ui->output_time_label->setText(QString::number(time)+"ms");
            ui->step_number_label->setText(QString::number(prensent_node.g_n));//显示步数
            PrintPath(prensent_node);//依次打印结点
            return;
        }
        int x, y, next_x, next_y;
        int i, j;
        for (i = 0; i < MATRIX_N; i++)        //找到空白位置
            for (j = 0; j < MATRIX_N; j++)
                if (prensent_node.matrix[i][j] == 0)
                    x = i, y = j;

        int dx[] = { 0,0,-1,1 }, dy[] = { 1,-1,0,0 };    //四个方向扩展


        for (i = 0; i < 4; i++) {        //向四个方向扩展
            next_x = x + dx[i], next_y = y + dy[i];
            if (next_x > 2 || next_x < 0 || next_y < 0 || next_y>2)    //判断是否跑出MATRIX_N*MATRIX_N的数组
                continue;
            swap(prensent_node.matrix[next_x][next_y], prensent_node.matrix[x][y]);    //将空白点与周围点交换位置
            Item temp(prensent_node.matrix, len, prensent_node.g_n + 1, calculate_h_n_1(prensent_node.matrix, matrix_end));    //构造出新的状态节点
            swap(prensent_node.matrix[next_x][next_y], prensent_node.matrix[x][y]);    //再交换回来
            int index = hash_index(temp.matrix);        //获取hash值
            if (!Close.count(index))//不在Close表中则放入Open表
            {
                Open.push(temp);
            }
        }
    }
    return;
}

