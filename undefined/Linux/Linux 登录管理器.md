Manjaro Linux 系统中 `/etc/systemd/login.conf` 文件是 systemd 的登陆管理器 systemd-logind 的配置文件。systemd-logind 是一个系统服务，负责管理用户登录

```ini
#NAutoVTs=6
#ReserveVT=6
# 未激活的设置，如果设置为yes，则在用户注销时结束其所有进程。
#KillUserProcesses=no
# 未激活的设置，如果提供用户名列表，只有这些用户的进程会在注销时被杀死。
#KillOnlyUsers=
#KillExcludeUsers=root
#InhibitDelayMaxSec=5
#UserStopDelaySec=10
#HandlePowerKey=poweroff
#HandlePowerKeyLongPress=ignore
#HandleRebootKey=reboot
#HandleRebootKeyLongPress=poweroff
#HandleSuspendKey=suspend
#HandleSuspendKeyLongPress=hibernate
#HandleHibernateKey=hibernate
#HandleHibernateKeyLongPress=ignore
# 合盖操作
#HandleLidSwitch=suspend
# 外接电源合盖操作
#HandleLidSwitchExternalPower=suspend
#HandleLidSwitchDocked=ignore
#PowerKeyIgnoreInhibited=no
#SuspendKeyIgnoreInhibited=no
#HibernateKeyIgnoreInhibited=no
#LidSwitchIgnoreInhibited=yes
#RebootKeyIgnoreInhibited=no
#HoldoffTimeoutSec=30s
#IdleAction=ignore
#IdleActionSec=30min
#RuntimeDirectorySize=10%
#RuntimeDirectoryInodesMax=
#RemoveIPC=yes
#InhibitorsMax=8192
#SessionsMax=8192
#StopIdleSessionSec=infinity
```
