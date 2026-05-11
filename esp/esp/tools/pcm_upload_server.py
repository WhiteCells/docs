#!/usr/bin/env python3
"""
最小 PCM 上传测试服务器。

运行：
  python3 tools/pcm_upload_server.py

ESP32-S3 上传后，会在当前目录生成 upload_*.pcm。
播放方式示例：
  ffplay -f s16le -ar 16000 -ac 1 upload_*.pcm
"""

from http.server import BaseHTTPRequestHandler, HTTPServer
from pathlib import Path
from time import strftime


class Handler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path != "/upload":
            self.send_response(404)
            self.end_headers()
            self.wfile.write(b"not found\n")
            return

        length = int(self.headers.get("Content-Length", "0"))
        data = self.rfile.read(length)
        filename = Path(f"upload_{strftime('%Y%m%d_%H%M%S')}.pcm")
        filename.write_bytes(data)

        print(f"saved {filename} ({len(data)} bytes)")
        self.send_response(200)
        self.send_header("Content-Type", "text/plain")
        self.end_headers()
        self.wfile.write(f"saved {filename} bytes={len(data)}\n".encode())


if __name__ == "__main__":
    server = HTTPServer(("0.0.0.0", 8000), Handler)
    print("listening on http://0.0.0.0:8000/upload")
    server.serve_forever()

