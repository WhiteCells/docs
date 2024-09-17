### c_cpp_properties.json

配置 cpp 版本，Intellisense 代码提示，编译器路径

```json
// Windows
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${default}"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64",
            "compilerPath": "D:/mingw64/bin/g++.exe",
            "cStandard": "c17"
        }
    ],
    "version": 4
}
```

```json
// Linux
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cppStandard": "gnu++17",
            "intelliSenseMode": "linux-gcc-x64",
            "cStandard": "gnu17"
        }
    ],
    "version": 4
}
```

`includePath` 参数 `${workspaceFolder}/**` 会递归的分析工作目录下的所有文件。

### launch.json

F5 进行调试程序时，会在 `launch.json` 搜索对应的配置

```json
{
    "configurations": [
        {
            // 状态栏显示
            "name": "g++.exe",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}\\output.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "D:/mingw64/bin",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "D:\\mingw64\\bin\\gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            // 需和 tasks.json 中 label 一致
            "preLaunchTask": "C/C++: g++.exe 生成活动文件"
        }
    ],
    "version": "2.0.0"
}
```

```json
// Linux
{
    "configurations": [
        {
            "name": "C/C++: g++-11",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/a.out",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: g++-11 生成活动文件",
            "miDebuggerPath": "/usr/bin/gdb",
            "miDebuggerArgs": "-q -ex quit; wait() { fg >/dev/null; }; /bin/gdb -q --interpreter=mi"
        }
    ],
    "version": "2.0.0"
}
```



### setting.json

工作区配置

```json
{
    "files.associations": {
        // ...
    },
    "cmake.configureOnOpen": false,
}
```

```json
// Linux
{
    "files.associations": {
       // ...
    }
    "cmake.configureOnOpen": false,
}
```



### tasks.json

```json
// Windows
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe 生成活动文件",
            "command": "D:/mingw64/bin/g++.exe",
            // 编译器执行的命令
            "args": [
                "-fdiagnostics-color=always",
                "-fno-elide-constructors",
                "-std=c++17",
                "-O0",
                "-g",
                "${file}",
                "-o",
                "${workspaceFolder}\\output.exe"
            ],
            "options": {
                "cwd": "D:/mingw64/bin"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```

```json
// Linux
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++-11 生成活动文件",
            "command": "/usr/bin/g++-11",
            "args": [
                "-fdiagnostics-color=always",
                "-std=c++20",
                "-O0",
                "-g",
                "${file}",
                "-o",
                "${workspaceFolder}/a.out",
                "-lpthread",
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "调试器生成的任务。"
        }
    ],
    "version": "2.0.0"
}
```

### Setting JSON

```json
{
    // 字体大小
    "editor.fontSize": 20,
    // 字体
    "editor.fontFamily": "Hack",
    // vcFormat
    "C_Cpp.formatting": "vcFormat",
    "C_Cpp.vcFormat.newLine.beforeOpenBrace.function": "sameLine",
    "C_Cpp.vcFormat.newLine.beforeOpenBrace.lambda": "sameLine",
    "C_Cpp.vcFormat.newLine.beforeOpenBrace.namespace": "sameLine",
    "C_Cpp.vcFormat.newLine.beforeOpenBrace.type": "sameLine",
    "C_Cpp.vcFormat.newLine.beforeElse": false,
    "C_Cpp.vcFormat.newLine.beforeCatch": false,
    "C_Cpp.vcFormat.newLine.beforeOpenBrace.block": "sameLine",
    "C_Cpp.vcFormat.space.aroundAssignmentOperator": "ignore",
    "C_Cpp.vcFormat.space.aroundBinaryOperator": "ignore",
    "C_Cpp.vcFormat.space.aroundTernaryOperator": "ignore",
    "C_Cpp.vcFormat.space.pointerReferenceAlignment": "right",
    "C_Cpp.vcFormat.wrap.preserveBlocks": "allOneLineScopes",
    "C_Cpp.vcFormat.indent.preserveComments": true,
    "C_Cpp.vcFormat.indent.withinParentheses": "alignToParenthesis",
    "C_Cpp.vcFormat.indent.lambdaBracesWhenParameter": false,
    "C_Cpp.vcFormat.indent.caseContentsWhenBlock": true,
    "C_Cpp.vcFormat.indent.caseLabels": true,
    "C_Cpp.vcFormat.space.withinInitializerListBraces": false,
    "C_Cpp.vcFormat.space.beforeInitializerListOpenBrace": true,
    "C_Cpp.inlayHints.parameterNames.suppressWhenArgumentContainsName": false,
    // namespace
    "C_Cpp.vcFormat.indent.namespaceContents": false,
    // 插入不替换右侧
    "[cpp]": {
        // 控制接受补全时是否覆盖单词，开启后会导致 "" 头文件多出 "
        // "editor.suggest.insertMode": "insert"
    },
    // enter 不接受建议
    "editor.acceptSuggestionOnEnter": "off",
    // 关闭编辑器中是通过拖放来移动选中内容
    "editor.dragAndDrop": false,
    // 编辑器失去焦点时保存文件
    "files.autoSave": "onFocusChange",
    // 保存时不格式化
    "editor.formatOnSave": false,
    // 换行格式化
    "editor.formatOnType": true,
    // 单个子目录不简化
    "explorer.compactFolders": false,
    // 终端的字号
    "terminal.integrated.fontSize": 17,
    // 面板位置(调试控制台...)
    "workbench.panel.defaultLocation": "right",
    // 更新
    "extensions.autoCheckUpdates": false,
    "update.mode": "none",
    "update.showReleaseNotes": false,
    // 鼠标悬停提示位于下方
    "editor.hover.above": false,
    // Linux window title
    "window.titleBarStyle": "custom",
    // title
    "window.menuBarVisibility": "toggle",
    "workbench.layoutControl.enabled": false,
    "window.commandCenter": false,
    // 控制在运行预启动任务后遇到错误时
    "debug.onTaskErrors": "abort",
    // 启动时不显示欢迎页面
    "workbench.startupEditor": "none",
    // alt 键滚动加速
    "editor.fastScrollSensitivity": 1,
    "workbench.list.fastScrollSensitivity": 1,
    // 关闭在编辑器顶部的滚动过程中显示嵌套的当前作用域
    "editor.stickyScroll.enabled": false,
    // 关闭拓展自动更新
    "extensions.autoUpdate": false,
    // 非活动工作区文件 CPU 占用
    "C_Cpp.workspaceParsingPriority": "low",
    // 缩略图
    "editor.minimap.enabled": false,
    // 关闭拓展建议
    "extensions.ignoreRecommendations": true,
    // markdown size
    "markdown.preview.fontSize": 19,
    // git 在没有暂存的更改时提交所有更改
    "git.enableSmartCommit": true,
    // git 同步 Git 存储库前不用进行确认
    "git.confirmSync": false,
    // git 控制是应打开工作区父文件夹中的存储库还是打开的文件
    "git.openRepositoryInParentFolders": "never",
    /*****************************************************************/
    /******************* plugin settings configuration ***************/
    /******************* plugin settings configuration ***************/
    /******************* plugin settings configuration ***************/
    /*****************************************************************/
    // material-icon config
    "material-icon-theme.folders.theme": "classic",
    "workbench.iconTheme": "material-icon-theme",
    /******************************************************************/
    // 驼峰翻译
    "varTranslation.baiduSecret": "6143tJPi4ZLyIyWwLfNK",
    "varTranslation.translationEngine": "baidu",
    /******************************************************************/
    // CMake
    "cmake.showOptionsMovedNotification": false,
    // CMake 项目目录打开时自动配置
    "cmake.configureOnOpen": false,
    // CMake 失败，关闭询问调试器进行配置
    "cmake.showConfigureWithDebuggerNotification": false,
    // CMake 头文件
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    // cmake status bar
    "cmake.options.statusBarVisibility": "compact",
    /******************************************************************/
}
```

### Snippets

```cpp
{
    "LeetCode": {
        "prefix": "lc",
        "body": [
            "#include \"../../head-file.h\"",
            "",
            "/*",
            "problme: ",
            "",
            "url: ",
            // "@Author: Eorys",
            // "@Date: $CURRENT_YEAR-$CURRENT_MONTH-$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND",
            // "@Last Modified by: Eorys",
            // "@Last Modified time: $CURRENT_YEAR-$CURRENT_MONTH-$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND",
            // "@Description: ",
            " */",
            "",
            "class Solution {",
            "public:",
            "\t$0",
            "};",
            "",
            "int main() {",
            "\t",
            "\treturn 0;",
            "}",
        ],
        "description": "lc Template"
    },
    "Solution 类": {
        "prefix": "#s",
        "body": [
            "// time complexity: O()",
            "// spatial complexity: O()",
            "class Solution {",
            "public:",
            "\t$0",
            "};",
        ],
        "description": "Solution 类"
    },
    "现在时间": {
        "prefix": "#time",
        "body": "$CURRENT_YEAR-$CURRENT_MONTH-$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND",
        "description": "现在时间"
    },
    "头文件防止重复包含": {
        "prefix": "#ifn",
        "body": [
            "#ifndef _${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_",
            "#define _${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_",
            "",
            "$0",
            "",
            "#endif // _${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_"
        ],
        "description": "头文件防止重复包含"
    },
    "头文件": {
        "prefix": "#head",
        "body": [
            "_${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_",
        ],
        "description": "头文件"
    },
    "Author info": {
        "prefix": "#author",
        "body": [
            "/*",
            " * @Author: Author",
            " * @Date: $CURRENT_YEAR-$CURRENT_MONTH-$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND",
            " * @Last Modified by: Author",
            " * @Last Modified time: $CURRENT_YEAR-$CURRENT_MONTH-$CURRENT_DATE $CURRENT_HOUR:$CURRENT_MINUTE:$CURRENT_SECOND",
            " * @Description: $0",
            "*/",
        ],
        "description": "作者信息"
    },
    "main": {
        "prefix": "main",
        "body": [
            "int main(int argc, char *argv[]) {",
            "\t$0",
            "\treturn 0;",
            "}",
        ],
        "description": "多行注释"
    },
}
```

