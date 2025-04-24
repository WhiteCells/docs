



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

