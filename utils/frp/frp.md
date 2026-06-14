# FRP

## 下载

```sh
sudo apt update
sudo apt install -y curl tar
export FRP_VERSION=0.68.1

# export ARCH=amd64 # note, 注意架构
case "$(uname -m)" in
  x86_64) ARCH=amd64 ;;
  aarch64|arm64) ARCH=arm64 ;;
  armv7l) ARCH=arm ;;
  *) ARCH=$(uname -m) ;;
esac

echo "$ARCH"

curl -fL -O "https://github.com/fatedier/frp/releases/download/v${FRP_VERSION}/frp_${FRP_VERSION}_linux_${ARCH}.tar.gz"
tar xf frp_${FRP_VERSION}_linux_${ARCH}.tar.gz
```

## token 生成

```sh
openssl rand -base64 32
```

# vps 公网服务端配置

```sh
sudo vim /etc/frp/frps.toml
```

```toml
bindAddr = "0.0.0.0"
bindPort = 7000

auth.method = "token"
auth.token = "随机token"

vhostHTTPPort = 880
vhostHTTPSPort = 8443

allowPorts = [
  { start = 60000, end = 60999 }
]

webServer.addr = "127.0.0.1"
webServer.port = 7500
webServer.user = "admin"
webServer.password = "换成强密码"
```

`allowPorts` 是服务端允许映射端口范围
`webServer` 是面板配置
`vhostHTTPPort` 是客户端 `http` 配置
`vhostHTTPSPort` 是客户端 `https` 配置

### 验证

```sh
sudo frps verify -c /etc/frp/frps.toml
```

### 启动

```sh
sudo frps -c /etc/frp/frps.toml
```

### 创建服务

```bash
sudo tee /etc/systemd/system/frps.service > /dev/null <<'EOF'
[Unit]
Description=frp server
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
ExecStart=/usr/local/bin/frps -c /etc/frp/frps.toml
Restart=on-failure
RestartSec=5s

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload
sudo systemctl enable --now frps
```

记得放行放行端口

# 内网客户端配置

```sh
sudo vim /etc/frp/frpc.toml
```

```toml
serverAddr = "公网IP"
serverPort = 7000

auth.method = "token"
auth.token = "和frps一样的token"

[[proxies]]
name = "web-app"
type = "http"
localIP = "127.0.0.1"
localPort = 8080
customDomains = ["app.example.com"]

[[proxies]]
name = "home-ssh"
type = "tcp"
localIP = "127.0.0.1"
localPort = 22
remotePort = 60022
```

TCP 暴露

```sh
[[proxies]]
name = "web-by-port"
type = "tcp"
localIP = "127.0.0.1"
localPort = 8080
remotePort = 60080
```

## 验证

```sh
sudo frpc verify -c /etc/frp/frpc.toml
```

## 启动

```sh
frpc -c /etc/frp/frpc.toml
```

## 创建服务

```bash
sudo tee /etc/systemd/system/frpc.service > /dev/null <<'EOF'
[Unit]
Description=frp client
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
ExecStart=/usr/local/bin/frpc -c /etc/frp/frpc.toml
Restart=on-failure
RestartSec=5s

[Install]
WantedBy=multi-user.target
EOF

sudo systemctl daemon-reload
sudo systemctl enable --now frpc
```

# 测试

A  example.com  ->  公网IP

curl example.com

ssh -p 60022 <username>@<ip>

日志

journalctl -u frps -f

# 访问 FRP Dashboard

ssh -L 7500:127.0.0.1:7500 <username>@<ip> -p <port>
