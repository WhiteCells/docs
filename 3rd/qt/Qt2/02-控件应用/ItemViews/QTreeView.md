### QTreeView

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QTreeView *tree_view;
    QStandardItemModel *model;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    tree_view = new QTreeView(this);
    tree_view->setGeometry(QRect(50, 50, 150, 200));
    
    // 数列数据类型 3 行 2 列
    model = new QStandardItemModel(3, 2);
    model->setHeaderData(0, Qt::Horizontal, "col1");
    model->setHeaderData(1, Qt::Horizontal, "col2");

    QStandardItem *item1 = new QStandardItem("item1");
    item1->setIcon(QIcon(QPixmap("/home/cells/wcdir/Users/Xuan/Pictures/case.svg")));

    QStandardItem *item2 = new QStandardItem("item2");
    item2->setIcon(QIcon(QPixmap("/home/cells/wcdir/Users/Xuan/Pictures/case.svg")));

    QStandardItem *item3 = new QStandardItem("item3");
    item3->setIcon(QIcon(QPixmap("/home/cells/wcdir/Users/Xuan/Pictures/case.svg")));

    // itme3 子项
    QStandardItem *item3_1 = new QStandardItem("item3_1");
    item3_1->setIcon(QIcon(QPixmap("/home/cells/wcdir/Users/Xuan/Pictures/case.svg")));
    item3->appendRow(item3_1);

    model->setItem(0, 0, item1);
    model->setItem(1, 0, item2);
    model->setItem(2, 0, item3);

    tree_view->setModel(model);
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

