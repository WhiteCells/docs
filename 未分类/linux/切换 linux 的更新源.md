Ubuntu / Debian：
- 更新源配置文件：`/etc/apt/sources.list`
- 使用文本编辑器（如 nano 或 vim）打开该文件：
  ```sh
  sudo nano /etc/apt/sources.list
  ```
- 在文件中找到类似 `deb http://archive.ubuntu.com/ubuntu/ focal main` 的行，将其替换为你想要使用的更新源地址。
- 保存并关闭文件。
- 运行以下命令以更新软件包列表：
  ```sh
  sudo apt update
  ```

CentOS / RHEL：
- 更新源配置文件：`/etc/yum.repos.d/CentOS-Base.repo`
- 使用文本编辑器打开该文件：
  ```sh
  sudo nano /etc/yum.repos.d/CentOS-Base.repo
  ```
- 在文件中找到 `[base]`、`[updates]`、`[extras]` 等段落，并将其中的 `baseurl` 地址替换为你想要使用的更新源地址。
- 保存并关闭文件。
- 运行以下命令以清除缓存并更新软件包列表：
  ```sh
  sudo yum clean all
  sudo yum update
  ```

Arch Linux：
- 更新源配置文件：`/etc/pacman.d/mirrorlist`
- 使用文本编辑器打开该文件：
  ```sh
  sudo nano /etc/pacman.d/mirrorlist
  ```
- 在文件开头添加一个井号 `#`，注释掉所有现有的镜像源。
- 在文件中添加你想要使用的更新源地址，可以从 Arch Linux 官方镜像列表中选择合适的源。
- 保存并关闭文件。
- 运行以下命令以同步软件包数据库：
  ```sh
  sudo pacman -Sy
  ```

在修改更新源之前，最好备份原始配置文件，以防出现问题。此外，确保更新源是可靠和稳定的，以确保系统的安全性和稳定性。

开源镜像站

- [1](https://mirror.tuna.tsinghua.edu.cn/help/ubuntu/)
- [2](https://mirrors.ustc.edu.cn/help/ubuntu.html)