### QGroupBox

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QGroupBox *group_box;
    QPushButton *button;
    QVBoxLayout *vbox_layout;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    group_box = new QGroupBox(this);
    group_box->setGeometry(QRect(30, 30, 300, 100));
    group_box->setTitle("title");

    button = new QPushButton();
    button->setText("button");

    vbox_layout = new QVBoxLayout();
    vbox_layout->addWidget(button);

    group_box->setLayout(vbox_layout);
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

