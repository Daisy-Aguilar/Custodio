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
    lockText();
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
    if(getIndex() == 3) { // put data in fullscanbox
        ui->plainTextEdit->appendPlainText(data);
    }
    if(getIndex() == 4) { // put data in folderscanbox
        ui->plainTextEdit_2->appendPlainText(data);
    }
    if(getIndex() == 5) {
        // send data to scheduled scan box
    }
}

void Widget::on_backButton_1_clicked() // move between pages
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_startFolderScanButton_clicked() // start folder scan
{
    //ui->stackedWidget->setCurrentIndex();
    scan.startCmd();
}


void Widget::on_backButton_2_clicked() // move between pages
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_startScheduledScanButton_clicked() // scheduled scan
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_backButton_3_clicked() // move between pages
{
    ui->stackedWidget->setCurrentIndex(2);
}


void Widget::on_backButton_4_clicked() // move between pages
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
    QString filename = QFileDialog::getOpenFileNames(this,tr("Open File"), "C://", "All Files (*.*);;").join("");
    ui->plainTextEdit_2->setPlainText(filename.toUtf8());
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

void Widget::on_stopFullScanButton_clicked() // stop scan
{
    scan.stopCmd();
}


void Widget::on_chooseDirectoryButton_clicked() // open file directory to choose folder
{
    QString filename = QFileDialog::getExistingDirectory(this, "Choose Folder");
    ui->plainTextEdit_2->setPlainText(filename.toUtf8());
}


void Widget::on_folderScanBox_textChanged() // reformat filepath to be used in cmdprompt
{
    QString path = ui->plainTextEdit_2->toPlainText();
    path.replace("/","\\");
    scan.setPath(path);
}


void Widget::on_stopFolderScan_clicked() // stop command prompt
{
    scan.stopCmd();
}

int Widget::getIndex() { // proxy to get index of page and return it to scan
    int curIndex = ui->stackedWidget->currentIndex();
    return(curIndex);
}

//void Widget::calendarTesting() {
    //ui->calendarWidget->firstDayOfWeek(); // possible for scheduled scan?
//}

void Widget::lockText() { // textboxes do not take input
    ui->plainTextEdit->setReadOnly(1); //fullScanBox
    ui->plainTextEdit_2->setReadOnly(1);} //folderScanBox
