#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Widget::on_scanButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_historyButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void Widget::on_fullScanButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void Widget::on_folderScanButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void Widget::on_scheduledScanButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void Widget::on_backButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void Widget::on_startFullScanButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_backButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_startFolderScanButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_startScheduledScanButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_backButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_backButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

