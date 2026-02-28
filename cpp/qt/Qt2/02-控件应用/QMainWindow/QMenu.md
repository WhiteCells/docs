### QMenu QToolBar

```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QToolBar>

class Widget : public QMainWindow {
    Q_OBJECT
        
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QMenu *file_menu;
    QAction *new_act;

    QMenu *edit_menu;
    QAction *cut_act;
    QAction *copy_act;
    QAction *paste_act;
    
    QMenu *help_menu;
    QAction *about_act;
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"
#include <QMessageBox>
#include <QMenuBar>

Widget::Widget(QWidget *parent) : QMainWindow(parent) {
    file_menu = menuBar()->addMenu("file");
    new_act = new QAction("new");
    new_act->setShortcut(tr("Ctrl + N"));
    new_act->setStatusTip(tr("create new file"));
    file_menu->addAction(new_act);
    file_menu->addSeparator();

    edit_menu = menuBar()->addMenu("edit");
    cut_act = new QAction("cut");
    cut_act->setShortcut(tr("Ctrl + X"));
    cut_act->setStatusTip("cut text");
    copy_act = new QAction("copy");
    copy_act->setShortcut(tr("Ctrl + C"));
    copy_act->setStatusTip("copy text");
    paste_act = new QAction("paste");
    paste_act->setShortcut(tr("Ctrl + V"));
    paste_act->setStatusTip("paste text");
    edit_menu->addAction(cut_act);
    edit_menu->addAction(copy_act);
    // 水平分割符
    edit_menu->addSeparator();
    edit_menu->addAction(paste_act);
    
    help_menu = menuBar()->addMenu("help");
    about_act = new QAction("about");
    about_act->setStatusTip("about");
    help_menu->addAction(about_act);
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

