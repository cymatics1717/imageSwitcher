import time
import datetime
import nnpy
import json

url = 'tcp://127.0.0.1:11111'
sock = nnpy.Socket(nnpy.AF_SP, nnpy.PAIR)
sock.connect(url)

cnt = 0
while True:
    cnt = cnt+1
    name = '{}-{}'.format(datetime.datetime.now(), cnt)
    data = {
        'desc': name,
        'url': "http://www.stevenround-birdphotography.com"
        "/source/image/puffin-{:02d}.jpg".format(cnt%100)
    }
    msg = json.dumps(data)
    try:
        sock.send(msg)
        print("<---{}".format(msg))
        time.sleep(1)
        msg = sock.recv()
        print("--->{}".format(msg.decode()))
    except KeyboardInterrupt:
        print("canceled by the user")
        break
    except Exception as ex:
        print("Exception:", ex.message)
        # break
