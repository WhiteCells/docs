查看当前系统支持的调节器：

```sh
cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors
```

**performance**：将 CPU 频率设置为最大值，以获得最佳性能，不根据 CPU 负载来调整频率

**powersave**：将 CPU 频率设置为最低值，以节省能源

**ondemand**：根据 CPU 的当前负载动态调整频率，当 CPU 负载增加时，它会提高频率，而当 CPU 负载减少时，它会降低频率

**conservative**：类似于 ondemand，但是它在调整频率时更加保守，会慢慢地增加频率，而在降低频率时则会更快

**userspace**：允许用户或者某些应用程序来设置 CPU 的频率。需要用户知道如何根据需要来手动或通过脚本调整频率

**schedutil**：较新的调节器，使用 Linux 内核的调度器信息来决定最合适的 CPU 频率，试图在性能和能源效率之间取得平衡

查看当前 CPU 调节器：

```sh
cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

默认为 `powersave` 调整为 `performance`

```sh
sudo echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor
```

也可以使用 `cpupower` 工具调整 CPU 频率调节器：

```sh
yay -S cpupower
```

查看当前调节器信息：

```sh
cpupower frequency-info
# analyzing CPU 1:
#   driver: intel_pstate
#   CPUs which run at the same hardware frequency: 1
#   CPUs which need to have their frequency coordinated by software: 1
#   maximum transition latency:  Cannot determine or is not supported.

#   硬件
#   hardware limits: 400 MHz - 4.20 GHz

#   可用调节器
#   available cpufreq governors: performance powersave

#   当前策略
#   current policy: frequency should be within 4.00 GHz and 4.20 GHz.
#                   The governor "performance" may decide which speed to use
#                   within this range.
#   current CPU frequency: Unable to call hardware

#   当前 CPU 频率
#   current CPU frequency: 401 MHz (asserted by call to kernel)
#   boost state support:
#     Supported: yes
#     Active: yes
```

设置调节器：

```sh
sudo cpupower frequency-set --governor performance
```

配置服务

```sh
sudo vim /etc/default/cpupower
```

开启配置自启动

```sh
sudo systemctl enable cpupower.service
```

