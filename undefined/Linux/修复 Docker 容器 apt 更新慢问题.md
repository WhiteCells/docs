```sh
cat >/etc/docker/daemon.json <<'EOF'                                                                                                      130 ↵ root@instance-20260308-1718
{
  "dns": ["8.8.8.8", "1.1.1.1"]
}
EOF
```