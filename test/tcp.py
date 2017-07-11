import time
import datetime
import json
import socket

address = ('127.0.0.1', 11111)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(address)

cnt = 0
while True:
    cnt = (cnt+1) % 100
    name = '{}-{}'.format(datetime.datetime.now(), cnt)
    data = {
        'url': "http://www.stevenround-birdphotography.com/source/image/puffin-{:02d}.jpg".format(cnt),
        'desc': name
    }
    s.send(json.dumps(data, indent=4).encode('utf-8'))
    time.sleep(1)
    data = s.recv(2014).decode('utf-8')
    print('[{}] received {}'.format(name, data))

s.close()
