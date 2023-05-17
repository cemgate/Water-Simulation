#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!isStart)
    {
        ui->pushButton->setText("STOP");
    }
    else
    {
        ui->pushButton->setText("START");
    }
    isStart=!isStart;
}


void MainWindow::on_pushButton_2_clicked()
{

}

