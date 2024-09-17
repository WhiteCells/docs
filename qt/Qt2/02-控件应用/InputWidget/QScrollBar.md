### QScrollBar

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QScrollBar>
#include <QSpinBox>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QScrollBar *scroll_bar;
    QSpinBox *spin_box;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    scroll_bar = new QScrollBar(this);
    // 水平滚动条
    scroll_bar->setOrientation(Qt::Horizontal);
    // 垂直滚动条
    // scroll_bar->setOrientation(Qt::Vertical);
    // 位置
    scroll_bar->setGeometry(QRect(50, 0, 180, 20));
    // 滚动条的宽度
    scroll_bar->setPageStep(10);

    spin_box = new QSpinBox(this);
    this->connect(scroll_bar, &QScrollBar::valueChanged,
                  spin_box, &QSpinBox::setValue);
    this->connect(spin_box, &QSpinBox::valueChanged,
                  scroll_bar, &QScrollBar::setValue);
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

