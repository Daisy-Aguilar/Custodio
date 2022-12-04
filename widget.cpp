#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QPixmap>
#include <fstream>
#include <iostream>
#include <QDate>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&scan,&gigaScan::output,this,&Widget::output);
    connect(&scan,&gigaScan::getIndex,this,&Widget::getIndex);
    lockText();
    QPixmap pix("C:../Custodio/Logo/logopng.png");
    ui->label->setPixmap(pix.scaled(500,500,Qt::KeepAspectRatio)); //image on page_0
    QPixmap pix_1("C:../Custodio/Logo/resizedLogo.png");
    ui->label_1->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_1
    ui->label_15->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_2
    ui->label_30->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_3
    ui->label_31->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_4
    ui->label_36->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_5
    ui->label_42->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_6
    ui->label_52->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_7
    ui->label_64->setPixmap(pix_1.scaled(250,250,Qt::KeepAspectRatio)); //image on page_8
    connect(&scan,&gigaScan::output,this,&Widget::output);
    connect(&scan,&gigaScan::isDailyChecked,this,&Widget::isDailyChecked);
    connect(&scan,&gigaScan::isWeeklyChecked,this,&Widget::isWeeklyChecked);
    connect(&scan,&gigaScan::isMonthlyChecked,this,&Widget::isMonthlyChecked);
    connect(&scan,&gigaScan::giveMonth,this,&Widget::giveMonth);
    connect(&scan,&gigaScan::giveDate,this,&Widget::giveDate);
    connect(&scan,&gigaScan::giveWeekNum,this,&Widget::giveWeekNum);
    connect(&scan,&gigaScan::readPath,this,&Widget::readPath);
    isMonthlyChecked();
    setCheckBoxes();
    ui->calendarWidget->setVisible(0);
    ui->plainTextEdit_5->setPlainText(readPath().replace("\\\\","/"));
    scan.startCmd();
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
    /*if(getIndex() == 5) {
        ui->plainTextEdit_4->appendPlainText(data);
    } */
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


void Widget::on_updateScheduledScanButton_clicked()
{
    if(ui->monthlyCheckBox->isChecked()) {
        std::ofstream file;
        file.open("..\\Custodio\\dateChecksAndFlags\\mCheck.txt");
        file << "1 \n";
        file.close();
     } else {
        std::ofstream file;
        file.open("..\\Custodio\\dateChecksAndFlags\\mCheck.txt");
        file << "0 \n";
        file.close();
    }
    if(ui->dailyCheckBox->isChecked()) {
        std::ofstream file;
        file.open("..\\Custodio\\dateChecksAndFlags\\dailyCheck.txt");
        file << "1 \n";
        file.close();
     } else {
        std::ofstream file;
        file.open("..\\Custodio\\dateChecksAndFlags\\dailyCheck.txt");
        file << "0 \n";
        file.close();
    }
    if(ui->weeklyCheckBox->isChecked()) {
        std::ofstream file;
        file.open("..\\Custodio\\dateChecksAndFlags\\weeklyCheck.txt");
        file << "1 \n";
        file.close();
     } else {
        std::ofstream file;
        file.open("..\\Custodio\\dateChecksAndFlags\\weeklyCheck.txt");
        file << "0 \n";
        file.close();
    }
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
    scan.stopCmd();
}


void Widget::on_stopScanButton_1_clicked()
{
    scan.stopCmd();
}


void Widget::on_chooseFileButton_clicked()
{
    QString filename = QFileDialog::getOpenFileNames(this,tr("Open File"), "C://", "All Files (*.*);;").join("");
    ui->plainTextEdit_3->setPlainText(filename.toUtf8());
}

void Widget::on_stopScanButton_2_clicked()
{
    //ui->stackedWidget->setCurrentIndex();
}


void Widget::on_chooseFileButton_1_clicked()
{
    QString filename = QFileDialog::getOpenFileNames(this,tr("Open File"), "C://", "All Files (*.*);;").join("");
    ui->plainTextEdit_5->setPlainText(filename.toUtf8());
}


void Widget::on_chooseFolderButton_1_clicked()
{
    QString filename = QFileDialog::getExistingDirectory(this, "Choose Folder");
    ui->plainTextEdit_5->setPlainText(filename.toUtf8());

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


void Widget::on_chooseFolderButton_clicked() // open file directory to choose folder
{
    QString filename = QFileDialog::getExistingDirectory(this, "Choose Folder");
    ui->plainTextEdit_3->setPlainText(filename.toUtf8());
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
    ui->plainTextEdit_2->setReadOnly(1); //folderScanBox
    ui->plainTextEdit_3->setReadOnly(1); //folderScanBox
    ui->plainTextEdit_4->setReadOnly(1);
    ui->plainTextEdit_5->setReadOnly(1);
    ui->plainTextEdit_6->setReadOnly(1);
    ui->plainTextEdit_7->setReadOnly(1);
}

bool Widget::isDailyChecked() {
    bool daily;
    if(ui->dailyCheckBox->isChecked()) {
        daily = 1;
    }
    return daily;
}

bool Widget::isWeeklyChecked() {
    bool weekly;
    if(ui->weeklyCheckBox->isChecked()) {
        weekly = 1;
    }
    return weekly;
}

bool Widget::isMonthlyChecked() {
    bool monthly;
    if(ui->monthlyCheckBox->isChecked()) {
        monthly = 1;
    }
    return monthly;
}

int Widget::giveMonth() {
    return ui->calendarWidget->monthShown();
}

QString Widget::giveDate() {
    return ui->calendarWidget->selectedDate().toString();
}

int Widget::giveWeekNum() {
    return ui->calendarWidget->selectedDate().QDate::weekNumber();

}

void Widget::setCheckBoxes() {
    std::fstream file;
    file.open("..\\Custodio\\dateChecksAndFlags\\mCheck.txt");
    std::string str;
     while (1) {
        file >> str;
        if (file.eof())
            break;
     }
    file.close();
    if (str == "1") {
        ui->monthlyCheckBox->setChecked(1);
    } else {
        ui->monthlyCheckBox->setChecked(0);
    }
    file.open("..\\Custodio\\dateChecksAndFlags\\weeklyCheck.txt");
     while (1) {
        file >> str;
        if (file.eof())
            break;
     }
     file.close();
    if (str == "1") {
        ui->weeklyCheckBox->setChecked(1);
    } else {
        ui->weeklyCheckBox->setChecked(0);
    }
    file.open("..\\Custodio\\dateChecksAndFlags\\dailyCheck.txt");
     while (1) {
        file >> str;
        if (file.eof())
            break;
     }
     file.close();
    if (str == "1") {
        ui->dailyCheckBox->setChecked(1);
    } else {
        ui->dailyCheckBox->setChecked(0);
    }
}

void Widget::on_plainTextEdit_5_textChanged()
{
    QString path = ui->plainTextEdit_5->toPlainText();
    path.replace("/","\\\\");
    scan.savePath(path);
}

void Widget::on_plainTextEdit_3_textChanged()
{
    QString path = ui->plainTextEdit_3->toPlainText();
    path.replace("/","\\");
    scan.setPath(path);
}

QString Widget::readPath() {
    std::fstream file;
    file.open("..\\Custodio\\savedPath.txt");
    std::string str;
     while (1) {
        file >> str;
        if (file.eof())
            break;
     }
    file.close();
    QString path = QString::fromStdString(str);
    path.replace("_"," ");
    return path;
}

void Widget::scanOnSchedule() {

}
