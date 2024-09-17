### UDP

在使用网络模块之前需要在配置文件中添加 `network` 模块。

```cmake
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Network)
```

```pro

```

### UDP Socket

主要的类：`QUdpSocket` 和 `QNetworkDatagram`

`QUdpSocket` 表示 UDP 的 socket。

| API                                     | type   | desc                                       | C API                          |
| --------------------------------------- | ------ | ------------------------------------------ | ------------------------------ |
| bind(const QHostAddress &, quint16)     | method | 绑定地址和端口号                           | bind                           |
| receiveDatagram()                       | method | 返回 QNetworkDatagram，读取一个 UDP 数据包 | recvfrom                       |
| writeDatagram(const QNetworkDatagram &) | method | 发送 UDP 数据包                            | sendto                         |
| readyRead                               | signal | 收到数据并准备就绪后触发                   | （类似 IO 多路复用的通知机制） |

`QNetworkDatagram` 表示 UDP 数据报。

`QNetworkDatagram(const QByteArray &, const QHostAddress &, quint16) ` 构造数据包。

`data()` 获取数据包内部持有的数据，返回 `QByteArray`

`senderAddress()` 获取数据报中包含的对端 IP 地址。

`senderPort()` 获取数据报中中包含的对端的端口号。

> 先连接信号与槽，在绑定端口。

