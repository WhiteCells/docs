### QGridLayout

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QGridLayout *gird_layout;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    gird_layout = new QGridLayout(this);

    button1 = new QPushButton("button1");
    button2 = new QPushButton("button2");
    button3 = new QPushButton("button3");
    button4 = new QPushButton("button4");

    gird_layout->addWidget(button1, 0, 0, 1, 1);
    gird_layout->addWidget(button2, 0, 1, 1, 1);
    gird_layout->addWidget(button3, 1, 0, 1, 1);
    gird_layout->addWidget(button4, 1, 1, 1, 1);
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

