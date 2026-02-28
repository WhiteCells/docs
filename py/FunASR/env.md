```sh
cd runtime/websocket

cmake -B build -DCMAKE_BUILD_TYPE=Release \
  -DONNXRUNTIME_DIR=/home/cells/onnxruntime \
  -DFFMPEG_DIR=/home/cells/ffmpeg \
  -DOPENSSL_ROOT_DIR=/usr/include/ \
  -DBLAS_LIBRARIES=/usr/lib/libopenblas.so
```



```sh
./build/bin/funasr-wss-client-2pass \
  --server-ip 127.0.0.1 \
  --port 10095 \
  --is-ssl 0 \
  --record 1

./build/bin/funasr-wss-server-2pass \
  --certfile "" \
  --keyfile ""
```

