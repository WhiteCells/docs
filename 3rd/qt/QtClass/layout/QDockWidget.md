### QDockWidget







### Case

```cpp
#ifndef DOCKWINDOW_H
#define DOCKWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QTextEdit>

class DockWindow : public QMainWindow {
    Q_OBJECT
    
public:
    DockWindow(QWidget *parent = nullptr);
    ~DockWindow();
    
private:
    QDockWidget *dock;
    QTextEdit *text;
};

#endif // DOCKWINDOW_H
```



```cpp
#include "dockwindow.h"

DockWindow::DockWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle("QDockWindow case");
    text = new QTextEdit("main window", this);
    text->setAlignment(Qt::AlignCenter);
    // text 设为主窗口的中央窗口
    this->setCentralWidget(text);
    
    // dock window1
    dock = new QDockWidget("dock window1 title", this);
    dock->setFeatures(QDockWidget::DockWidgetMovable);
    // 设置停靠窗口的特性
    // DockWidgetClosable          可关闭
    // DockWidgetMovable           移动
    // DockWidgetFloatable         可浮动
    // DockWidgetVerticalTitleBar  左边垂直标题栏
    // DockWidgetFeatureMask
    // NoDockWidgetFeatures        不可移动、关闭、浮动
    // Reserved
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    // 设置停靠窗口的可停靠区域
    // Qt::LeftDockWidgetArea      主窗口左侧停靠
    // Qt::RightDockWidgetArea     主窗口右侧停靠
    // Qt::TopDockWidgetArea       主窗口顶部停靠
    // Qt::BottomDockWidgetArea    主窗口底部停靠
    // Qt::AllDockWidgetAreas      主窗口任意位置停靠
    // Qt::DockWidgetArea_Mask
    // Qt::NoDockWidgetArea        只可停靠处插入
    text = new QTextEdit("aaa", this);
    text->setAlignment(Qt::AlignLeft);
    dock->setWidget(text);
    // 主窗口添加指定停靠方式的停靠窗口
    this->addDockWidget(Qt::LeftDockWidgetArea, dock);
    
    // dock window2
    dock = new QDockWidget("dock Window2 title", this);
    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea);
    text = new QTextEdit("bbb", this);
    text->setAlignment(Qt::AlignLeft);
    dock->setWidget(text);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
    
    // dock window3
    dock = new QDockWidget("dock window3 title", this);
    dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    text = new QTextEdit("ccc", this);
    text->setAlignment(Qt::AlignLeft);
    dock->setWidget(text);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}

DockWindow::~DockWindow() {
}
```



```cpp
#include "dockwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    DockWindow w;
    w.show();
    return a.exec();
}
```

