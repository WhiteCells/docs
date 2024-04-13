### vless

[cf-wkrs-pages-vless](https://github.com/Misaka-blog/cf-wkrs-pages-vless)

[EDtunnel](https://github.com/3Kmfi6HP/EDtunnel)

cloudflare 创建 Worker，编辑代码，将项目 _worker.js 复制代码至 cloudflare workers 中的 worker.js 修改 `userID` ，使用工具[生成 UUID](https://1024tools.com/uuid) 填写为生成 UUID，worker.js 中 `let proxyIp` 是 中转 ip，作用是中转流量，没有中转 ip 会访问不了由 cloudflare 托管的网站

[CloudFlare 优先 IP](https://stock.hostmonit.com/CloudFlareYes)

```
CF https端口：2053，2083，2087，2096，8443，443 
CF http端口：2052，2082，2086，2095，80，8080，8880
```

VLESS 配置：

```ini
地址: 优选地址
端口: http 端口
UUID: 生成的 UUID
传输: ws
传输层安全: 无
Path: /
Host: worker-name.cf-name.workers.dev
```

可以通过 cloudflare workers 地址加 UUID，访问生成的协议配置信息，将信息 vless 导入代理工具，修改地址、端口和传输层安全，使用 sing-box 内核

