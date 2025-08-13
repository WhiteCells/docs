使用包管理工具安装 zsh（zshell）

```sh
# pacman
sudo pacman -S zsh

# yum
sudo yum install zsh

# apt
sudo apt install zsh
```

下载 [oh-my-shell](https://github.com/ohmyzsh/ohmyzsh)

```sh
# curl
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# wget
sh -c "$(wget -O- https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# fetch
sh -c "$(fetch -o - https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
```

下载插件或主题

`~/.oh-my-zsh/plugins` 内置插件，`cd ~/.oh-my-zsh/custom/plugins` 用户插件

`~/.oh-my-zsh/themes` 内置主题，`~/.oh-my-zsh/custom/them# 查看支持 shell
cat /etc/shellses` 用户主题

```sh
# zsh-syntax-highlighting
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ~/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting

# zsh-autosuggestions
git clone https://github.com/zsh-users/zsh-autosuggestions.git ~/.oh-my-zsh/custom/plugins/zsh-autosuggestions

# powerlevel10k
git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k
```

修改 oh-my-shell 配置

```sh
vim ~/.zshrc
```

修改 zsh 配置文件

```sh
# ~/.zshrc

# theme
ZSH_THEME="af-magic"
# ZSH_THEME="powerlevel10k/powerlevel10k"

# plugins
plugins=(
	git
	zsh-autosuggestions
	zsh-syntax-highlighting
)
```

```sh
# 使配置文件生效
source ~/.zshrc
```

```sh
# 查看支持 shell
cat /etc/shells

# 修改默认 shell
sudo chsh -s /bin/zsh username
```

root 用户 zsh 配置文件 `/usr/share/zsh/<*-zsh-config>` 和 `/usr/share/zsh/<*-zsh-prompt>`
