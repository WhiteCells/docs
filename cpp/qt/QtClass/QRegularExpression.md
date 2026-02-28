### QRegularExpression

### Case

```cpp
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

class Dialog : public QDialog {
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QPushButton *ok_btn, *cancel_btn;
    QLineEdit *input;
    QLabel *text;
    QHBoxLayout *hbox1, *hbox2;
    QVBoxLayout *vbox;

private slots:
    void checkInput();
};

#endif // DIALOG_H
```

```cpp
#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent) {
    hbox1 = new QHBoxLayout();
    text = new QLabel("Input: ");    
    input = new QLineEdit();
    QRegularExpression reg_exp("[a-zA-Z][0-9][0-9]{1,2}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(reg_exp, this);
    input->setValidator(validator);
    hbox1->addWidget(text);
    hbox1->addWidget(input);

    hbox2 = new QHBoxLayout();
    ok_btn = new QPushButton("Ok");
    ok_btn->setEnabled(false);
    cancel_btn = new QPushButton("Cancel");
    hbox2->addWidget(ok_btn);
    hbox2->addWidget(cancel_btn);

    vbox = new QVBoxLayout(this);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);

    connect(ok_btn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel_btn, &QPushButton::clicked, this, &QDialog::reject);
    connect(input, &QLineEdit::textChanged, this, &Dialog::checkInput);
}

Dialog::~Dialog() {
}

void Dialog::checkInput() {
    ok_btn->setEnabled(input->hasAcceptableInput());
}
```

```cpp
#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
```