### WebSocket

WebSocket 是一个长连接的协议，包含了解包的过程，当在客户端发起以 `ws` 开头的 HTTP 请求时，如 `ws://127.0.0.1:8080`，就是向 `WebSocket` 服务器发起请求。

`beast` 封装了超时处理，通过 `set_option` 来设置连接的超时时间。

WebSocket 流对象不是线程安全的，当多个线程同时访问该对象，则会产生未定义行为。

对于多线程，可以通过构造 `tcp_stream` 对象时使用 `executor` 来保证线程安全。

使用 `strand` 调用所有完成处理程序的 WebSocket 流对象：

```cpp
stream<boost::beast::tcp_socket> ws(boost::asio::make_strand(ioc));
```

通过 `std::move` 将已存在的 TCP 套接字对象移动到 WebSocket 流对象：

```cpp
stream<boost::beast::tcp_socket> ws(std::move(ioc));
```

通过调用 `WebSocket` 流对象的 `next_layer()` 的函数访问下一层流对象：

```cpp
ws.next_layer().close();
```

通过调用 `get_lowest_layer()` 函数，可以直接获取多层流中的最底层流，而无需逐层调用 `next_layer()`，用于取消所有未完成 I/O，在关闭连接之前取消所有挂起的异步操作。

### SSL

使用 `boost::asio::ssl::stream` 类模板作为流的模板类型，并将 `boost::asio::io_context` 和 `boost::asio::ssl::context` 参数传递给流的构造函数。

```cpp
stream<ssl_stream<tcp_stream>> wss(boost::asio::make_strand(ioc), ctx);
// ctx
```

### 连接

客户端

```cpp
stream<tcp_stream> ws(ioc);
boost::asio::ip::tcp::resolver resolver(ioc);
get_lowest_layer(ws).connect(resolver.resolve("example.com", "ws"));
```

服务器

```cpp
boost::asio::ip::tcp::acceptor acceptor(ioc);
acceptor.bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));

```

