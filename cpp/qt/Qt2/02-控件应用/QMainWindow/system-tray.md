### System Tray

```cpp
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>

class MainWindow : public QMainWindow {
    Q_OBJECT
        
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSystemTrayIcon *tray_icon;
    QMenu *menu;
    QAction *restore_action;
    QAction *quit_action;

    void createMenu();

    void changeEvent(QEvent *);

private slots:
    void showNormal();
};

#endif // _MAINWINDOW_H_
```

```cpp
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createMenu();
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        return;
    }
    tray_icon = new QSystemTrayIcon(this);
    tray_icon->setIcon(QIcon("case.svg"));
    tray_icon->setToolTip("system tray");
    tray_icon->showMessage("tray", "tray setting", QSystemTrayIcon::Information, 10000);
    tray_icon->setContextMenu(menu);
    tray_icon->show();
}

MainWindow::~MainWindow() {

}

void MainWindow::createMenu() {
    restore_action = new QAction("restore", this);
    quit_action = new QAction("quit", this);

    menu = new QMenu();
    menu->addAction(restore_action);
    menu->addSeparator();
    menu->addAction(quit_action);

    this->connect(restore_action, &QAction::triggered, this, &MainWindow::showNormal);
    this->connect(quit_action, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::showNormal() {
    this->show();
}

// 最小化自动隐藏
void MainWindow::changeEvent(QEvent *event) {
    if ((event->type() == QEvent::WindowStateChange) && this->isMinimized()) {
        this->hide();
    }
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

