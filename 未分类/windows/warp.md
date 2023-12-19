[warp installation](https://1.1.1.1/)

[key generation](https://replit.com/@WhiteCells/warp-key-generator)

[WireGuard installation](https://www.wireguard.com/install/)

[WireGuard profile generation](https://replit.com/@WhiteCells/wgcf-profile-generator)

[nekoray installation](https://github.com/MatsuriDayo/nekoray/releases)

[warp preferred IP](https://gitlab.com/Misaka-blog/warp-script/-/blob/main/files/warp-yxip/warp-yxip-win.7z)

nekoray 设置：

1. 首选项-基本设置-核心-切换核心为 sing-box
2. 首选项-路由设置-简易路由-预设-绕过局域网和大陆
3. 服务器-手动输入配置

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
    "server": "engage.cloudflareclient.com",
    "server_port": 2408,
    "system_interface": false,
    "tag": "proxy",
    "type": "wireguard"
}
```



