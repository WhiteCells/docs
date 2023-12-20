[wsl official documents](https://learn.microsoft.com/zh-cn/windows/wsl/install)

系统要求：Windows 10 版本 2004 及以上（内部版本 19041 及以上）或 Windows 11  

管理员模式下打开 PowerShell 或 Windows 命令提示符

```sh
wsl --list --online # 查看可安装列表
wsl --install -d Ubuntu # 需要代理，否则很慢
wsl --set-version Ubuntu 2 # wsl2
```



```sh
explorer.exe . # 打开子系统当前路径

cd /mnt/ # 进入本地磁盘挂载
```

WSL2 关闭

```sh
wsl --shutdown # powershell 中执行
```

WSL 删除指定系统

```sh
wsl --unregister [distribution_name]
```

WSL 指定默认启动系统

```sh
wsl --set-default [distribution_name]
```

WSL 优化

linux 默认 shell 是 bash 在 gdb 调试时补全 program 会出现卡顿

安装 zsh（zshell）

```sh
sudo apt install zsh
```

oh-my-shell

```sh
# curl
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# wget
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# fetch
sh -c "$(fetch -o - https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

修改 oh-my-shell 配置

```sh
vim ~/.zshrc
# af-magic
source ~/.zshrc
```

添加 oh-my-shell 插件

```sh
cd ~/.oh-my-zsh/plugins # 内置 plugins

# 在配置中添加
plugins=(
	git
	zsh-autosuggestions
)

# 第三方插件 clone 到 plugins 目录下
```

修改默认 shell

```sh
sudo chsh -s /bin/new-shell username
```

