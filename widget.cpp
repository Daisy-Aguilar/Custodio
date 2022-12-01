#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&scan,&gigaScan::output,this,&Widget::output);
    connect(&scan,&gigaScan::getIndex,this,&Widget::getIndex);

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
    scan.startCmd();
}

void Widget::output(QString data) {
    if(getIndex() == 3) {
        ui->plainTextEdit->appendPlainText(data); // folder scan box
    }
    if(getIndex() == 4) {
        ui->folderScanBox->appendPlainText(data);
    }
    if(getIndex() == 5) {
        // send data to scheduled scan box
    }
}

void Widget::on_backButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_startFolderScanButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
    scan.startCmd();
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


void Widget::on_stopFullScanButton_clicked()
{
    scan.stopCmd();
}


void Widget::on_chooseDirectoryButton_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this, "Choose Folder");
    ui->folderScanBox->setPlainText(filename.toUtf8());
}


void Widget::on_chooseFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileNames(this,tr("Open File"), "C://", "All Files (*.*);;").join("");
    ui->folderScanBox->setPlainText(filename.toUtf8());
}

void Widget::on_folderScanBox_textChanged()
{
    QString path = ui->folderScanBox->toPlainText();
    path.replace("/","\\");
    scan.setPath(path);
}


void Widget::on_stopFolderScan_clicked()
{
    scan.stopCmd();
}

int Widget::getIndex() {
    int curIndex;
    curIndex = ui->stackedWidget->currentIndex();
    return(curIndex);
}
