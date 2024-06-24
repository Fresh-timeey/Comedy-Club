#include <QApplication>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QPixmap>
#include <cstdlib>
#include <ctime>

class ClockWidget : public QWidget {
public:
    ClockWidget(QWidget *parent = nullptr) : QWidget(parent) {
        srand(static_cast<unsigned>(time(nullptr)));
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &ClockWidget::updateTime);
        timer->start(1000);

        bgTimer = new QTimer(this);
        connect(bgTimer, &QTimer::timeout, this, &ClockWidget::changeBackground);
        bgTimer->start(3000);  //меняется на 2-3 секунду (30000 - 30 секунд)

        loadBackgroundImages();
        changeBackground();
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        if (!currentBg.isNull()) {
            painter.drawPixmap(rect(), currentBg);
        }

        drawClock(&painter);
    }

private:
    QTimer *timer;
    QTimer *bgTimer;
    QTime currentTime;
    QPixmap currentBg;
    QPixmap backgroundImages[5];
    //колво изображений(можно штук 7-10)
    void loadBackgroundImages() {
        backgroundImages[0] = QPixmap("1f.jpg");
        backgroundImages[1] = QPixmap("2f.jpg");
        backgroundImages[2] = QPixmap("3f.jpg");
        backgroundImages[3] = QPixmap("4f.jpg");
        backgroundImages[4] = QPixmap("5f.jpg");
    }

    void updateTime() {
        currentTime = QTime::currentTime();
        update();
    }

    void changeBackground() {
        int index = rand() % 5;    // %3 т.к 3 картинки на данный момент
        currentBg = backgroundImages[index];
        update();
    }

    void drawClock(QPainter *painter) {
        static const QPoint hourHand[3] = {
            QPoint(7, 8),
            QPoint(-7, 8),
            QPoint(0, -40)
        };
        static const QPoint minuteHand[3] = {
            QPoint(7, 8),
            QPoint(-7, 8),
            QPoint(0, -70)
        };
        static const QPoint secondHand[3] = {
            QPoint(7, 8),
            QPoint(-5, 8),   //изначально было(-7, 8)
            QPoint(0, -100)
        };

        //изначально было(207,0,127)
        QColor hourColor(255, 0, 0, 255);       //(227, 0, ) ярче; если послед 227 - ярко фиол
        //изначально было(0,167,187,191)
        QColor minuteColor(255, 165, 0, 255);
        //изначально было(0,117,187,191)
        QColor secondColor(255, 255, 0, 255);

        int side = qMin(width(), height());
        painter->setRenderHint(QPainter::Antialiasing);
        painter->translate(width() / 2, height() / 2);   //тут не надо менять
        painter->scale(side / 200.0, side / 200.0);

        painter->setPen(Qt::NoPen);
        painter->setBrush(hourColor);

        QTime time = currentTime;

        painter->save();
        painter->rotate(30.0 * (time.hour() + time.minute() / 60.0));
        painter->drawConvexPolygon(hourHand, 3);
        painter->restore();

        painter->setPen(hourColor);

        for (int i = 0; i < 12; ++i) {
            painter->drawLine(88, 0, 96, 0);
            painter->rotate(30.0);
        }

        painter->setPen(Qt::NoPen);
        painter->setBrush(minuteColor);

        painter->save();
        painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
        painter->drawConvexPolygon(minuteHand, 3);
        painter->restore();

        painter->setPen(minuteColor);

        for (int j = 0; j < 60; ++j) {
            if ((j % 5) != 0)
                painter->drawLine(92, 0, 96, 0);
            painter->rotate(6.0);
        }

        painter->setPen(Qt::NoPen);
        painter->setBrush(secondColor);

        painter->save();
        painter->rotate(6.0 * time.second());
        painter->drawConvexPolygon(secondHand, 3);
        painter->restore();

        for (int j = 0; j < 60; ++j) {
            if ((j % 5) != 0)
                painter->drawLine(96, 0, 96, 0);
            painter->rotate(6.0);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ClockWidget clock;
    clock.resize(600, 400);  //(-, |)
    clock.show();

    return app.exec();
}
