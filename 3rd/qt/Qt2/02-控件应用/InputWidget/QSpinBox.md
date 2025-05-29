### QSpinBox

```cpp
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QHBoxLayout>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QSpinBox *spin_box;
};
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("QSpinBox");
    spin_box = new QSpinBox(this);
    spin_box->setGeometry(QRect(30, 30, 50, 20));
    // 初始值
    spin_box->setValue(10);
    // 值范围
    spin_box->setRange(0, 100);
    // 前缀
    spin_box->setPrefix("*");
    // 后缀
    spin_box->setSuffix("$");
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

