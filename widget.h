#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gigascan.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void output(QString data);

    int getIndex();

    void on_startButton_clicked();

    void on_scanButton_clicked();

    void on_historyButton_clicked();

    void on_fullScanButton_clicked();

    void on_folderScanButton_clicked();

    void on_scheduledScanButton_clicked();

    void on_backButton_clicked();

    void on_startFullScanButton_clicked();

    void on_backButton_1_clicked();

    void on_startFolderScanButton_clicked();

    void on_backButton_2_clicked();

    void on_startScheduledScanButton_clicked();

    void on_backButton_3_clicked();

    void on_backButton_4_clicked();

    void on_helpButton_clicked();

    void on_backButton_0_clicked();

    void on_helpButton_1_clicked();

    void on_stopScanButton_clicked();

    void on_stopScanButton_1_clicked();

    void on_chooseFileButton_clicked();

    void on_chooseFolderButton_clicked();

    void on_stopScanButton_2_clicked();

    void on_chooseFileButton_1_clicked();

    void on_chooseFolderButton_1_clicked();

    void on_hourlyCheckBox_stateChanged(int arg1);

    void on_dailyCheckBox_stateChanged(int arg1);

    void on_weeklyCheckBox_stateChanged(int arg1);

    void on_monthlyCheckBox_stateChanged(int arg1);

    void on_viewQuarantineButton_clicked();

    void on_backButton_5_clicked();

    void on_viewQuarantineButton_1_clicked();

    void on_deleteAllFilesButton_clicked();

    void on_restoreFilesButton_clicked();

    void on_backButton_6_clicked();

    void on_chooseFilesButton_clicked();

    void on_restoreFilesButton_2_clicked();

    void on_stopFullScanButton_clicked();

    void on_stopFolderScan_clicked();

    void on_plainTextEdit_5_textChanged();

    //void calendarTesting();

    bool isDailyChecked();
    bool isWeeklyChecked();
    bool isMonthlyChecked();
    int giveMonth();
    void setCheckBoxes();
    QString giveDate();
    int giveWeekNum();
    void lockText();
    QString readPath();
    void scanOnSchedule();


    void on_plainTextEdit_3_textChanged();

private:
    Ui::Widget *ui;
    gigaScan scan;
};
#endif // WIDGET_H
