### 安装依赖

```sh
paru -S cmake base-devel glfw-x11 mesa pkgconf
```

### 配置 GLAD

https://glad.dav1d.de/

| 选项              | 设置         |
| ----------------- | ------------ |
| Language          | `C/C++`      |
| Specification     | `OpenGL`     |
| API               | `3.3`        |
| Profile           | `Core`       |
| Generate a Loader | 选择         |
| Extensions        | 留空或自定义 |