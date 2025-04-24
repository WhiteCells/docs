systemd 服务单元文件是用来描述启动和管理服务的配置文件，通常位于 `/etc/systemd/system` 或 `/usr/lib/systemd/system` 目录下，以 `.service` 为后缀

基本的 systemd 服务单元文件包含三个部分：

**[Unit]** 部分：提供服务的描述、依赖和启动顺序

```ini
[Unit]
# 该服务的文字描述
Description=
# 该服务的文档连接或路径
Documentation=
# 该服务的强依赖，依赖没有启动，该服务不会启动
Requires=
# 该服务的弱依赖，即使依赖没有启动，该服务仍然尝试启动
Wants=
# 控制启动顺序，该服务应在指定的服务之后启动
After=
# 控制启动顺序，该服务应在指定的服务之前启动
Before=
# 类似 Requires，如果绑定的服务停止，该服务也会停止
BindsTo=
# 如果引用的单元停止或重启，该服务也相应地停止或重启
PartOf=
# 指定与该服务冲突的服务，当该服务启动时，其冲突服务会停止
Conflicts=
```

**[Service]** 部分：定义服务的行为

```ini
[Service]
# 该服务的启动类型，常见类型：
# simple: 默认值，执行 ExecStart 制定的命令，该命令持续执行
# forking: 适用于传统的守护进程，即启动时创建子进程的服务
# oneshot: 适用于一次性服务，执行完 ExecStart 后服务停止
# dbus: 当服务通过 D-Bus 注册自己时，认为服务启动成功
# notify: 服务启动完成后发送一个通知
# idle: 类似 simple，但是等待所有其他任务完成后才启动服务
Type=
# 指定启动服务时制定的命令
ExecStart=
# 指定 ExecStart 执行之前的命令
ExecStartPre=
# 指定 ExecStart 执行之后的命令
ExecStartPost=
# 指定服务收到重载指令时执行的命令
ExecReload=
# 指定停止服务时执行的命令
ExecStop=
# 定义服务退出时的重启策略，常见策略：
# no: 不自动重启
# on-success: 仅在服务正常退出时重启
# on-failure: 在服务异常退出时重启
# on-abnormal: 在服务异常退出或信号终止时重启
# on-watchdog: 在服务没有响应看门狗时重启
# always: 都要重启
Restart=
# 重启之间等待的时间
RestartSec=
# 指定服务启动的超时时间
TimeoutStartSec=
# 指定服务停止的超时时间
TimeoutStopSec=
# 设置环境变量
Environment=
```

**[Install]** 部分：定义了如何安装服务，即如何使服务在系统启动时自动启动

```ini
[Install]
# 指定服务安装后被哪个目标所包含
# multi-user.target: 多用户运行级别
WantedBy=
# 类似 WanteBy，创建一个更强的依赖关系
RequiredBy=
# 为服务创建别名
Alias=
```

创建 systemd 服务文件

```sh
sudo vim /etc/systemd/system/xxx.service
```

写入：

```ini
[Unit]
Description=

[Service]
Type=oneshot
ExecStart=

[Install]
WantedBy=
```

重新加载 systemd 管理器配置：

```sh
sudo systemctl daemon-reload
```

开机自启创建的服务：

```sh
sudo systemctl enable xxx.service
```

启动脚本中如果有 `nohup` 的话需要指定存储 pid 的文件，否则不要 `nohup`。

```sh
# 查询服务启动时的详细日志输出
journalctl -u <xxx>.service
```

