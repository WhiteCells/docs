```cpp
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QToolBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QToolBar *tool_bar1;
    QToolBar *tool_bar2;
    QToolBar *tool_bar3;
};

#endif // _MAINWINDOW_H_
```

```cpp
#include "mainwindow.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    tool_bar1 = addToolBar(tr("bar1"));
    tool_bar1->addAction(new QAction("tool1_1", this));
    tool_bar1->addAction(new QAction("tool1_2"));

    tool_bar2 = addToolBar(tr("bar2"));
    tool_bar2->addAction(new QAction("tool2_1", this));
    tool_bar2->addAction(new QAction("tool2_2"));

    tool_bar3 = addToolBar(tr("bar3"));
    tool_bar3->addAction(new QAction("tool3_1", this));
    tool_bar3->addAction(new QAction("tool3_2"));
}

MainWindow::~MainWindow() {
    
}
```

```cpp
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
```

