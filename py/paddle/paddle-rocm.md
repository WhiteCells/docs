```sh
# 克隆并进入项目
git clone https://gitee.com/whitecells/paddle-pr.git
cd paddle-pr

# 创建虚拟环境
conda create -n <xxx_env> python=<x.x>
# 激活环境
conda activate <xxx_env>
# 安装包
pip install -r python/requirement.txt -i https://pypi.tuna.tsinghua.edu.cn/simple

# 加载动态库
# /opt/rocm/lib/llvm/lib 加入到动态库的搜索路径
export LD_LIBRARY_PATH=/opt/rocm/lib/llvm/lib:$LD_LIBRARY_PATH
# 配置 cmake 查找文件路径
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/opt/rocm/lib/cmake/

# 创建并进入构建目录
mkdir build && cd build

# 构建编译脚本
# 将 <x.x> 换为虚拟环境中的 python 版本
cmake .. \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
-DCMAKE_CXX_FLAGS="-Wno-error -Wno-dev -w" \
-DPY_VERSION=<x.x> \
-DPYTHON_EXECUTABLE=$(which python) \
-DWITH_CUSTOM_DEVICE=OFF \
-DWITH_TESTING=OFF \
-DON_INFER=ON \
-DWITH_DISTRIBUTE=ON \
-DWITH_MKL=ON \
-DWITH_ROCM=ON \
-DWITH_RCCL=ON \
-DWITH_FLASHATTN=OFF

# 编译
make -j$(nproc)
```

