### QComboBox

```cpp
#include <QWidget>
#include <QComboBox>

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QComboBox *combox;
};
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    combox = new QComboBox(this);
    QStringList str;
    str << "item1" << "item2" << "item3";
    combox->addItems(str);
    combox->setGeometry(30, 30, 60, 40);
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

