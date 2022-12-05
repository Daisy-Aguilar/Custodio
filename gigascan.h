#ifndef GIGASCAN_H
#define GIGASCAN_H

#include <QObject>
#include <QDebug>
#include <QSysInfo>
#include <QProcess>
#include <QRegularExpression>

class gigaScan : public QObject
{
    Q_OBJECT
public:
    explicit gigaScan(QObject *parent = nullptr); // for scanning
    QString fullScanCmd(); // for inputting fullscan command
    void setPath(const QString &path); // set and getPath are used as a proxy to return filepath to scan
    QString getPath() const;
    QString folderCommand(); // for inputting folderscan command
    QString scheduledScan();
    void savePath(QString pathToSave);
    QString updateDatabase();
    QString deleteQuarantine();

signals:
    void output(QString data); // function that displays our data to a widget
    int getIndex(); // proxy to get index to scan
    bool isDailyChecked(); // flag
    bool isWeeklyChecked();
    bool isMonthlyChecked();
    int giveMonth();
    void setCheckBoxes();
    QString giveDate();
    int giveWeekNum();
    QString readPath();

public slots:
    void startCmd(); // start and stop command prompt in QProcess
    void stopCmd();

private slots:
    void stateChanged(QProcess::ProcessState newState);
    void readyReadStandardOutput();

private:
    QProcess cmdPrompt; // linking QProcess to cmdPrompt
    bool isRunning; // flag to see if cmd is running or not
    void inputCommand(); // input command to command prompt in qprocess
    QString folderScanPath; // path that gets used in folderscancmd

};

#endif // GIGASCAN_H
