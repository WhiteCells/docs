### 关闭更新

系统环境变量 `POWERSHELL_UPDATECHECK` 设置为 off（没有则新建）

### 允许执行脚本

不允许情况下使用 conda 时会无法加载脚本

```powershell
Set-ExecutionPolicy RemoteSigned -Scope CurrentUser -Force
```

