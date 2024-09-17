**HTTP** 报文头通常由**请求头**和**响应头**两部分组成。

### HTTP Request Headers

HTTP 请求头包含的字段：

- Request-line：格式为 `METHOD PATH HTTP-VERSION`
  - `:method` 请求方法（如 `GET`、`POST` 等）
  - `:path` 请求资源路径（如 `/index.html` 等）
  - `HTTP 版本（如 `HTTP/1.1`）
- Host: 指定被请求资源的主机名或  IP 地址和端口号
- Accept：指定客户端能够接收的媒体类型列表，用 `,` 分隔，如：`text/plain, text/html`
- User-Agent: 包含客户端的详细信息（如名称、版本、操作系统等）
- Cookie: 如果包含该字段，则将该字段信息发送给服务器，多个 cookie 通过 `;` 分隔。
- Connection: 指示是否保持 TCP 连接，以供后续请求复用（例如 keep-alive）

```txt
GET /index.html HTTP/1.1
Host example.com
Accept: text/html, application/xhtml+xml
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/128.0.0.0 Safari/537.36
Cookie: _octo=GH1.1.759214116.1707483329; _device_id=1f9f57c9881f9b54cdaf4e8d8b2fc986; user_session=isVtBn5; session_same_site=isNLFARn5;
Connection: keep-alive
```

> 浏览器终端中 `Network` 中显示 `Raw`

### HTTP Response Headers

HTTP 响应头包含以下字段：

- Status-line: 
  - `HTTP` 版本
  - 状态码
  - 状态信息
- Content-Type: 响应体的 MIME 类型
- Content-length: 响应体的字节数（GET 请求通常没有）
- Set-Cookie: 服务器向服务器发送的 cookie
- Server: 服务器类型和版本号
- Connection: 是否需要长连接

```txt
HTTP/1.1 200 OK
Content-Type: ttext/html; charset=utf-8
Content-Length: 2048
Set-Cookie: _octo=GH1.1.759214116.1707483329
Server: Apache/2.2.30 (Unix) OpenSSL/1.0-e-fips
Connection: keep-alive
```

```cpp

```

