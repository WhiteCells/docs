### QTimeEdit

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QTimeEdit>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTimeEdit *time_edit;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

#include <QDateTime>
#include <QTimer>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    time_edit = new QTimeEdit(this);
    time_edit->setGeometry(QRect(50, 50, 120, 20));
    // 获取系统时间
    QDateTime system_time = QDateTime::currentDateTime();
    // 将时分秒以 ":" 拆分赋予 list 数组
    QStringList time_list = system_time.toString("hh:mm:ss").split(':');
    // 设置显示格式，默认不显示秒
    time_edit->setDisplayFormat("hh:mm:ss");
    // 将时间绑定控件
    time_edit->setTime(QTime(time_list[0].toInt(), time_list[1].toInt(), time_list[2].toInt()));
}

Widget::~Widget() {
    
}
```

```cpp
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
```

