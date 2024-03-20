### SVG

`CMakeLists.txt` 修改：

```cmake
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)

target_link_libraries(SVG-case PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)
```

`.pro` 文件

```qmake
QT += svg
```

### Case

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "svg_window.h"

#include <QMainWindow>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createMenu();

public slots:
    void openSVGFile();

private:
    SVGWindow *svg_window;
};

#endif // MAINWINDOW_H
```

```cpp
#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("SVG case");
    this->setMinimumSize(500, 400);
    createMenu();
    svg_window = new SVGWindow();
    this->setCentralWidget(svg_window);
}

MainWindow::~MainWindow() {

}

void MainWindow::createMenu() {
    QMenu *file_menu = menuBar()->addMenu("file");
    QAction *open_act = new QAction("open", this);
    this->connect(open_act, &QAction::triggered,
                  this, &MainWindow::openSVGFile);
    file_menu->addAction(open_act);
}

void MainWindow::openSVGFile() {
    QString name = QFileDialog::getOpenFileName(this, "open svg", "/", "file(*.svg)");
    svg_window->setFile(name);
}
```

```cpp
#ifndef SVG_WIDGET_H
#define SVG_WIDGET_H

#include <QtSvg>
#include <QSvgWidget>
#include <QSvgRenderer>

class SVGWidget : public QSvgWidget {
    Q_OBJECT
public:
    SVGWidget(QWidget *parent = nullptr);
    ~SVGWidget();

    void wheelEvent(QWheelEvent *);
private:
    QSvgRenderer *render;
};

#endif // SVG_WIDGET_H
```

```cpp
#include "svg_widget.h"

#include <QWheelEvent>

SVGWidget::SVGWidget(QWidget *parent) : QSvgWidget(parent) {
    render = this->renderer();
}

SVGWidget::~SVGWidget() {

}

void SVGWidget::wheelEvent(QWheelEvent *event) {
    const double diff = 0.1;
    if (event->angleDelta().y() > 0) {
        int width = int(this->width() + this->width() * diff);
        int height = int(this->height() + this->height() * diff);
        this->resize(width, height);
    } else if (event->angleDelta().y() < 0) {
        int width = int(this->width() - this->width() * diff);
        int height = int(this->height() - this->height() * diff);
        this->resize(width, height);
    }
}
```

```cpp
#ifndef SVG_WINDOW_H
#define SVG_WINDOW_H

#include "svg_widget.h"

#include <QScrollArea>

class SVGWindow : public QScrollArea {
    Q_OBJECT
public:
    SVGWindow(QWidget *parent = nullptr);
    ~SVGWindow();

    void setFile(QString);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    SVGWidget *svg_widget;
    QPoint mouse_press_point;
    QPoint scroll_bar_value_on_mouse_press;
};

#endif // SVG_WINDOW_H
```

```cpp
#include "svg_window.h"

#include <QMouseEvent>
#include <QScrollBar>

SVGWindow::SVGWindow(QWidget *parent) : QScrollArea(parent) {
    svg_widget = new SVGWidget();
    this->setWidget(svg_widget);
}

SVGWindow::~SVGWindow() {

}

void SVGWindow::setFile(QString file_path) {
    svg_widget->load(file_path);
    QSvgRenderer *render = svg_widget->renderer();
    svg_widget->resize(render->defaultSize());
}

void SVGWindow::mousePressEvent(QMouseEvent *event) {
    mouse_press_point = event->pos();
    scroll_bar_value_on_mouse_press.rx() = horizontalScrollBar()->value();
    scroll_bar_value_on_mouse_press.ry() = verticalScrollBar()->value();
    event->accept();
}

void SVGWindow::mouseMoveEvent(QMouseEvent *event) {
    horizontalScrollBar()->setValue(
        scroll_bar_value_on_mouse_press.x() - event->pos().x());
    verticalScrollBar()->setValue(
        scroll_bar_value_on_mouse_press.y() - event->pos().y());
    horizontalScrollBar()->update();
    verticalScrollBar()->update();
    event->accept();
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
