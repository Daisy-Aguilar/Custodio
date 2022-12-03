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


void Widget::on_helpButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_backButton_0_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Widget::on_helpButton_1_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_stopScanButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_stopScanButton_1_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_chooseFileButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_chooseFolderButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_stopScanButton_2_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_chooseFileButton_1_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_chooseFolderButton_1_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_hourlyCheckBox_stateChanged(int arg1)
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_dailyCheckBox_stateChanged(int arg1)
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_weeklyCheckBox_stateChanged(int arg1)
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_monthlyCheckBox_stateChanged(int arg1)
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_viewQuarantineButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void Widget::on_backButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void Widget::on_viewQuarantineButton_1_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_deleteAllFilesButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_restoreFilesButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}


void Widget::on_backButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void Widget::on_chooseFilesButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_restoreFilesButton_2_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}

