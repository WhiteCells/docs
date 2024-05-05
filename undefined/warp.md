[warp installation](https://1.1.1.1/)

[key generation](https://replit.com/@WhiteCells/warp-key-generator)

[WireGuard installation](https://www.wireguard.com/install/)

[WireGuard profile generation](https://replit.com/@WhiteCells/wgcf-profile-generator)

[nekoray installation](https://github.com/MatsuriDayo/nekoray/releases)

[warp preferred IP](https://gitlab.com/Misaka-blog/warp-script/-/blob/main/files/warp-yxip/warp-yxip-win.7z)

nekoray 设置：

1. 首选项-基本设置-核心-切换核心为 sing-box
2. 首选项-路由设置-简易路由-预设-绕过局域网和大陆
3. 服务器-手动输入配置-类型（sing-box 出站），粘贴以下 json

```json
{
    "interface_name": "WARP",
    "local_address": [
        "172.16.0.2/32",
        "2606:4700:110:8f0a:fcdb:db2f:3b3:4d49/128"
    ],
    "mtu": 1408,
    "peer_public_key": "bmXOC+F1FxEMF9dyiK2H5/1SUtzH0JuVo51h2wPfgyo=",
    "private_key": "GAl2z55U2UzNU5FG+LW3kowK+BA/WGMi1dWYwx20pWk=",
    "server": "engage.cloudflareclient.com", // 切换为优选 ip
    "server_port": 2408, // 切换为优选 ip 端口
    "system_interface": false,
    "tag": "proxy",
    "type": "wireguard"
}
```

延迟测速 URL `https://gstatic.com/generate_204`

[cf-wkrs-pages-vless](https://github.com/Misaka-blog/cf-wkrs-pages-vless)

[EDtunnel](https://github.com/3Kmfi6HP/EDtunnel)

cloudflare 创建 Worker，编辑代码，将项目 _worker.js 复制代码至 cloudflare workers 中的 worker.js 修改 `userID` ，使用工具生成 UUID填写为生成 UUID，worker.js 中 `let proxyIp` 是 中转 ip，作用是中转流量，没有中转 ip 会访问不了由 cloudflare 托管的网站

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

