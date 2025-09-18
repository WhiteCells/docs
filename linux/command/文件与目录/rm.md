### rm

```sh
rm [OPTION]... [FILE]...

OPTIONS:
    -f, --force: ignore nonexistent files and arguments, 
                 never prompt
    -i: prompt before every removal
    -I: prompt once before removing more than three files, 
        or when removing recursively; less intrusive than -i,
        while still giving protection against most mistakes
    --interactive[=WHEN]: prompt according to WHEN: never, once (-I),
                          or always (-i); without WHEN, prompt always
    --one-file-system: when removing a hierarchy recursively,
                       skip any directory that is on a file system
                       different from that of the corresponding command
                       line argument
    --no-preserve-root: do not treat '/' specially
    --preserve-root[=all]: do not remove '/'; with 'all', reject any command
                           line argument on a separate device from its parent
    -r, -R, --recursive: remove directories and their contents recursively
    -d, --dir: remove empty directories
    -v, --verbose: explain what is being done
    --help: display this help and exit
    --version: output version information and exit
```

该命令用于删除文件或目录，默认情况下不能删除目录，需要 `-r` 选项才能删除给定的目录及其中内容。

注意：如要删除文件名一个字符为 "-" 的文件（如文件名为 "-R"）（该文件名会与 OPTION 混淆），可使用以下命令进行删除：

```sh
rm -- -R
# or
rm ./-R
```
