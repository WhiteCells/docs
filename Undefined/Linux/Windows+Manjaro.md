### Window

磁盘中划分出大于 30G（30720MB）的磁盘空间，保证该磁盘状态为**未分配**（划分空闲分区也可以在安装时进行）

下载  [Manjaro iso](https://manjaro.org/download/)

下载 [rufus](https://rufus.ie/zh/) 工具，用于制作启动U盘，选择镜像后，rufus 设置默认即可

> 也可以使用 [ventory](https://www.ventoy.net/cn/download.html)（可以引导多个镜像）

### Bios

bios 关闭 **Secure Boot** 模式，manjaro 不支持 Secure Boot

修改 bios 启动顺序为U盘优先启动

### Manjaro 安装

双系统可以不需要单独的 efi 分区，`/boot/efi` 引导，挂载到 Windows efi，gpt 分区下为文件格式为 FAT32，选择其并设置挂载点，内容保留

| 分区       | 文件类型 | 磁盘空间 | 标注 |
| ---------- | -------- | -------- | ---- |
| /boot      | ext4     | 1G       | boot |
| /home      | ext4     | 10G      |      |
| /linuxswap | ext4     | 2G       |      |
| /boot/efi  |          |          |      |
| /          | ext4     | 剩余空间 | root |

1. **ext4**: Linux中最广泛使用的文件系统，默认情况下被许多Linux发行版采用。
2. **XFS**: 是一个高性能的文件系统，被设计用于高并发的场景，支持大容量存储并且文件恢复速度较快。在有大量数据处理的服务器上尤其受欢迎。在某些数据删除和缩小分区方面，它不如ext4灵活。
3. **Btrfs**: 是一个较新的文件系统，支持高级特性，如子卷、快照、压缩、在线扩展和收缩等。设计目标是提高存储效率和空间利用率。
4. **f2fs (Flash-Friendly File System)**: 是为NAND闪存设备设计的文件系统，如SSDs和eMMC存储设备。它提供了特别优化以提高闪存寿命和性能的特性。

独划分 `/home` 分区的优点在于，当需要升级或重新安装系统时，用户的个人数据得以保留，不会被覆盖。而且能更有效地管理磁盘空间。如果选择不挂载单独的 `/home` 分区，那么用户的数据将会存储在 `/` 根分区中

### 双系统时间问题

双系统中有一个系统时间会出错，在 Linux 执行命令，然后在 Windows 中调整时间即可

```sh
timedatectl set-local-rtc 1 --adjust-system-clock
```

### Manjaro 卸载

> *linux is free only if your time is free*

`/`、`/home`、`/linuxswap` 分区在 Windows 可以通过图形界面的磁盘管理删除卷，但 `boot/efi` 分区必须使用命令行删除

```sh
# 进入磁盘管理
diskpart

# 列出所有磁盘
list disk

# 选择磁盘
# 例如 磁盘 0，select disk 0
select disk [num]

# 列出当前磁盘所有分区
list part

# 选择分区
# 例如 分区 1，select part 1
select part [num]

# 删除当前分区，无法删除 efi 分区
delete part

# 删除 efi 分区
delete part override
```

> 对于启动U盘，只需要将其在 rufus 上引导选项设置为 **非可引导**，然后开始即可恢复

### 修改 grub

修改文件 `/etc/default/grub` 文件修改系统引导设置

取消注释 `GRUB_SAVEDEFAULT='true'` 使得每一次启动使用上一次选择，还需要 `GRUB_DEFAULT` 为 `saved`

更新 grub 设置：

```sh
sudo update-grub
```
