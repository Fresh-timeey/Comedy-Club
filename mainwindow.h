#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCalendarWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dateTimeEdit_textChanged();
    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    QString numberToWords(int num);
};

#endif // MAINWINDOW_H
