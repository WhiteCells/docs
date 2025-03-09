## venv

常用命令：

```sh
deactivate
```



## conda

[Anaconda Archive](https://repo.anaconda.com/archive/)

#### Linux

```sh
# 下载安装脚本
wget https://repo.anaconda.com/archive/Anaconda3-2024.06-1-Linux-x86_64.sh

# 验证安装脚本的 SHA-256 哈希值
<sha256sum> Anaconda3-2023.07-0-Linux-x86_64.sh

# 运行安装脚本
bash Anaconda3-2023.07-0-Linux-x86_64.sh
# 接受许可协议，选择安装目录

# 在修改 shell 配置文件时选择允许

# 配置使用的 shell
conda init zsh

# 删除 conda
rm -rf <conda_path>
conda init --reverse --all
rm -rf ~/.condarc ~/.conda ~/.continum
```

常用命令：

```sh
# 创建环境
conda create --name <env_name> [python=<version>]
conda create -n <env_name> [python=<version>]
# conda create --name pyspark-env python=3.8
# conda create -n web-env python=3.8

# 激活环境
conda activate <env_name>

# 停用环境
conda deactivate

# 删除环境
conda env remove -n <env_name>

# 列出环境
conda info --envs

# 关闭 base 虚拟环境自动激活
conda config --set auto_activate_base false

# 更新 conda
conda update conda

# 更新包
conda update <package_name>

# 删除包
conda remove <package_name>

# 查看已安装包
conda list

# 导出环境配置文件
conda env export > environment.yml

# 通过配置文件创建环境
conda env create -f environment.yml

# 克隆环境
conda create -n <new_env> --clone <existing_env>

# 查看 conda 环境列表
conda env list

# conda 版本
conda --version

# 搜索包
conda search <package_name>

# 清理缓存
conda clean --all

# 重置 conda 配置
conda config --remove-key <key_name>
```

### 配置环境

#### Linux

`.bash` 配置写入（如果不存在该配置）：

```sh
# >>> conda initialize >>>
__conda_setup="$('/usr/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/usr/etc/profile.d/conda.sh" ]; then
        . "/usr/etc/profile.d/conda.sh"
    else
        export PATH="/usr/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<


# or
export PATH="/usr/local/Anaconda/bin:$PATH"
```

`source ~/.bash` 重新加载配置。

## pip

常用命令：

```sh
pip install <package_name> # 安装包

pip install <package1> <package2> # 安装多个包

pip install -r requirements.txt # 根据 requirements.txt 安装依赖

pip install --target=<path> <package_name> # 指定安装路径

pip install --ignore-installed <package_name> # 忽略已安装的包，强制重新安装

pip install <package_name> -i <url> # 指定镜像源

pip search <package_name> # 搜索 PyPI 中的包

pip cache purge # 清理缓存

pip uninstall <package_name> # 卸载包

pip uninstall <package1> <package2> # 卸载多个包

pip uninstall --yes <package_name> # 强制卸载包
```

修改源

`<镜像加速器地址~/.config/pip/pip.conf` 配置写入（没有则创建）：

```sh
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple

[install]
trusted-host = pypi.tuna.tsinghua.edu.cn
```

使用默认源：

```sh
[global]
index-url = https://pypi.org/simple
```