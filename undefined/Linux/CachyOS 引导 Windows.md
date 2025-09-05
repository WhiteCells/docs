使用 GRUB 2.13

安装 `os-prober` 用于检测 Windows 系统：

```sh
sudo paru -S os-prober
```

编辑 GRUB 配置：

```sh
sudo vim /etc/default/grub
```

修改 `GRUB_DISABLE_OS_PROBER` 为 `false`，以允许 GRUB 使用 `os-prober` 发现 Windows 并加入引导项。

重新生成  GRUB 配置：

```sh
sudo grub-mkconfig -o /boot/grub/grub.cfg
```

执行中看到类似输出，即代表成功：

```sh
Found Windows Boot Manager on /dev/nvme0n1p2@/EFI/Microsoft/Boot/bootmgfw.efi
```

