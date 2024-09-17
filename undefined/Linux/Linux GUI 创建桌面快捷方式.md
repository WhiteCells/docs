使用任意文本编辑器在 `/usr/share/applications` 或 `~/.local/share/applications` 创建 `.desktop` 文件

典型的 `.desktop` 文件：

```desktop
[Desktop Entry]
Encoding=UTF-8
Version=1.0                                     # 程序版本
Name=yEd                                        # 程序名称
GenericName=GUI Port Scanner                    # 程序全称
Exec=java -jar /opt/yed-3.11.1/yed.jar          # 程序执行路径，可带参数
Terminal=false                                  # 是否在终端中运行
Icon=/opt/yed-3.11.1/icons/yicon32.png          # 图标路径
Type=Application                                # 快捷方式类型
Categories=Application                          # 菜单类别
Comment[en_US]=yEd Graph Editor                 # 工具提示
URL                                             # Type 为 Link 时访问 URL
```

AppImage 添加桌面快捷方式

添加 `.AppImage` 文件可执行权限：

```sh
sudo chmod +x xxx.AppImage
```

提取 `.AppImage` 文件的 `.desktop` 文件及 `icon`：

```sh
./xxx.AppImage --appimage-extract
```

将 `.desktop` 文件移动到`~/.local/share/applications`：

```sh
mv ./squashfs-root/usr/share/applications/xxx.desktop ~/.local/share/applications
```

将 `icon` 文件移动到 `~/AppImage/icon`（自定义）：

```sh
mv ./squashfs-root/usr/share/icons/hicolor/64x64/apps/xxx.png ~/AppImage/icon
```

将 AppImage 文件移动到 `~/AppImage`（自定义，移动到 `~/local/bin` 可以用命令行启动程序，但为了便于管理，移动到自定义路径）：

```sh
mv ./xxx.AppImage ~/AppImage
```

可以删除 `squashfs-root` 文件夹：

```sh
rm -rf ./squashfs-root
```

编辑 `.desktop` 文件：

```sh
vim ~/.local/share/applications/xxx.desktop
```

修改 `Exec` 为 AppImage 文件绝对路径，`Icon` 为 icon 文件绝对路径。

更新桌面文件数据库：

```sh
update-desktop-database ~/.local/share/applications
```

