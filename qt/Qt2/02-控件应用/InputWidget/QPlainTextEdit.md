### QPlainTextEdit

```cpp
#include <QWidget>
#include <QPlainTextEdit>

class MainWindow : public QWidget {
    Q_OBJECT
        
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPlainTextEdit *plain_text_edit;
};
```

```cpp
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    plain_text_edit = new QPlainTextEdit(this);
    // plain_text_edit->setGeometry(QRect(50, 50, 200, 100));
    plain_text_edit->setGeometry(50, 50, 200, 100);
    plain_text_edit->setPlainText("one line");
}

MainWindow::~MainWindow() {

}
```

```cpp
#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
```

