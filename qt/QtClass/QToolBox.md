### QToolBox



### Case

```cpp
#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QToolBox>
#include <QToolButton>
#include <QGroupBox>
#include <QLayout>

class ToolBox : public QToolBox {
    Q_OBJECT
    
public:
    ToolBox(QWidget *parent = nullptr);
    ~ToolBox();
    
private:
    QToolButton *tool_btn11;
    QToolButton *tool_btn12;
    QGroupBox *group_box1;
    QVBoxLayout *vbox1;
    
    QToolButton *tool_btn21;
    QToolButton *tool_btn22;
    QGroupBox *group_box2;
    QVBoxLayout *vbox2;
};

#endif // TOOLBOX_H
```

```cpp
#include "toolbox.h"

ToolBox::ToolBox(QWidget *parent) : QToolBox(parent) {
    this->setWindowTitle("QToolBox case");
    
    tool_btn11 = new QToolButton();
    tool_btn11->setText("AAA");
    tool_btn11->setIcon(QPixmap("custom.png"));
    // 设置按钮大小
    tool_btn11->setIconSize(QPixmap("custom.png").size());
    tool_btn11->setAutoRaise(true);
    tool_btn11->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    tool_btn12 = new QToolButton();
    tool_btn12->setText("BBB");
    tool_btn12->setIcon(QPixmap("custom.png"));
    tool_btn12->setIconSize(QPixmap("custom.png").size());
    // 鼠标离开时按钮自动恢复为弹起状态
    tool_btn12->setAutoRaise(true);
    tool_btn12->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    /*
        ToolButtonIconOnly,
        ToolButtonTextOnly,
        ToolButtonTextBesideIcon,
        ToolButtonTextUnderIcon,
        ToolButtonFollowStyle
    */
    
    group_box1 = new QGroupBox();
    vbox1 = new QVBoxLayout(group_box1);
    vbox1->addWidget(tool_btn11);
    vbox1->addWidget(tool_btn12);
    vbox1->setAlignment(Qt::AlignCenter);

    tool_btn21 = new QToolButton();
    tool_btn21->setText("CCC");
    tool_btn21->setIcon(QPixmap("custom.png"));
    tool_btn21->setIconSize(QPixmap("custom.png").size());
    tool_btn21->setAutoRaise(true);
    tool_btn21->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    tool_btn22 = new QToolButton();
    tool_btn22->setText("DDD");
    tool_btn22->setIcon(QPixmap("custom.png"));
    tool_btn22->setIconSize(QPixmap("custom.png").size());
    tool_btn22->setAutoRaise(true);
    tool_btn22->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    group_box2 = new QGroupBox();
    vbox2 = new QVBoxLayout(group_box2);
    vbox2->addWidget(tool_btn21);
    vbox2->addWidget(tool_btn22);
    
    this->addItem((QWidget *)group_box1, "bar1");
    this->addItem((QWidget *)group_box2, "bar2");
}

ToolBox::~ToolBox() {
    
}
```

```cpp
#include "toolbox.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ToolBox w;
    w.show();
    return a.exec();
}
```

