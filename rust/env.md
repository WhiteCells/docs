### Linux 上安装 rustup

```sh
curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh
```

### Windows 上安装 rustup

Windows 上安装 Rust 需要 C++ 环境



### 更新

```sh
rustup update
```

#### 卸载

```sh
rustup self uninstall
```



### 初始化

```sh
cargo init
cargo init --lib
```

或者

```sh
cargo new project-name
cd project-name
```



### VSCode 插件

- rust-analyzer
- CodeLLDB（更好的调试，便于查看调试变量内容）
- Even Better TOML（.toml 文件）