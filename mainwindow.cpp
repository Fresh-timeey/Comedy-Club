#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLocale>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем и настраиваем таблицу
    tableWidget = new QTableWidget(2, 1, this);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Дата и время");
    tableWidget->setVerticalHeaderLabels(QStringList() << "Числовой формат" << "Словесный формат");

    // Устанавливаем ширину столбца
    tableWidget->setColumnWidth(0, 600);

    setCentralWidget(tableWidget);

    // Настраиваем таймер
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDateTime);


    // Обновляем дату и время при запуске
    updateDateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDateTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("dd.MM.yyyy HH:mm:ss");
    QString wordDateTime = dateTimeToWords(currentDateTime);

    tableWidget->setItem(0, 0, new QTableWidgetItem(formattedDateTime));
    tableWidget->setItem(1, 0, new QTableWidgetItem(wordDateTime));
}

QString MainWindow::dateTimeToWords(const QDateTime &dateTime)
{
    QStringList months = {"января", "февраля", "марта", "апреля", "мая", "июня",
                          "июля", "августа", "сентября", "октября", "ноября", "декабря"};
    QStringList hours = {"ноль", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять",
                         "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать",
                         "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать", "двадцать", "двадцать один",
                         "двадцать два", "двадцать три"};
    QStringList minutes_seconds = {"ноль", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять",
                                   "десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать",
                                   "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать", "двадцать", "двадцать одна",
                                   "двадцать две", "двадцать три", "двадцать четыре", "двадцать пять", "двадцать шесть",
                                   "двадцать семь", "двадцать восемь", "двадцать девять", "тридцать", "тридцать одна",
                                   "тридцать две", "тридцать три", "тридцать четыре", "тридцать пять", "тридцать шесть",
                                   "тридцать семь", "тридцать восемь", "тридцать девять", "сорок", "сорок одна", "сорок две",
                                   "сорок три", "сорок четыре", "сорок пять", "сорок шесть", "сорок семь", "сорок восемь",
                                   "сорок девять", "пятьдесят", "пятьдесят одна", "пятьдесят две", "пятьдесят три", "пятьдесят четыре",
                                   "пятьдесят пять", "пятьдесят шесть", "пятьдесят семь", "пятьдесят восемь", "пятьдесят девять"};

    int day = dateTime.date().day();
    int month = dateTime.date().month();
    int year = dateTime.date().year();
    int hour = dateTime.time().hour();
    int minute = dateTime.time().minute();
    int second = dateTime.time().second();

    QString wordDateTime = QString::number(day) + " " + months[month - 1] + " " +
                           QString::number(year) + " года " + hours[hour] + " часов " + minutes_seconds[minute] + " минут " + minutes_seconds[second] + " секунд";

    return wordDateTime;
}
