### QTableWidget

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QTabWidget>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTabWidget *table_widget;
};

class TabA : public QWidget {
    Q_OBJECT
public:
    TabA(QWidget *parent = nullptr);
    ~TabA();
};

class TabB : public QWidget {
    Q_OBJECT
public:
    TabB(QWidget *parent = nullptr);
    ~TabB();
};

class TabC : public QWidget {
    Q_OBJECT
public:
    TabC(QWidget *parent = nullptr);
    ~TabC();
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    table_widget = new QTabWidget(this);
    table_widget->setGeometry(QRect(30, 30, 300, 200));
    table_widget->addTab(new TabA(), "widget1");
    table_widget->addTab(new TabB(), "widget2");
    table_widget->addTab(new TabC(), "widget3");
}

Widget::~Widget() {

}

TabA::TabA(QWidget *parent) : QWidget(parent) {
    QPushButton *button = new QPushButton(this);
    button->setText("TabA");
}

TabA::~TabA() {

}

TabB::TabB(QWidget *parent) : QWidget(parent) {
    QPushButton *button = new QPushButton(this);
    button->setText("TabB");
}

TabB::~TabB() {

}

TabC::TabC(QWidget *parent) : QWidget(parent) {
    QPushButton *button = new QPushButton(this);
    button->setText("TabC");
}

TabC::~TabC() {
    
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

