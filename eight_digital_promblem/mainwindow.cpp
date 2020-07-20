#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "show_tree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Detail->hide();//隐藏细节（步骤、时间、步数）

    connect(ui->action_About_us,&QAction::triggered,this,&MainWindow::About_clicked);
    connect(ui->action_Usage,&QAction::triggered,this,&MainWindow::Usage_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化start和end数组，并检测使用哪种hn
bool MainWindow::init_start_and_end()
{
    //清空所有变量
    while(!Open.empty())
        Open.pop();
    Close.clear();
    path.clear();
    result="\n";

    //start框的输入
    matrix_start[0][0]=ui->Start_0_0->text().toInt();
    matrix_start[0][1]=ui->Start_0_1->text().toInt();
    matrix_start[0][2]=ui->Start_0_2->text().toInt();
    matrix_start[1][0]=ui->Start_1_0->text().toInt();
    matrix_start[1][1]=ui->Start_1_1->text().toInt();
    matrix_start[1][2]=ui->Start_1_2->text().toInt();
    matrix_start[2][0]=ui->Start_2_0->text().toInt();
    matrix_start[2][1]=ui->Start_2_1->text().toInt();
    matrix_start[2][2]=ui->Start_2_2->text().toInt();

    //判断输入是否正确
    int i = 0, j = 0, signal[9]={0};
    bool judge=true;//输入是否正确

    for (i = 0; i < MATRIX_N; i++) {
        for (j = 0; j < MATRIX_N; j++) {
            signal[matrix_start[i][j]] = 1;
        }
    }
    for (i = 0; i < MATRIX_N*MATRIX_N; i++) {
        if (!signal[i]) {
            judge = false;
        }
    }
    if (!judge) {
        QMessageBox::information(NULL, "Waring", "The Initial State Is Wrong", QMessageBox::Yes, QMessageBox::Yes);
        return false;
    }
    //end框的输入
    matrix_end[0][0]=ui->End_0_0->text().toInt();
    matrix_end[0][1]=ui->End_0_1->text().toInt();
    matrix_end[0][2]=ui->End_0_2->text().toInt();
    matrix_end[1][0]=ui->End_1_0->text().toInt();
    matrix_end[1][1]=ui->End_1_1->text().toInt();
    matrix_end[1][2]=ui->End_1_2->text().toInt();
    matrix_end[2][0]=ui->End_2_0->text().toInt();
    matrix_end[2][1]=ui->End_2_1->text().toInt();
    matrix_end[2][2]=ui->End_2_2->text().toInt();

    //判断输入是否正确
    for (i = 0; i < MATRIX_N; i++) {
        for (j = 0; j < MATRIX_N; j++) {
            signal[matrix_end[i][j]] = 1;
        }
    }
    for (i = 0; i < MATRIX_N*MATRIX_N; i++) {
        if (!signal[i]) {
            judge = false;
        }
    }
    if (!judge) {
        QMessageBox::information(NULL, "Waring", "The Terminate State Is Wrong", QMessageBox::Yes, QMessageBox::Yes);
        return false;
    }

    //给hn函数指针赋值
    if(ui->checkBox->isChecked()==true&&ui->checkBox_2->isChecked()==false&&ui->checkBox_3->isChecked()==false&&ui->checkBox_4->isChecked()==false)
        calculate_h_n=calculate_h_n_1;
    else if(ui->checkBox->isChecked()==false&&ui->checkBox_2->isChecked()==true&&ui->checkBox_3->isChecked()==false&&ui->checkBox_4->isChecked()==false)
        calculate_h_n=calculate_h_n_2;
    else if(ui->checkBox->isChecked()==false&&ui->checkBox_2->isChecked()==false&&ui->checkBox_3->isChecked()==true&&ui->checkBox_4->isChecked()==false)
        calculate_h_n=calculate_h_n_3;
    else if(ui->checkBox->isChecked()==false&&ui->checkBox_2->isChecked()==false&&ui->checkBox_3->isChecked()==false&&ui->checkBox_4->isChecked()==true)
        calculate_h_n=calculate_h_n_4;
    else{
        QMessageBox::information(NULL, "Waring", "Please tell us which h(n) you would like to use", QMessageBox::Yes, QMessageBox::Yes);
        return false;
    }

    return true;
}

//槽
void MainWindow::Go_clicked()
{
    ui->go_button->setEnabled(false);//每次开始时将go按钮禁用
    if(init_start_and_end()==false){
        ui->go_button->setEnabled(true);//将go按钮开启
        return;
    }
    find_path();

    ui->textBrowser->setText(result);
    ui->go_button->setEnabled(true);//每次结束时时将go按钮开启
}

void MainWindow::About_clicked()//关于
{
    QMessageBox message(QMessageBox::NoIcon, "About_us", " Tongji University \n Writer:Ju Xuan \n Contributors: Zheng Xinyao,Xu Siqi \n Email:13273105100@163.com");
    message.exec();
}
void MainWindow::Usage_clicked()//使用方法
{
    QMessageBox message(QMessageBox::NoIcon, "Usage", " Start&End:input 1-8 as moveable number,0 as vacancy\n Go:start moving \n Ditail:check process,time,step number");
    message.exec();

}
void MainWindow::Show_tree_clicked()
{
   Show_tree* show = new Show_tree(this->path);
   show->show();
}
