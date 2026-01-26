```sh
git clone https://huggingface.co/jingyaogong/MiniMind2
paru -S git-lfs
git lfs install
git lfs pull
```

---

```sh
# 查看显卡占用
nvitop # 也可以查看A卡或I卡
nvidia-smi
```

---

google可以访问，但是插件和账号都无法正常访问，尝试切换 DNS

---

clangd 的索引依赖于 Ninja 生成的 compile_commands.json 文件

---

```sh
# conda 环境中配置 pip 全局源
pip config set global.index-url https://mirrors.aliyun.com/pypi/simple/
```

---

