### Ubuntu 出现 E: Failed to fetch

#### 问题

使用 `sudo apt update` 出现以下错误

```sh
$ sudo apt update
Err:1 http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu focal InRelease
  Temporary failure resolving 'ppa.launchpad.net'
Err:2 http://security.ubuntu.com/ubuntu focal-security InRelease
  Temporary failure resolving 'security.ubuntu.com'
Err:3 http://archive.ubuntu.com/ubuntu focal InRelease
  Temporary failure resolving 'archive.ubuntu.com'
Err:4 http://archive.ubuntu.com/ubuntu focal-updates InRelease
  Temporary failure resolving 'archive.ubuntu.com'
Err:5 http://archive.ubuntu.com/ubuntu focal-backports InRelease
  Temporary failure resolving 'archive.ubuntu.com'
Reading package lists... Done
Building dependency tree
Reading state information... Done
13 packages can be upgraded. Run 'apt list --upgradable' to see them.
W: Failed to fetch http://archive.ubuntu.com/ubuntu/dists/focal/InRelease  Temporary failure resolving 'archive.ubuntu.com'
W: Failed to fetch http://archive.ubuntu.com/ubuntu/dists/focal-updates/InRelease  Temporary failure resolving 'archive.ubuntu.com'
W: Failed to fetch http://archive.ubuntu.com/ubuntu/dists/focal-backports/InRelease  Temporary failure resolving 'archive.ubuntu.com'
W: Failed to fetch http://security.ubuntu.com/ubuntu/dists/focal-security/InRelease  Temporary failure resolving 'security.ubuntu.com'
W: Failed to fetch http://ppa.launchpad.net/ubuntu-toolchain-r/test/ubuntu/dists/focal/InRelease  Temporary failure resolving 'ppa.launchpad.net'
W: Some index files failed to download. They have been ignored, or old ones used instead.
```

#### 解决

方法1

```sh
sudo apt-get update
sudo apt-get upgrade
```

方法2

```sh
sudo vim /etc/resolv.conf
```

添加 阿里 DNS

```sh
nameserver 223.5.5.5
nameserver 223.6.6.6
```
