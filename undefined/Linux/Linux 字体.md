### 添加字体

下载需要的 `.ttf` 字体文件，复制字体文件到 Linux 字体目录 `/usr/share/fonts` 中。

```sh
sudo mv xxx.ttf /usr/share/fonts
cd /usr/share/fonts
sudo mkfontscale
sudo mkfontdir
sudo fc-cache -fv

# 查看指定语言的字体是否安装
fc-list :lang=zh
```

### 卸载字体

删除 `.ttf` 字体文件，然后刷新系统字体缓存。

### 修改字体卡顿问题

原因：Linux 中会有大量的 Noto 字体，在选择字体时，加载字体会异常的卡顿。

解决方法：建议将 Noto 字体进行从 `/usr/share/fonts` 移植其他地方进行备份。





