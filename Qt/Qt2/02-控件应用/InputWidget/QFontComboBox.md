### QFontComboBox

```cpp
#include <QWidget>
#include <QFontComboBox>
#include <QPushButton>
#include <QLabel>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QFontComboBox *font_combobox;
    QPushButton *btn;
    QLabel *label;

private slots:
    void showFont();
};
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    font_combobox = new QFontComboBox(this);
    font_combobox->setGeometry(QRect(50, 50, 120, 25));

    label = new QLabel("no font", this);
    label->setGeometry(QRect(50, 150, 300, 25));
    
    btn = new QPushButton("select", this);
    btn->move(180, 50);

    this->connect(btn, &QPushButton::released, this, &Widget::showFont);
}

Widget::~Widget() {

}

void Widget::showFont() {
    label->setText(font_combobox->currentText());
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

