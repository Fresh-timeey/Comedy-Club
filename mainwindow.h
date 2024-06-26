#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTableWidget>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateDateTime();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTableWidget *tableWidget;
    QString dateTimeToWords(const QDateTime &dateTime);
};

#endif // MAINWINDOW_H
