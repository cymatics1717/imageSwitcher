import time
import datetime
import nnpy
import json

url = 'tcp://127.0.0.1:11111'
sock = nnpy.Socket(nnpy.AF_SP, nnpy.PAIR)
sock.connect(url)

cnt = 0
while True:
    cnt = (cnt+1) % 100
    name = '{}-{}'.format(datetime.datetime.now(), cnt)
    data = {
        'url': "http://www.stevenround-birdphotography.com/source/image/puffin-{:02d}.jpg".format(cnt),
        'desc': name
    }
    sock.send(json.dumps(data, indent=4))
    time.sleep(1)
    msg = sock.recv()
    print('[{}] received {}'.format(name, msg))
