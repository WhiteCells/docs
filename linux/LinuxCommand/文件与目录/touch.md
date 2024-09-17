### touch

```sh
touch [OPTION]... FILE...

OPTIONS:
    -a: change only the access time
    -c, --no-create: do not create any files
    -d, --date=STRING: parse STRING and use it instead of current time
    -f: (ignored)
    -h, --no-dereference: affect each symbolic link instead of any referenced file
                          (useful only on systems that can change the timestamps of a symlink)
    -m: change only the modification time
    -r. --reference=FILE: use this file's times instead of current time
    -t STAMP: use [[CC]YY]MMDDhhmm[.ss] instead of current time
    --time=WORD: change the specified time: 
                 WORD is access, atime, or use: equivalent to -a
                 WORD is modify or mtime: equvialent to -m
    --help: display this help and exit
    --version: output version information and exit
```

将每一个 `FILE` 的访问时间和修改时间更改为当前时间。

除非提供 `-c` 或 `-h` 选项，否则不存在的 `FILE` 会被创建，其内容为空。

