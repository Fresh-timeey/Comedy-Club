#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->dateTimeEdit, &QLineEdit::textChanged, this, &MainWindow::on_dateTimeEdit_textChanged);


    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &MainWindow::on_calendarWidget_selectionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dateTimeEdit_textChanged()
{
    QString inputText = ui->dateTimeEdit->text();
    QDateTime dateTime = QDateTime::fromString(inputText, "dd.MM.yyyy hh:mm:ss");
    if (dateTime.isValid()) {
        QDate date = dateTime.date();
        QTime time = dateTime.time();

        QString dayString = numberToWords(date.day());
        QString monthString = QLocale(QLocale::Russian).toString(date, "MMMM");
        QString yearString = numberToWords(date.year());

        QString hourString = numberToWords(time.hour());
        QString minuteString = numberToWords(time.minute());
        QString secondString = numberToWords(time.second());

        QString dateString = QString("%1 %2 %3 года").arg(dayString, monthString, yearString);
        QString timeString = QString("%1 часов(час/часа) %2 минут(минуты/минута) %3 секунд(секунды/секунда)").arg(hourString, minuteString, secondString);


        ui->dateTimeLabel->setWordWrap(true);

        ui->dateTimeLabel->setText(dateString + "\n" + timeString);
    } else {
        ui->dateTimeLabel->setText("Неверный формат даты или времени");
    }
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    QDate selectedDate = ui->calendarWidget->selectedDate();
    QString dateString = selectedDate.toString("dd.MM.yyyy");
    ui->dateTimeEdit->setText(dateString);
}

QString MainWindow::numberToWords(int num)
{
    static const QStringList units = {"ноль", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
    static const QStringList teens = {"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
    static const QStringList tens = {"", "", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"};
    static const QStringList hundreds = {"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"};
    static const QStringList thousands = {"", "тысяча", "тысячи", "тысяч"};

    if (num < 10)
        return units[num];
    else if (num < 20)
        return teens[num - 10];
    else if (num < 100)
        return tens[num / 10] + (num % 10 != 0 ? " " + units[num % 10] : "");
    else if (num < 1000)
        return hundreds[num / 100] + (num % 100 != 0 ? " " + numberToWords(num % 100) : "");
    else if (num < 1000000)
        return numberToWords(num / 1000) + " " + thousands[(num / 1000) % 10 == 1 ? 1 : (num / 1000) % 10 > 1 && (num / 1000) % 10 < 5 ? 2 : 3] + (num % 1000 != 0 ? " " + numberToWords(num % 1000) : "");

    return QString::number(num);
}
