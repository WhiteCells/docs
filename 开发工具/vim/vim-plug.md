[vim-plug](https://github.com/junegunn/vim-plug.git)

Unix

```sh
curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
    https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
```

Windows

```powershell
iwr -useb https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim |`
    ni $HOME/vimfiles/autoload/plug.vim -Force
```

`.vimrc` 文件

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

如果哪个 vim 插件不想要了，只要删掉 Vim 配置文件中的 Plug 'xxx/xxx' 那一行就好了。下次Vim启动的时候，那个插件就不会被加载。这样做并不会删掉那个插件的文件。可以通过 :PlugClean 来删除所有的已经不用了的插件的文件。
