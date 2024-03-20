### QSplashScreen

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
```

```cpp
#include "mainwindow.h"
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("QSplashScreen case");
    QTextEdit *edit = new QTextEdit();
    edit->setText("Splash example");
}

MainWindow::~MainWindow() {

}
```

```cpp
#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPixmap pix("case.png");
    QSplashScreen splash(pix);
    splash.show();
    // 使程序在在显示启动动画时依然能响应事件
    a.processEvents();
    MainWindow w;
    w.show();
    // 主窗口初始化完成后结束启动动画
    splash.finish(&w);
    return a.exec();
}
```

