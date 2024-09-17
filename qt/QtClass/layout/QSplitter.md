### QSplitter



### Case

```cpp
#ifndef SPLITTER_H
#define SPLITTER_H

#include <QWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QLayout>

class Splitter : public QWidget
{
    Q_OBJECT
    
public:
    Splitter(QSplitter *parent = nullptr);
    ~Splitter();

private:
    QSplitter *splitter_main, *splitter_right;
    QTextEdit * text;
    QHBoxLayout *hbox;
};

#endif // SPLITTER_H
```

```cpp
#include "splitter.h"

Splitter::Splitter(QSplitter *parent)
    : QWidget(parent) {
    this->setWindowTitle("QSplitter case");
    
    hbox = new QHBoxLayout(this);
    
    splitter_main = new QSplitter(Qt::Horizontal);
    text = new QTextEdit("main window", splitter_main);
    
    splitter_right = new QSplitter(Qt::Vertical, splitter_main);
    text = new QTextEdit("window 1", splitter_right);
    text = new QTextEdit("window 2", splitter_right);
    text = new QTextEdit("window 3", splitter_right);
    
    // 拖拽是否实时更新
    splitter_right->setOpaqueResize(false);
    
    splitter_main->setStretchFactor(1, 1);
    
    hbox->addWidget(splitter_main);
}

Splitter::~Splitter() {
}
```

```cpp
#include "splitter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Splitter w;
    w.show();
    return a.exec();
}
```

