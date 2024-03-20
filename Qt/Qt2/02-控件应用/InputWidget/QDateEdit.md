### QDateEdit

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QDateEdit>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QDateEdit *date_edit;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

#include <QDateTime>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    date_edit = new QDateEdit(this);
    date_edit->setGeometry(QRect(50, 50, 120, 20));
    QDateTime system_time = QDateTime::currentDateTime();
    QStringList list = system_time.toString("yyyy-MM-dd").split('-');
    date_edit->setDate(QDate(list[0].toInt(), list[1].toInt(), list[2].toInt()));
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

