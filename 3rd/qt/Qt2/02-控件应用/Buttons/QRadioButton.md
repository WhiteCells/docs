### QRadioButton

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QRadioButton>
#include <QLabel>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QRadioButton *radio_man;
    QRadioButton *radio_woman;
    QLabel *label;

private slots:
    void radioChange();
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    radio_man = new QRadioButton(this);
    radio_man->setGeometry(QRect(50, 50, 50, 50));
    radio_man->setText("man");

    radio_woman = new QRadioButton(this);
    radio_woman->setGeometry(QRect(100, 50, 80, 50));
    radio_woman->setText("woman");

    label = new QLabel("no select", this);
    label->setGeometry(QRect(50, 100, 100, 25));

    this->connect(radio_man, &QRadioButton::clicked,
                  this, &Widget::radioChange);
    this->connect(radio_woman, &QRadioButton::clicked,
                  this, &Widget::radioChange);
}

Widget::~Widget() {

}

void Widget::radioChange() {
    if (this->sender() == radio_man) {
        label->setText("man");
    } else if (this->sender() == radio_woman) {
        label->setText("woman");
    }
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

