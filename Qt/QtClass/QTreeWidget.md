### QTreeWidget



### Case

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QLayout>

class Widget : public QWidget {
    Q_OBJECT
    
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    
private:
    QTreeWidget *tree_widget;
    QTreeWidgetItem *group1;
    QTreeWidgetItem *sub11;
    QTreeWidgetItem *sub12;
    QTreeWidgetItem *sub13;
    QTreeWidgetItem *group2;
    QTreeWidgetItem *sub21;
    QTreeWidgetItem *sub22;
    QTreeWidgetItem *sub23;
    QHBoxLayout *main_layout;
    
    void updateGroupItemState(QTreeWidgetItem *item);
private slots:
    void changeTreeWidgetItem(QTreeWidgetItem *item);
};

#endif // WIDGET_H
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    this->setWindowTitle("QTreeWidget case");
    
    Qt::ItemFlags item_flags = Qt::ItemIsUserCheckable 
            | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    
    tree_widget = new QTreeWidget();
    
    group1 = new QTreeWidgetItem(tree_widget);
    group1->setFlags(item_flags);
    group1->setText(0, "group1");
    group1->setCheckState(0, Qt::Unchecked);
    
    sub11 = new QTreeWidgetItem(group1);
    sub11->setFlags(item_flags);
    sub11->setText(0, "sub1");
    sub11->setCheckState(0, Qt::Unchecked);
    
    sub12 = new QTreeWidgetItem(group1);
    sub12->setFlags(item_flags);
    sub12->setText(0, "sub2");
    sub12->setCheckState(0, Qt::Unchecked);
    
    sub13 = new QTreeWidgetItem(group1);
    sub13->setFlags(item_flags);
    sub13->setText(0, "sub3");
    sub13->setCheckState(0, Qt::Unchecked);
    
    group2 = new QTreeWidgetItem(tree_widget);
    group2->setFlags(item_flags);
    group2->setText(0, "group2");
    group2->setCheckState(0, Qt::Unchecked);
    
    sub21 = new QTreeWidgetItem(group2);
    sub21->setFlags(item_flags);
    sub21->setText(0, "sub21");
    sub21->setCheckState(0, Qt::Unchecked);
    
    sub22 = new QTreeWidgetItem(group2);
    sub22->setFlags(item_flags);
    sub22->setText(0, "sub22");
    sub22->setCheckState(0, Qt::Unchecked);
    
    sub23 = new QTreeWidgetItem(group2);
    sub23->setFlags(item_flags);
    sub23->setText(0, "sub23");
    sub23->setCheckState(0, Qt::Unchecked);
    
    main_layout = new QHBoxLayout(this);
    main_layout->addWidget(tree_widget, 0, Qt::AlignCenter);
    main_layout->setSizeConstraint(QLayout::SetFixedSize);
    
    this->connect(tree_widget, &QTreeWidget::itemChanged, 
                  this, &Widget::changeTreeWidgetItem);
}

Widget::~Widget() {
    
}

void Widget::updateGroupItemState(QTreeWidgetItem *item) {
    if (item->parent()) {
        int select_cnt = 0;
        int child_cnt = item->parent()->childCount();
        for (int i = 0; i < child_cnt; ++i) {
            if (item->parent()->child(i)->checkState(0) == Qt::Checked) {
                ++select_cnt;
            }
        }
        if (child_cnt == select_cnt) {
            item->parent()->setCheckState(0, Qt::Checked);
        } else if (select_cnt > 0 && select_cnt < child_cnt) {
            item->parent()->setCheckState(0, Qt::PartiallyChecked);
        } else if (0 == select_cnt) {
            item->parent()->setCheckState(0, Qt::Unchecked);
        }
    }
}

// Qt::ItemIsAutoTristate
void Widget::changeTreeWidgetItem(QTreeWidgetItem *item) {
    if (item->childCount() > 0) {
        if (item->checkState(0) == Qt::Checked) {
            for (int i = 0; i < item->childCount(); ++i) {
                item->child(i)->setCheckState(0, Qt::Checked);
            }
        } else if (item->checkState(0) == Qt::Unchecked) {
            for (int i = 0; i < item->childCount(); ++i) {
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
        }
    } else if (item->parent()) {
        updateGroupItemState(item);
    }
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

