```sh
# 显示所有磁盘
sudo fdisk -l
```

```sh
Disk /dev/nvme0n1：476.94 GiB，512110190592 字节，1000215216 个扇区
磁盘型号：INTEL SSDPEKNW512G8                     
单元：扇区 / 1 * 512 = 512 字节
扇区大小(逻辑/物理)：512 字节 / 512 字节
I/O 大小(最小/最佳)：512 字节 / 512 字节
磁盘标签类型：gpt
磁盘标识符：3291AD6B-EDAC-45D1-A47D-7C55107F1646

设备                起点       末尾      扇区   大小 类型
/dev/nvme0n1p1      2048     534527    532480   260M EFI 系统
/dev/nvme0n1p2    534528     567295     32768    16M Microsoft 保留
/dev/nvme0n1p3    567296  368505486 367938191 175.4G Microsoft 基本数据
/dev/nvme0n1p4 578224128  997652479 419428352   200G Microsoft 基本数据
/dev/nvme0n1p5 997654528  999804927   2150400     1G Windows 恢复环境
/dev/nvme0n1p6 999804928 1000214527    409600   200M Windows 恢复环境
/dev/nvme0n1p7 368505487  410449919  41944433    20G Linux 文件系统
/dev/nvme0n1p8 410449920  574027775 163577856    78G Linux 文件系统
/dev/nvme0n1p9 574027776  578224127   4196352     2G EFI 系统
```

```sh
# 创建挂载点
mkdir windows_c_disk
mkdir windows_d_disk

# 需挂载的磁盘不能处于已打开状态
sudo mount /dev/nvme0n1p3 windows_c_disk
sudo mount /dev/nvme0n1p4 windows_d_disk
```

编辑 `/etc/fstab` 文件，使挂载持久化

```sh
vim /etc/fstab
```

```sh
# 写入
/dev/nvme0n1p3 /home/xuan/windows_c_disk ntfs defaults 0 0
/dev/nvme0n1p4 /home/xuan/windows_d_disk ntfs defaults 0 0
```

为防止挂载失败导致系统无法启动，需要在重启前进行测试，如果正常挂载则可重启

```sh
# 挂载磁盘
sudo mount -a

# 查看挂载情况
df -h
```
