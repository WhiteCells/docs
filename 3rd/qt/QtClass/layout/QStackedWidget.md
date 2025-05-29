### QStackedWidget





### Case

```cpp
#ifndef STACKEDDIALOG_H
#define STACKEDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QHBoxLayout>

class StackedDialog : public QDialog {
    Q_OBJECT
    
public:
    StackedDialog(QWidget *parent = nullptr);
    ~StackedDialog();

private:
    QListWidget* list_widget;
    QHBoxLayout* hbox_layout;
    QStackedWidget *stack_widget;
    QLabel *label1, *label2, *label3;
};

#endif // STACKEDDIALOG_H
```



```cpp
#include "stackeddialog.h"

StackedDialog::StackedDialog(QWidget *parent)
    : QDialog(parent) {
    this->setWindowTitle("QStackedWidget case");
    
    list_widget = new QListWidget(this);
    list_widget->insertItem(0, "window1");
    list_widget->insertItem(1, "window2");
    list_widget->insertItem(2, "window3");
    
    stack_widget = new QStackedWidget(this);
    label1 = new QLabel("aaa");
    label2 = new QLabel("bbb");
    label3 = new QLabel("ccc");
    // 先加入 index 为 0
    stack_widget->addWidget(label1);
    stack_widget->addWidget(label2);
    stack_widget->addWidget(label3);
    
    hbox_layout = new QHBoxLayout(this);
    // 设置控件间间隔为 5
    hbox_layout->setSpacing(5);
    hbox_layout->addWidget(list_widget);
    hbox_layout->addWidget(stack_widget, 0, Qt::AlignHCenter);
    // 设置拉伸因子
    hbox_layout->setStretchFactor(list_widget, 1);
    hbox_layout->setStretchFactor(stack_widget, 4);
    
    // connect(list_widget, SIGNAL(currentRowChanged(int)), stack_widget, SLOT(setCurrentIndex(int)));
    connect(list_widget, &QListWidget::currentRowChanged, stack_widget, &QStackedWidget::setCurrentIndex);
}

StackedDialog::~StackedDialog() {
}
```



```cpp
#include "stackeddialog.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    StackedDialog w;
    w.show();
    return a.exec();
}
```

