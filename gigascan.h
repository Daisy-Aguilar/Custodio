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
    QString fullScanCmd(); // for inputting command
    void setPath(const QString &path);
    QString getPath() const;
    void folderScan();
    QString folderCommand();

signals:
    void output(QString data);

public slots:
    void startCmd();
    void stopCmd();

private slots:
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void stateChanged(QProcess::ProcessState newState);
    void readyReadStandardOutput();

private:
    QProcess cmdPrompt;
    bool isRunning;
    void inputCommand();
    QString curPage;
    QString folderScanPath;

};

#endif // GIGASCAN_H
