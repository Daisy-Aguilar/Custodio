#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
