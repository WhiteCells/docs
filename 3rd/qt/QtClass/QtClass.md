### QString

```cpp
#ifndef QSTRING_CASE_H
#define QSTRING_CASE_H

#include <QString>
#include <QDebug>

void QString1() {
    QString str = "hello";
    str += " world";
    str.append('!');
    str.push_back('~');
    str.push_front("*");
    qDebug() << str; // "*hello world!~"

    QString str2 = QString::asprintf("%s", "hello world");
    qDebug() << str2; // "hello world"

    // QString str3 = QString("%1 test %2").arg("hello").arg("world");
    QString str3 = QString("%1 test %2").arg("hello", "world");
    qDebug() << str3; // "hello test world"

    QString str4 = "hello world";
    str4.insert(0, "!");
    str4.prepend("c");
    str4.replace("hello", "world");
    qDebug() << str4; // "c!world world"

    QString str5 = " hello\n ";
    str5 = str5.trimmed();
    qDebug() << str5; // "hello"

    QString str6 = " he\tllo\n ";
    str6 = str6.simplified();
    qDebug() << str6; // "he llo"

    QString str7 = "hello world";
    // Qt::CaseSensitive 敏感
    // Qt::CaseInsensitive 不敏感
    // 判断是否以指定字符串开始
    qDebug() << str7.startsWith("HELLO", Qt::CaseInsensitive); // true
    // 判断是否以指定字符串结束
    qDebug() << str7.endsWith("world", Qt::CaseSensitive); // true
    // 判断指定字符串是否出现
    qDebug() << str7.contains("HELLO", Qt::CaseInsensitive); // true

    // 重载 < <= > >= ==
    qDebug() << (str6 == str7); // false 

    // compare
    QString str8 = "HELLO", str9 = "hello";
    qDebug() << QString::compare(str8, str9, Qt::CaseSensitive) // <0
             << QString::compare(str8, str9, Qt::CaseInsensitive); // =0

    // toDouble toFloat toLong toLongLong
    QString str10 = "0x11";
    bool flag;
    int val1 = str10.toInt(&flag, 16);
    qDebug() << flag << val1; // true 17

    QString str11 = "123";
    int val2 = str11.toInt(&flag, 10);
    qDebug() << flag << val2; // true 123

    QString str12 = "011";
    int val3 = str12.toInt(&flag, 8);
    qDebug() << flag << val3; //  true 9

    QString str13 = "111";
    int val4 = str13.toInt(&flag, 2);
    qDebug() << flag << val4; // 7

    QString str14 = "123";
    int val5 = str14.toInt();
    qDebug() << val5;

    QString str15 = "hello";
    std::string stdstr = str15.toStdString();

    // ASCII
    QByteArray utf8str = str15.toUtf8();

    qDebug() << QString().isNull() // true
             << QString().isEmpty() // true
             << QString("").isNull() // false
             << QString("").isEmpty(); // true
}

#endif // QSTRING_CASE_H
```

### QByteArray

```cpp

```

### QList

```cpp
#ifndef QLIST_CASE_H
#define QLIST_CASE_H

#include <QList>
#include <QDebug>
#include <QString>

void QList1() {
    QList<QString> list;
    list.push_back(QString("test"));
    list << "test2" << "test3";
    for (int i = 0; i < list.size(); ++i) {
        // qDebug() << list[i];
        qDebug() << list.at(i);
    }
}

#endif // QLIST_CASE_H
```

### QVector

```cpp
#ifndef QVECTOR_CASE_H
#define QVECTOR_CASE_H

#include <QVector>
#include <QDebug>

void QVector1() {
    // QDebug 子类有 QPolygon QPolygonF QStack

    QVector<int> qvec;
    qvec.push_back(1);
    qvec.emplace_back(2);
    qvec << 3 << 4 << 5;
    qvec.insert(5, 6);
    for (const auto &ele : qvec) {
        qDebug() << ele;
    }
    for (int i = 0; i < qvec.size(); ++i) {
        qDebug() << qvec[i];
        // qDebug() << qvec.at(i); // 只读
    }
    // 只读迭代器
    for (QVectorIterator<int> it(qvec); it.hasNext();) {
        qDebug() << it.next();
    }
    // 读写迭代器
    for (QMutableVectorIterator<int> it(qvec); it.hasNext();) {
        qDebug() << it.next();
    }

    QMutableVectorIterator<int> it(qvec);
    it.toBack();
    for (; it.hasPrevious();) {
        if (it.previous() == 6) {
            it.remove(); // 需要读写迭代器
        }
        qDebug() << it.previous();
    }

    // 只读迭代器
    for (QVector<int>::ConstIterator it = qvec.constBegin(); it != qvec.constEnd(); ++it) {
    // for (QVector<int>::const_iterator it = qvec.cbegin(); it != qvec.cend(); ++it) {
        qDebug() << *it;
    }
    // 读写迭代器
    for (QVector<int>::Iterator it = qvec.begin(); it != qvec.end(); ++it) {
    // for (QVector<int>::iterator it = qvec.begin(); it != qvec.end(); ++it) {
        qDebug() << *it;
    }

    QVector<int> qvec2 {1, 2, 3, 4, 5};
    if (qvec2 == qvec) {
        qDebug() << "is same";
    }

    qDebug() << qvec.empty();

    qvec.clear();
}

#endif // QVECTOR_CASE_H
```

### QMap

```cpp
#ifndef QMAP_CASE_H
#define QMAP_CASE_H

#include <QMap>
#include <QString>
#include <QDebug>

void QMap1() {
    QMap<QString, QString> map;
    // map.insert()
    map.insert("a", "1");
    map.insert("b", "1");

    // read-only iterator
    for (QMapIterator<QString, QString> it(map); it.hasNext();) {
        qDebug() << it.next().key() << it.next().value();
    }

    // read write iterator
    for (QMutableMapIterator<QString, QString> it(map); it.hasNext();) {
        qDebug() << it.next().key() << it.next().value();
    }

    // STL iterator
    for (QMap<QString, QString>::ConstIterator it = map.cbegin(); it != map.cend(); ++it) {
    // for (QMap<QString, QString>::const_iterator it = map.cbeing(); it != map.cned(); ++it) {
        qDebug() << *it;
    }

    for (QMap<QString, QString>::Iterator it = map.begin(); it != map.end(); ++it) {
    // for (QMap<QString, QString>::iterator it = map.begin(), it != map.end(); ++it) {
        qDebug() << *it;
    }

    // iterator
    QMutableMapIterator<QString, QString> it(map);
    // it.findNext(value)
    if (it.findNext("1")) {
        it.setValue("0");
        it.value() = "0";
        qDebug() << it.next().value();
    }

    // STL iterator
    QMap<QString, QString>::iterator it2 = map.find("a");
    // map.find(key)
    if (map.find("a") != map.end()) {
        qDebug() << "exist";
        *it2 = "20";
        it2.value() = "30";
        qDebug() << *it2;
    }

    // map.count(key)
    if (map.count("a")) {
        map["a"] = "0";
    }

    // map.empty()
    qDebug() << map.empty();

    // map.clear()
    map.clear();
}

#endif // QMAP_CASE_H
```

### QHash

```cpp

```

### QVariant

```cpp
#ifndef QVARIANT_CASE_H
#define QVARIANT_CASE_H

#include <QVariant>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QColor>
#include <QStringList>

void QVariant1() {
    QVariant val(123);
    qDebug() << val.toInt();

    QVariant str("hello world");
    qDebug() << str.toString();


    QMap<QString, QVariant> map;
    map["a"] = 1;
    map["b"] = '2';
    map["c"] = "3";
    map["d"] = 1.1;
    map["e"] = 1.1f;
    map["f"] = QColor(0, 0, 0);

    for (QMap<QString, QVariant>::ConstIterator it = map.cbegin(); it != map.cend(); ++it) {
        qDebug() << it.key() << it.value();
    }
    qDebug() << map["a"].toInt();
    qDebug() << map["b"].toChar();
    qDebug() << map["c"].toString();
    qDebug() << map["d"].value<double>();
    qDebug() << map["e"].toFloat();
    qDebug() << map["f"].value<QColor>();

    QStringList str1;
    str1 << "1" << "2" << "3";
    QVariant sv(str1);
    // if (sv.type() == QVariant::StringList) { // deprecated
    if (sv.typeId() == QMetaType::QStringList) {
        qDebug() << "is same";
    }
}

#endif // QVARIANT_CASE_H
```
