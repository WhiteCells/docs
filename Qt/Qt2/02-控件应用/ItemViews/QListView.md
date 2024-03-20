### QListView

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QListView>
#include <QStringListModel>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QListView *list_view;
    QStringListModel *model;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    list_view = new QListView(this);
    list_view->setGeometry(QRect(50, 50, 100, 100));
    QStringList str;
    str << "item1" << "item2" << "item3";
    model = new QStringListModel(str, this);
    list_view->setModel(model);
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

