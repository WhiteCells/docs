 "connect EACCES /var/run/docker.sock" 错误，原因是 `/var/run/docker.sock` 只有 root 和 `docker` 组的用户能访问，将用户加入 `docker` 组：

```sh
sudo groupadd docker
sudo usermod -aG docker $USER
newgrp docker
```





```sh
docker build -t <image_name> .

docker run -d -p 8000:8000 --nane <web_name> <image_name>

docker ps

docker stop <web_name>

docker rm <web_name>

docker rm <image_name>
```



```sh
docker search <image_name>
docker pull <image_name>:<tag>  # 标签默认 latest
docker images                   # 查看本地所有镜像
docker rmi <image_id>           # 删除镜像
docker rmi $(docker images -q)  # 删除所有镜像

docker build -t <image_name>:<tag> <dockfile_path> # 构建镜像
docker build --no--cache -t <image_name>:<tag> <dockerfile_path> # 不使用缓存构建

docker tag <image_id> <repo_name>:<tag>
docker push <repo_name>:<tag>
docker save -o <file_name>.tar <image_name>

```







```sh
# 指定 docker-compose.yml 文件
sudo docker-compose -f xxx.yml up
sudo docker compose -f xxx.yml up
```





docker 设置代理

`sudo vim /etc/docker/daemon.json`：

```json
{
  "proxies": {
    "default": {
      "httpProxy": "http://127.0.0.1:2080",
      "httpsProxy": "http://127.0.0.1:2080",
      "noProxy": "localhost,127.0.0.1"
    }
  }
}
```

或者 `~/.docker/daemon.json`。

使用镜像

```json
{
    "registry-mirrors": ["https://dockerproxy.net"]
}
```



version 需要加，用于适配低版本 docker。



```sh
docker cp <local_path> <container_name>:<container_path>
```



docker 配置代理

```sh
sudo tee /etc/systemd/system/docker.service.d/http-proxy.conf <<EOF
[Service]
Environment="HTTP_PROXY=http://127.0.0.1:2080"
Environment="HTTPS_PROXY=http://127.0.0.1:2080"
Environment="NO_PROXY=localhost,127.0.0.1"
EOF

sudo systemctl daemon-reexec
sudo systemctl daemon-reload
sudo systemctl restart docker
```

