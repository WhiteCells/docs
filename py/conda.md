## venv

常用命令：

```sh
deactivate
```



## conda

常用命令：

```sh
conda create --name <env_name> [python=<version>] # 创建环境

conda activate <env_name> # 激活环境

conda deactivate # 停用环境

conda env remove -n <env_name> # 删除环境

conda info --envs # 列出环境

conda config --set auto_activate_base false # 关闭 base 虚拟环境自动激活

conda update conda # 更新 conda

conda update <package_name> # 更新包

conda remove <package_name> # 删除包

conda list # 查看已安装包

conda env export > environment.yml # 导出环境配置文件

conda env create -f environment.yml # 通过配置文件创建环境

conda create -n <new_env> --clone <existing_env> # 克隆环境

conda --version # conda 版本

conda search <package_name> # 搜索包

conda clean --all # 清理缓存s

conda config --remove-key <key_name> # 重置 conda 配置


```

### 配置环境

#### Linux

`.bash` 配置写入：

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

`～/.config/pip/pip.conf` 配置写入：

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