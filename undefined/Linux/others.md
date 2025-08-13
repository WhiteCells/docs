



```sh
# 列出所有设备
aplay -l

# 测试播放音频文件到设备
aplay -D hw:2,0 /home/cells/dev/c-project/pj-demo/pa/16k16bit.wav
```



pjproject

```sh
cd pjproject
make distclean
./configure --enable-pjsua --enable-sound --enable-video --disable-ssl --disable-opencore-amr
make dep
make
sudo make install
```



启动 AppImage 时错误：

```
----------------------------------------------------------------------------------------------------
~/dev/app » ./MoeKoe                                                                    cells@white
dlopen(): error loading libfuse.so.2

AppImages require FUSE to run. 
You might still be able to extract the contents of this AppImage 
if you run it with the --appimage-extract option. 
See https://github.com/AppImage/AppImageKit/wiki/FUSE 
for more information
```

解决方法：

```sh
paru -S fuse2
```

