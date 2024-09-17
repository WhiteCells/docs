### QPalette

改变某个控件的颜色外观

### Case

```cpp
#ifndef PALETTE_H
#define PALETTE_H

#include <QDialog>
#include <QPalette>
#include <QComboBox>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLayout>

class Palette : public QDialog {
    Q_OBJECT

public:
    Palette(QWidget *parent = nullptr);
    ~Palette();

    void createCtrlFrame();
    void createContentFrame();
    void fillColorList(QComboBox *);

private:
    // 左侧
    QFrame *ctrl_frame;
    QLabel *window_label;
    QComboBox *window_combobox;
    QLabel *window_text_label;
    QComboBox *window_text_combobox;
    QLabel *button_label;
    QComboBox *button_combobox;
    QLabel *button_text_label;
    QComboBox *button_text_combobox;
    QLabel *base_label;
    QComboBox *base_combobox;
    QGridLayout *ctrl_frame_layout;

    // 右侧
    QFrame *content_frame;
    QLabel *test1_label;
    QComboBox *test1_combobox;
    QLabel *test2_label;
    QLineEdit *test2_input;
    QTextEdit *text_edit;
    QGridLayout *top_layout;
    QPushButton *ok_btn;
    QPushButton *cancel_btn;
    QHBoxLayout *bottom_layout;
    QVBoxLayout *content_frame_layout;

    QHBoxLayout *main_layout;

private slots:
    void showWindow();
    void showWindowText();
    void showButton();
    void showButtonText();
    void showBase();
};

#endif // QPALETTECASE_H
```

```cpp
#include "palette.h"

Palette::Palette(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("QPalette case");
    createCtrlFrame();    
    createContentFrame();
    main_layout = new QHBoxLayout(this);
    main_layout->addWidget(ctrl_frame);
    main_layout->addWidget(content_frame);
}

Palette::~Palette() {

}

void Palette::createCtrlFrame() {
    window_label = new QLabel("QPalette::Window");
    window_combobox = new QComboBox();
    fillColorList(window_combobox);
    this->connect(window_combobox, &QComboBox::activated, this, &Palette::showWindow);

    window_text_label = new QLabel("QPalette::WindowText");
    window_text_combobox = new QComboBox();
    fillColorList(window_text_combobox);
    this->connect(window_text_combobox, &QComboBox::activated, this, &Palette::showWindowText);

    button_label = new QLabel("QPalette::Button");
    button_combobox = new QComboBox();
    fillColorList(button_combobox);
    this->connect(button_combobox, &QComboBox::activated, this, &Palette::showButton);

    button_text_label = new QLabel("QPalette::ButtonText");
    button_text_combobox = new QComboBox();
    fillColorList(button_text_combobox);
    this->connect(button_text_combobox, &QComboBox::activated, this, &Palette::showButtonText);

    base_label = new QLabel("QPalette::Base");
    base_combobox = new QComboBox();
    fillColorList(base_combobox);
    this->connect(base_combobox, &QComboBox::activated, this, &Palette::showBase);

    ctrl_frame = new QFrame();
    ctrl_frame_layout = new QGridLayout(ctrl_frame);
    ctrl_frame_layout->addWidget(window_label, 0, 0);
    ctrl_frame_layout->addWidget(window_combobox, 0, 1);
    ctrl_frame_layout->addWidget(window_text_label, 1, 0);
    ctrl_frame_layout->addWidget(window_text_combobox, 1, 1);
    ctrl_frame_layout->addWidget(button_label, 2, 0);
    ctrl_frame_layout->addWidget(button_combobox, 2, 1);
    ctrl_frame_layout->addWidget(button_text_label, 3, 0);
    ctrl_frame_layout->addWidget(button_text_combobox, 3, 1);
    ctrl_frame_layout->addWidget(base_label, 4, 0);
    ctrl_frame_layout->addWidget(base_combobox, 4, 1);
}

void Palette::createContentFrame() {
    test1_label = new QLabel("select num");
    test1_combobox = new QComboBox();
    test1_combobox->addItem("1");
    test1_combobox->addItem("2");
    test1_combobox->addItem("3");
    test2_label = new QLabel("input string");
    test2_input = new QLineEdit();
    text_edit = new QTextEdit();

    top_layout = new QGridLayout();
    top_layout->addWidget(test1_label, 0, 0);
    top_layout->addWidget(test1_combobox, 0, 1);
    top_layout->addWidget(test2_label, 1, 0);
    top_layout->addWidget(test2_input, 1, 1);
    top_layout->addWidget(text_edit, 2, 0, 2, 2);

    ok_btn = new QPushButton("OK");
    ok_btn->setAutoFillBackground(true);
    cancel_btn = new QPushButton("Cancel");
    cancel_btn->setAutoFillBackground(true);

    bottom_layout = new QHBoxLayout();
    bottom_layout->setAlignment(Qt::AlignRight);
    bottom_layout->addStretch(1); // 添加弹性控件
    bottom_layout->addWidget(ok_btn);
    bottom_layout->addWidget(cancel_btn);

    content_frame = new QFrame();
    content_frame->setAutoFillBackground(true);
    content_frame_layout = new QVBoxLayout(content_frame);
    content_frame_layout->addLayout(top_layout);
    content_frame_layout->addLayout(bottom_layout);
}

void Palette::showWindow() {
    qDebug() << "showWindow()";
    QStringList color_list = QColor::colorNames();
    QColor color = QColor(color_list[window_combobox->currentIndex()]);
    QPalette p = content_frame->palette();
    p.setColor(QPalette::Window, color);
    content_frame->setPalette(p);
    content_frame->update();
}

void Palette::showWindowText() {
    qDebug() << "showWindowText()";
    QStringList color_list = QColor::colorNames();
    QColor color = QColor(color_list[window_text_combobox->currentIndex()]);
    QPalette p = content_frame->palette();
    p.setColor(QPalette::WindowText, color);
    content_frame->setPalette(p);
}

void Palette::showButton() {
    qDebug() << "showButton()";
    QStringList color_list = QColor::colorNames();
    QColor color = QColor(color_list[button_combobox->currentIndex()]);
    QPalette p = content_frame->palette();
    p.setColor(QPalette::Button, color);
    content_frame->setPalette(p);
}

void Palette::showButtonText() {
    qDebug() << "showButtonText()";
    QStringList color_list = QColor::colorNames();
    QColor color = QColor(color_list[button_text_combobox->currentIndex()]);
    QPalette p = content_frame->palette();
    p.setColor(QPalette::ButtonText, color);
    content_frame->setPalette(p);
}

void Palette::showBase() {
    qDebug() << "showBase()";
    QStringList color_list = QColor::colorNames();
    QColor color = QColor(color_list[base_combobox->currentIndex()]);
    QPalette p = content_frame->palette();
    p.setColor(QPalette::Base, color);
    content_frame->setPalette(p);
}

void Palette::fillColorList(QComboBox *combobox) {
    QStringList color_list = QColor::colorNames();
    foreach (QString color, color_list) {
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color));
        combobox->addItem(QIcon(pix), NULL);
        combobox->setIconSize(QSize(70, 20));
        combobox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}
```

```cpp
#include "palette.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Palette w;
    w.show();
    return a.exec();
}
```
