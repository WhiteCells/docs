按 F5 都会在终端输出，但是会附加一串信息。例如：

```sh
hello world
[1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-tih6ti0q.cz0" 1>"/tmp/Microsoft-MIEngine-Out-s6ibdwj6.pwh"
```

实际上这些信息是我们发送到 gdb 的命令，以允许终端使用 VS Code。

更确切的说

*"The text you are seeing is the command we need to send to `gdb` to redirect its stdin/stdout/stderr so that we can communicate with it  from the debug adapter. In changing to allow integratedTerminal, we also chose to allow VS Code to handle all the terminal launching for  external console too due to a request by the community to support more  than just `xTerm` and `gnomeTerminal`."*

解决方案是在 launch.json 中添加：

```json
"miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /bin/gdb -q --interpreter=mi"
```