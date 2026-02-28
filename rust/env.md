### Linux 上安装 rustup

```sh
curl --proto '=https' --tlsv1.2 https://sh.rustup.rs -sSf | sh
```

### Windows 上安装 rustup

#### msvc

安装

#### gnu

安装 [MSYS2](https://www.msys2.org/)

配置环境变量 `PATH` 为 MSYS 的 `mingw64` 的 `bin` 目录。

在 MSYS 中安装 rustup：

```sh
curl https://sh.rustup.rs -sSf | sh
```

按照以下进行配置：

```sh
Current installation options:

   default host triple: x86_64-pc-windows-msvc
     default toolchain: stable (default)
               profile: default
  modify PATH variable: yes

1) Proceed with installation (default)
2) Customize installation
3) Cancel installation
>2 # 输入 2，自定义安装

I'm going to ask you the value of each of these installation options.
You may simply press the Enter key to leave unchanged.

Default host triple? [x86_64-pc-windows-msvc]
x86_64-pc-windows-gnu # 指定 gnu 版本

Default toolchain? (stable/beta/nightly/none) [stable]
stable # stable 稳定

Profile (which tools and data to install)? (minimal/default/complete) [default]
complete # complete 完整

Modify PATH variable? (Y/n)
Y # 修改环境变量

Current installation options:

   default host triple: x86_64-pc-windows-gnu
     default toolchain: stable
               profile: complete
  modify PATH variable: yes

1) Proceed with installation (default)
2) Customize installation
3) Cancel installation
> 1 # 安装
```

### 常用命令

```sh
rustc -V # 
cargo -V # 

rustup update # 更新 rust
rustup self uninstall # 卸载 rust

# 初始化
cargo init
cargo init --lib
# or
cargo new project-name
cd project-name
```

### VSCode 插件

- rust-analyzer
- CodeLLDB（更好的调试，便于查看调试变量内容）
- Even Better TOML（.toml 文件）