### 编译 C/C++

```sh
# 输入的运行程序名
cmd /c g++ -o "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" "$(FULL_CURRENT_PATH)" && "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" & PAUSE
```