### QHBoxLayout

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QHBoxLayout *hbox_layout;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    hbox_layout = new QHBoxLayout(this);
    // 间隔
    hbox_layout->setSpacing(60);

    button1 = new QPushButton("button1");
    button2 = new QPushButton("button2");
    button3 = new QPushButton("button3");

    hbox_layout->addWidget(button1);
    hbox_layout->addWidget(button2);
    hbox_layout->addWidget(button3);
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

