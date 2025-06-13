### firewall

```sh
sudo systemctl start firewall
sudo systemctl stop firewall
sudo systemctl restart firewall
sudo systemctl status firewall
```



```sh
sudo netstat -tuln | grep 8080
sudo ss -tuln | grep 8080

sudo firewall-cmd --permanent --add-port=8080/tcp
sudo firewall-cmd --reload
sudo firewall-cmd --list-ports
```



```sh
# 临时开放 8080 端口（tcp）
sudo iptables -A INPUT -p tcp --dport 8080 -j ACCEPT

# 保存规则
sudo service iptables save
# 或
sudo iptables-save > /etc/iptables/rules.v4
```



```sh
# 启用 ufw（如未启用）
sudo ufw enable

# 允许端口 8080
sudo ufw allow 8080/tcp

# 查看规则
sudo ufw status
```



```sh
# 启用 ufw（如未启用）
sudo ufw enable

# 允许端口 8080
sudo ufw allow 8080/tcp

# 查看规则
sudo ufw status
```
