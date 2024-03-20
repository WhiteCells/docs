### QProgressBar



### Case

```cpp
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProgressDialog>

class Dialog : public QDialog {
    Q_OBJECT
    
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    
private:
    QLabel *file_num;
    QLineEdit *file_num_input;
    QLabel *display_type;
    QComboBox *display_type_input;
    QPushButton *start_btn;
    QProgressBar *progress_bar;
    QGridLayout *main_layout;
    
private slots:
    void startProgress();
};

#endif // DIALOG_H
```

```cpp
#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent) {
    this->setWindowTitle("progress bar case");
    
    file_num = new QLabel("file num");
    file_num_input = new QLineEdit("100000");
    display_type = new QLabel("display type");
    display_type_input = new QComboBox();
    display_type_input->addItem("progress bar");
    display_type_input->addItem("progress dialog");
    progress_bar = new QProgressBar();
    start_btn = new QPushButton("start");
    
    main_layout = new QGridLayout(this);
    main_layout->addWidget(file_num, 0, 0);
    main_layout->addWidget(file_num_input, 0, 1);
    main_layout->addWidget(display_type, 1, 0);
    main_layout->addWidget(display_type_input, 1, 1);
    main_layout->addWidget(progress_bar, 2, 0, 1, 2);
    main_layout->addWidget(start_btn, 3, 1);
    
    this->connect(start_btn, &QPushButton::clicked, this, &Dialog::startProgress);
}

Dialog::~Dialog() {
    
}

void Dialog::startProgress() {
    bool ok;
    int num = file_num_input->text().toInt(&ok);
    if (display_type_input->currentIndex() == 0) {
        progress_bar->setRange(0, num);
        for (int i = 1; i < num + 1; ++i) {
            progress_bar->setValue(i);
        }
    } else if (display_type_input->currentIndex() == 1) {
        QProgressDialog *progress_dialog = new QProgressDialog(this);
        // 在显示进度时其他窗口不响应输入信号
        progress_dialog->setWindowModality(Qt::WindowModal);
        // 进度对话框出现需等待的时间(秒)
        progress_dialog->setMinimumDuration(5);
        progress_dialog->setWindowTitle("please wait");
        progress_dialog->setLabelText("copying");
        progress_dialog->setCancelButtonText("Cancel Dialog");
        progress_dialog->setRange(0, num);
        for (int i = 1; i < num + 1; ++i) {
            progress_dialog->setValue(i);
            if (progress_dialog->wasCanceled()) {
                return;
            }
        }
    }
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

