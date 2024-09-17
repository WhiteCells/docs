### Linux

vscode 安装 `clangd` 插件。

创建 `~/.clangd` 文件，添加以下内容：

```yaml
CompileFlags:
  Remove: [-mno-direct-extern-access]
```

修改 `.bashrc` 文件（当前使用的），添加以下内容：

```sh
export CLANG_CONFIG_FILE=~/.clangd
```

创建 `~/.clang-format` 文件，添加以下内容：

```yaml
BasedOnStyle: LLVM                                     # 基于 LLVM 风格
IndentWidth: '4'                                       # 缩进宽度为 4 个空格
ColumnLimit: '0'                                       # 最长多少列换行
AlignAfterOpenBracket: Align                           # 在括号后的内容对齐
AlignConsecutiveMacros: 'true'                         # 连续的宏定义对齐
# AlignConsecutiveAssignments: 'true'                    # 按等号对齐连续的赋值语句
AlignConsecutiveDeclarations: 'true'                   # 连续的声明对齐
AlignTrailingComments: 'true'                          # 尾随注释对齐
AccessModifierOffset: -4                               # 访问控制符缩进 4 格
AllowAllArgumentsOnNextLine: 'false'                   # 不允许所有参数换到下一行
AllowAllConstructorInitializersOnNextLine: 'true'      # 允许所有构造函数初始化器换到下一行
AllowAllParametersOfDeclarationOnNextLine: 'false'     # 不允许函数声明的所有参数换到下一行
AllowShortBlocksOnASingleLine: 'false'                 # 不允许短代码块在同一行
AllowShortCaseLabelsOnASingleLine: 'false'             # 不允许短的 case 标签在同一行
AllowShortFunctionsOnASingleLine: None                 # 不允许短函数在同一行，视上下文而定
AllowShortIfStatementsOnASingleLine: Never             # 不允许短的 if 语句在同一行
AllowShortLambdasOnASingleLine: None                   # 短的 lambda 表达式视情况放在一行
AllowShortLoopsOnASingleLine: 'false'                  # 不允许短的循环在同一行
AlwaysBreakAfterDefinitionReturnType: None             # 函数定义时返回类型后不强制换行
AlwaysBreakAfterReturnType: None                       # 函数声明时返回类型后不强制换行
AlwaysBreakBeforeMultilineStrings: 'false'             # 不在多行字符串前强制换行
AlwaysBreakTemplateDeclarations: 'Yes'                 # 模板声明始终换行
BinPackArguments: 'true'                               # 函数参数尽可能放在一行
BinPackParameters: 'true'                              # 函数声明中的参数尽可能放在一行
BreakConstructorInitializers: AfterColon               # 构造函数初始化列表在冒号后换行
BreakInheritanceList: AfterColon                       # 继承列表在冒号后换行
BreakStringLiterals: 'true'                            # 允许将字符串字面量打断成多行
CompactNamespaces: 'false'                             # 不使用紧凑命名空间
ConstructorInitializerAllOnOneLineOrOnePerLine: 'true' # 构造函数初始化器可以全在一行或每个初始化器一行
ConstructorInitializerIndentWidth: '4'                 # 构造函数初始化器缩进为 4
ContinuationIndentWidth: '4'                           # 换行后的行缩进为 4
Cpp11BracedListStyle: 'true'                           # 使用 C++11 括号风格
DerivePointerAlignment: 'true'                         # 自动推导指针对齐方式，除非显式设置
DisableFormat: 'false'                                 # 不禁用格式化功能
FixNamespaceComments: 'true'                           # 在命名空间结束时自动添加注释
PointerAlignment: Right                                # 指针符号对齐到类型的右侧
SortIncludes: 'false'                                  # 不自动排序 include 语句
Standard: Auto                                         # 自动检测使用的 C++ 标准
MaxEmptyLinesToKeep: 1                                 # 最多的连续空格
```

修改 vscode 的 `setting.json` 文件（可以不用指定路径），添加以下内容：

```json
{
    "[cpp]": {
        "editor.links": false // 关闭头文件下划线
    },
    "C_Cpp.clang_format_style": "file:~/.clang-format",
    "C_Cpp.clang_format_fallbackStyle": "none",
    "[c]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    },
    "editor.inlayHints.enabled": "offUnlessPressed",
    "clangd.arguments": [
        "--header-insertion=never"	// 关闭头文件自动插入
    ],
}
```

