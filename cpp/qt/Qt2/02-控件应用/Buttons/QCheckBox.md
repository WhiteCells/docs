### QCheckBox

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QString>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QCheckBox *check_box1;
    QCheckBox *check_box2;
    QCheckBox *check_box3;
    QLabel *label;
    QString select_result;

private slots:
    void checkChange();
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    check_box1 = new QCheckBox(this);
    check_box1->setGeometry(QRect(20, 10, 60, 20));
    check_box1->setText("check1");

    check_box2 = new QCheckBox(this);
    check_box2->setGeometry(QRect(20, 30, 60, 20));
    check_box2->setText("check2");

    check_box3 = new QCheckBox(this);
    check_box3->setGeometry(QRect(20, 50, 60, 20));
    check_box3->setText("check3");

    label = new QLabel(this);
    label->setGeometry(QRect(20, 70, 100, 20));
    label->setText("not select");

    this->connect(check_box1, &QCheckBox::stateChanged, this, checkChange);
    this->connect(check_box2, &QCheckBox::stateChanged, this, checkChange);
    this->connect(check_box3, &QCheckBox::stateChanged, this, checkChange);
}

Widget::~Widget() {

}

void Widget::checkChange() {
    if (this->sender() == check_box1) {
        if (check_box1->checkState() == Qt::Checked) {
            select_result += "1";
        } else {
            select_result.replace("1", "");
        }
    }
    if (this->sender() == check_box2) {
        if (check_box2->checkState() == Qt::Checked) {
            select_result += "2";
        } else {
            select_result.replace("2", "");
        }
    }
    if (this->sender() == check_box3) {
        if (check_box3->checkState() == Qt::Checked) {
            select_result += "3";
        } else {
            select_result.replace("3", "");
        }
    }
    label->setText(select_result);
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

