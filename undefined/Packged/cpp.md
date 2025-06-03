

```sh
# 修改可执行文件的 RPATH，优先加载相对 lib
patchelf --set-rpath '$ORIGIN/../lib' ./bin/voip
```

