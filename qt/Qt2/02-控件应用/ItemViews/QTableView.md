### QTableView

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTableView *table_view;
    QStandardItemModel *model;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    table_view = new QTableView(this);
    table_view->setGeometry(QRect(50, 50, 330, 200));

    model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem("item1"));
    model->setHorizontalHeaderItem(1, new QStandardItem("item2"));
    model->setHorizontalHeaderItem(2, new QStandardItem("item3"));

    model->setItem(0, 0, new QStandardItem("a"));
    model->setItem(0, 1, new QStandardItem("b"));
    model->setItem(0, 2, new QStandardItem("c"));

    model->setItem(1, 0, new QStandardItem("d"));
    model->setItem(1, 1, new QStandardItem("e"));
    model->setItem(1, 2, new QStandardItem("f"));

    table_view->setModel(model);
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

