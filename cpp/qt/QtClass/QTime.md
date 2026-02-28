### QTime



### Case

```cpp
#ifndef CLOCK_H
#define CLOCK_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QPalette>
#include <QPoint>

class Clock : public QLCDNumber {
    Q_OBJECT
    
public:
    Clock(QWidget *parent = nullptr);
    ~Clock();
    
private:
    QTimer *timer;
    QPointF drag_position;
    bool show_colon;
    
    // 重写
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    
private slots:
    void showTime();
};

#endif // CLOCK_H
```

```cpp
#include "clock.h"

Clock::Clock(QWidget *parent) : QLCDNumber(parent) {
    QPalette p = this->palette();
    p.setColor(QPalette::Window, Qt::white);
    p.setColor(QPalette::WindowText, Qt::lightGray);
    // 设置控件颜色
    this->setPalette(p);
    // 窗口标记
    this->setWindowFlags(Qt::FramelessWindowHint);
    // 透明度，X11 系统中不起作用
    this->setWindowOpacity(0.8);
    // 定时器
    timer = new QTimer(this);
    this->connect(timer, &QTimer::timeout, this, &Clock::showTime);
    // 每隔 1000ms 启动定时器
    timer->start(1000);
    showTime();
    this->resize(300, 60);
    show_colon = true;
}

Clock::~Clock() {
        
}

void Clock::showTime() {
    QString time_string = QTime::currentTime().toString();
    if (show_colon) {
        time_string[5] = ':';
        show_colon = false;
    } else {
        time_string[5] = ' ';
        show_colon = true;
    }
    // qDebug() << time_string;
    display(time_string);
}

void Clock::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drag_position = event->globalPosition() - this->frameGeometry().topLeft();
        event->accept();
    }
    if (event->button() == Qt::RightButton) {
        this->close();
    }
}

void Clock::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPointF point = event->globalPosition() - drag_position;
        this->move(point.rx(), point.ry());
        event->accept();
    }
}
```

```cpp
#include "clock.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Clock w;
    w.show();
    return a.exec();
}
```

