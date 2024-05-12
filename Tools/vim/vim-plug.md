[vim-plug](https://github.com/junegunn/vim-plug.git)

### Unix

```sh
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

### Windows

```powershell
iwr -useb https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim |`
    ni $HOME/vimfiles/autoload/plug.vim -Force
```

### rc 文件

```sh
vim ~/.vimrc
```

```vim
call plug#begin('~/.vim/plugged') " plug 安装路径
Plug 'preservim/nerdtree'
" ... 其他插件 ...
call plug#end()
```

命令行模式执行 `PlugInstall` 命令

`Not an editor command: PlugInstall`

那么说明 vim-plug 没有正确安装

关闭 vim 插件需要在配置文件中删除对应的 Plug 'xxx/xxx' 启动的时该插件就不会被加载。通过 `PlugClean` 来删除所有的已经不用了的插件。
