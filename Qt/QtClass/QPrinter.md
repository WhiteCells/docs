### QPrinter

需要添加模块

`.pro` 文件添加：

```qmake
QT += printsupport
```

`CMakeLists.txt` 文件修改：

```cmake
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

target_link_libraries(QSplashScreen-case PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)
```

### Case

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLayout>

#include <QPrinter>
#include <QPrintDialog>

class Widget : public QWidget {
    Q_OBJECT
    
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    
private:
    QPushButton *btn;
    QTextEdit *text;
    QVBoxLayout *main_layout;
    
private slots:
    void showPrint();
};

#endif // WIDGET_H
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    text = new QTextEdit();
    btn = new QPushButton("fix print");
    main_layout = new QVBoxLayout(this);
    main_layout->addWidget(text);
    main_layout->addWidget(btn);
    this->connect(btn, &QPushButton::clicked, this, &Widget::showPrint);
}

Widget::~Widget() {
    
}

void Widget::showPrint() {
    QPrinter printer;
    QPrintDialog print_dialog(&printer, this);
    if (print_dialog.exec()) {
        QTextDocument *doc = text->document();
        doc->print(&printer);
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

