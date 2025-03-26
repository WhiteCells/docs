

```sh
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash
```



```sh
nvm install 16

nvm use 16

nvm alias default 16
```



npm 设置代理

```sh
npm config set https-proxy http://your-proxy-server:port
npm config set proxy http://your-proxy-server:port
```



问题：

```sh
npm ERR! code ERR_INVALID_URL
npm ERR! Invalid URL

npm ERR! A complete log of this run can be found in:
npm ERR!     /home/cells/.npm/_logs/2025-03-26T03_04_26_060Z-debug-0.log
```

设置代理 `npm config set ...`

