vscode 在运行程序时，终端附加一串信息。例如：

```sh
hello world
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-tih6ti0q.cz0" 1>"/tmp/Microsoft-MIEngine-Out-s6ibdwj6.pwh"
```

解决方案是在 launch.json 中添加：

```json
"miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /bin/gdb -q --interpreter=mi"
```