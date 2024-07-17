### Linux install MySQL Connector/C++

[MySQL Community Downloads Connector/C++](https://dev.mysql.com/downloads/connector/cpp/)

```sh
# 9.0.0 Linux x86, 64 bit
wget https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-9.0.0-linux-glibc2.28-x86-64bit.tar.gz
tar -xzvf mysql-connector-c++-9.0.0-linux-glibc2.28-x86-64bit.tar.gz
sudo cp mysql/include/* /usr/local/include -r
sudo cp mysql/lib64/* /usr/local/lib -r
sudo cp mysql/*.cmake /usr/local/lib
```
