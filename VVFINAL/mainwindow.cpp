#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "water.h"

/**
 * @class MainWindow
 * @brief Główne okno aplikacji.
 */
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

 /**
     * @brief Slot dla kliknięcia przycisku "START/STOP".
     */
void MainWindow::on_pushButton_clicked()
{
    if(!isStart)
    {
        ui->pushButton->setText("STOP");
        ui->pushButton->setStyleSheet("background-color: red; color:blue; font: 700 22pt;");
    }
    else
    {
        ui->pushButton->setText("START");
        ui->pushButton->setStyleSheet("background-color: green; color:blue; font: 700 22pt;");
    }
    isStart=!isStart;
    isStarted=true;
}


void MainWindow::on_RESTART_clicked()
{
    if(!isStart&&isStarted)
    {
    timeToRestart=true;
    }
}

