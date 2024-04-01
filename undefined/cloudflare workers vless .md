### vless

[cf-wkrs-pages-vless](https://github.com/Misaka-blog/cf-wkrs-pages-vless)

[EDtunnel](https://github.com/3Kmfi6HP/EDtunnel)

cloudflare 创建 Worker，编辑代码，将项目 _worker.js 复制代码至 cloudflare workers 中的 worker.js 修改 `userID` ，使用工具[生成 UUID](https://1024tools.com/uuid) 填写为生成 UUID，worker.js 中 `let proxyIp` 是 中转 ip，作用是中转流量，没有中转 ip 会访问不了由 cloudflare 托管的网站

[CloudFlare 优先 IP](https://stock.hostmonit.com/CloudFlareYes)

CF 优选域名：

```
wz.weishao2023.dk.eu.org
wz.weishao2023.uk.eu.org
www.visa.com
www.wto.org
time.is
csgo.
www.who.int
cdn.anycast.eu.org
time.cloudflare.com
shopify.com
time.is
icook.hk
icook.tw
ip.sb
japan.com
malaysia.com
russia.com
singapore.com
skk.moe
www.visa.com
www.visa.com.sg
www.visa.com.hk
www.visa.com.tw
www.visa.co.jp
www.visakorea.com
www.gco.gov.qa
www.gov.se
www.gov.ua
www.digitalocean.com
www.csgo.com
www.shopify.com
www.whoer.net
www.whatismyip.com
www.ipget.net
www.hugedomains.com
www.udacity.com
www.4chan.org
www.okcupid.com
www.glassdoor.com
www.udemy.com
www.baipiao.eu.org
cdn.anycast.eu.org
cdn-all.xn--b6gac.eu.org
cdn-b100.xn--b6gac.eu.org
xn--b6gac.eu.org
edgetunnel.anycast.eu.org
alejandracaiccedo.com
nc.gocada.co
log.bpminecraft.com
www.boba88slot.com
gur.gov.ua
www.zsu.gov.ua
www.iakeys.com
edtunnel-dgp.pages.dev
www.d-555.com
fbi.gov
www.sean-now.com
download.yunzhongzhuan.com
whatismyipaddress.com
www.ipaddress.my
www.pcmag.com
www.ipchicken.com
www.iplocation.net
iplocation.io
www.who.int
www.wto.org

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

可以通过 cloudflare workers 地址加 UUID https://worker-name.cf-name.workers.dev/uuid，访问生成的协议配置信息，将信息 vless 导入代理工具，修改地址、端口和传输层安全，使用 sing-box 内核



