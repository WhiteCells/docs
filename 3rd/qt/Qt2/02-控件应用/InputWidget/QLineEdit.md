### QLineEdit

```cpp
#include <QWidget>
#include <QLineEdit>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLineEdit *line_edit ;
};
```

```cpp
#include "widget.h"

#include <QRegularExpression>

Widget::Widget(QWidget *parent) : QWidget(parent) {
    line_edit = new QLineEdit(this);
    line_edit->setText("text");
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

