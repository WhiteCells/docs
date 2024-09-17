```cpp
#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

class Widget : public QWidget {
    Q_OBJECT
        
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QGridLayout *main_layout_;
    QLabel *file_path_label_;
    QLineEdit *file_path_edit_;
    QPushButton *browse_file_btn_;
    QLabel *node_label_;
    QLineEdit *node_edit_;
    QLabel *key_label_;
    QLineEdit *key_edit_;
    QLabel *val_label_;
    QLineEdit *val_edit_;
    QPushButton *create_btn_;
    QPushButton *write_btn_;
    QPushButton *read_btn_;
    QSettings *write_ini_;
    QSettings *read_ini_;

private slots:
    void browseIniFile();
    void createIniFile();
    void writeIniFile();
    void readIniFile();
};

#endif // _WIDGET_H_
```

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent) {
    file_path_label_ = new QLabel("ini file path");
    file_path_edit_ = new QLineEdit();
    browse_file_btn_ = new QPushButton("browse");
    node_label_ = new QLabel("node name");
    node_edit_ = new QLineEdit();
    key_label_ = new QLabel("key");
    key_edit_ = new  QLineEdit();
    val_label_ = new QLabel("val");
    val_edit_ = new QLineEdit();
    create_btn_ = new QPushButton("create");
    write_btn_ = new QPushButton("write");
    read_btn_ = new QPushButton("read");

    main_layout_ = new QGridLayout(this);
    main_layout_->addWidget(file_path_label_, 0, 0);
    main_layout_->addWidget(file_path_edit_, 0, 1);
    main_layout_->addWidget(browse_file_btn_, 0, 2);
    main_layout_->addWidget(node_label_, 1, 0);
    main_layout_->addWidget(node_edit_, 1, 1);
    main_layout_->addWidget(key_label_, 2, 0);
    main_layout_->addWidget(key_edit_, 2, 1);
    main_layout_->addWidget(val_label_, 3, 0);
    main_layout_->addWidget(val_edit_, 3, 1);

    btn_layout_ = new QHBoxLayout();
    btn_layout_->addWidget(create_btn_);
    btn_layout_->addWidget(write_btn_);
    btn_layout_->addWidget(read_btn_);

    main_layout_->addLayout(btn_layout_, 4, 0, 1, 3);
    
    this->connect(browse_file_btn_, &QPushButton::clicked,
                  this, &Widget::browseIniFile);

    this->connect(create_btn_, &QPushButton::clicked,
                  this, &Widget::createIniFile);

    this->connect(write_btn_, &QPushButton::clicked,
                  this, &Widget::writeIniFile);

    this->connect(read_btn_, &QPushButton::clicked,
                  this, &Widget::readIniFile);
}

Widget::~Widget() {

}

void Widget::browseIniFile() {
    QString ini_file_path = QFileDialog::getOpenFileName(this, "open ini file",
                                                         "/", "ini file(*.ini)");
    if (!ini_file_path.isEmpty()) {
        file_path_edit_->setText(ini_file_path);
    }
}

void Widget::createIniFile() {
    if (file_path_edit_->text().isEmpty()) {
        QMessageBox::warning(this, "create ini file", "path empty");
        return;
    }
    QFile new_ini_file(file_path_edit_->text());
    if (new_ini_file.exists()) {
        QMessageBox::warning(this, "create ini file",
                             "ini file exists");
    } else {
        writeIniFile();
        QMessageBox::warning(this, "create ini file",
                             "create success");
    }
    new_ini_file.close();
}

void Widget::writeIniFile() {
    if (file_path_edit_->text().isEmpty()
        || node_edit_->text().isEmpty()
        || key_edit_->text().isEmpty()
        || val_edit_->text().isEmpty()) {
        QMessageBox::warning(this, "write ini file", "write failed");
        return;
    }
    write_ini_ = new QSettings(file_path_edit_->text(),
                               QSettings::IniFormat);
    write_ini_->setValue(node_edit_->text() + "/" + key_edit_->text(),
                         val_edit_->text());
    delete write_ini_;
}

void Widget::readIniFile() {
    if (file_path_edit_->text().isEmpty()
        || node_edit_->text().isEmpty()
        || key_edit_->text().isEmpty()) {
        QMessageBox::warning(this, "read ini file", "read failed");
        return;
    }
    read_ini_ = new QSettings(file_path_edit_->text(),
                              QSettings::IniFormat);
    QString res = read_ini_->value(node_edit_->text() + "/"
                                   + key_edit_->text()).toString();
    val_edit_->setText(res);
    delete read_ini_;
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

