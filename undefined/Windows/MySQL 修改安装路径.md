1. 修改环境变量为新路径
2. 修改注册表 `计算机\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\mysql` 中 `ImagePath` 的数据为新路径
3. 修改 MySQL 配置文件 `my.ini` 中 `basedir` 的值为新路径