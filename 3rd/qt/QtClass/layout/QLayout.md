### QLayout

- QLayout
  - QBoxLayout
    - QHBoxLayout
    - QVBoxLayout
- QGridLayout

```cpp
// 添加布局的控件
void addWidget(
    QWidget *,  // 插入的控件对象
    int row,    // 插入的行
    int column, // 插入的列
    Qt::Alignment = Qt::Alignment() // 控件的对齐方式
);
void addWidget(
    QWidget *,      // 插入的控件对象
    int row,        // 插入的起始行
    int column,     // 插入的起始列
    int rowSpan,    // 占用的行
    int columnSpan, // 占用的列
    Qt::Alignment = Qt::Alignment() // 控件的对齐方式
);
```

```cpp
// 添加子布局
void addLayout(
    QLayout *,   // 插入的子布局对象
    int row,     // 插入的行
    int column,  // 插入的列
    Qt::Alignment = Qt::Alignment() // 子布局的对齐方式
);
void addLayout(
    QLayout *,      // 插入的子布局对象
    int row,        // 插入的行
    int column,     // 插入的列
    int rowSpan,    // 占用的行
    int columnSpan, // 占用的列
    Qt::Alignment = Qt::Alignment() // 子布局的对齐方式
);
```

### Case

```cpp
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private:
    // left layout
    QLabel *user_id;
    QLabel *user_name;
    QLabel *user_sex;
    QLabel *user_department;
    QLabel *user_age;
    QLabel *user_note;
    QLineEdit *user_id_input;
    QLineEdit *user_name_input;
    QComboBox *user_sex_input;
    QLineEdit *user_age_input;
    QTextEdit *user_department_input;
    QLineEdit *user_note_input;
    QGridLayout *left_layout;
    
    // right layout
    QLabel *user_avator;
    QLabel *user_avator_icon;
    QPushButton *user_avator_update_btn;
    QLabel *user_profile;
    QTextEdit *user_profile_input;
    QHBoxLayout *hbox_layout;
    QVBoxLayout *right_layout;
    
    // bottom layout
    QPushButton *ok_btn, *cancel_btn, *update_avator_btn;
    QHBoxLayout *bottom_layout;
    
    QGridLayout *main_layout;
};

#endif // MAINWINDOW_H
```



```cpp
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    this->setWindowTitle("用户信息");
    
    QWidget *widget = new QWidget(this);
    this->setCentralWidget(widget);
    
    // left layout
    user_name = new QLabel("姓名");
    user_name_input = new QLineEdit();
    user_id = new QLabel("用户名");
    user_id_input = new QLineEdit();
    user_sex = new QLabel("性别");
    user_sex_input = new QComboBox();
    user_sex_input->addItem("男");
    user_sex_input->addItem("女");
    user_department = new QLabel("部门");
    user_department_input = new QTextEdit();
    user_department_input->resize(100, 50);
    user_age = new QLabel("年龄");
    user_age_input = new QLineEdit();
    user_note = new QLabel("备注");
    user_note_input = new QLineEdit();
    
    left_layout = new QGridLayout();
    left_layout->addWidget(user_id, 0, 0);
    left_layout->addWidget(user_id_input, 0, 1);
    left_layout->addWidget(user_name, 1, 0);
    left_layout->addWidget(user_name_input, 1, 1);
    left_layout->addWidget(user_sex, 2, 0);
    left_layout->addWidget(user_sex_input, 2, 1);
    left_layout->addWidget(user_department, 3, 0);
    left_layout->addWidget(user_department_input, 3, 1);
    left_layout->addWidget(user_age, 4, 0);
    left_layout->addWidget(user_age_input, 4, 1);
    left_layout->addWidget(user_note, 5, 0);
    left_layout->addWidget(user_note_input, 5, 1);
    
    // right layout
    user_avator = new QLabel("头像");
    user_avator_icon = new QLabel();
    QPixmap icon("../../avator.png");
    user_avator_icon->setPixmap(icon);
    user_avator_icon->resize(icon.width(), icon.height());
    user_avator_update_btn = new QPushButton("更新");
    user_profile = new QLabel("个人说明");
    // user_profile->setFrameStyle();
    user_profile_input = new QTextEdit();
    
    right_layout = new QVBoxLayout();
    hbox_layout = new QHBoxLayout();
    hbox_layout->setSpacing(20);
    hbox_layout->addWidget(user_avator);
    hbox_layout->addWidget(user_avator_icon);
    hbox_layout->addWidget(user_avator_update_btn);
    
    right_layout->addLayout(hbox_layout);
    right_layout->addWidget(user_profile);
    right_layout->addWidget(user_profile_input);
    
    // bottom layout
    bottom_layout = new QHBoxLayout();
    ok_btn = new QPushButton("Ok");
    cancel_btn = new QPushButton("Cancel");
    // bottom_layout->addStretch();
    bottom_layout->addWidget(ok_btn);
    bottom_layout->addWidget(cancel_btn);
    
    // main layout
    main_layout = new QGridLayout(widget);
    main_layout->addLayout(left_layout, 0, 0);
    main_layout->addLayout(right_layout, 0, 1);
    main_layout->addLayout(bottom_layout, 1, 1, Qt::AlignRight);
    main_layout->setSpacing(10);
    // 窗口变化不影响控件大小，控件按 sizeHint() 大小显示
    main_layout->setSizeConstraint(QLayout::SetFixedSize);
    
    this->connect(ok_btn, &QPushButton::clicked, this, &QMainWindow::close);
    this->connect(cancel_btn, &QPushButton::clicked, this, &QMainWindow::close);
}

MainWindow::~MainWindow() {
}
```



```cpp
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
```

