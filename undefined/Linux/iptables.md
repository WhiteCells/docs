```sh
iptables -F

iptables -P INPUT DROP
iptables -P OUTPUT ACCEPT
iptables -P FORWARD DROP

iptables -A INPUT -i lo -j ACCEPT

iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT

iptables -A INPUT -p tcp --dport 22 -j ACCEPT

iptables -A INPUT -p tcp --dport 80 -j ACCEPT

iptables -A INPUT -p tcp --dport 443 -j ACCEPT

# 删除端口类型为 REJECT 的 6277 端口
iptables -D INPUT -p tcp --dport 6277 -j REJECT

# 按照需要删除
iptables -L --line-numbers
iptables -D INPUT 14
```
