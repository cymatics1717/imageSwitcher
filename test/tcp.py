import time
import datetime
import json
import socket

address = ('127.0.0.1', 11111)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(address)

cnt = 0
while True:
    cnt = cnt+1
    name = '{}-{}'.format(datetime.datetime.now(), cnt)
    data = {
        'url': "http://www.stevenround-birdphotography.com/"
                "source/image/puffin-{:02d}.jpg".format(cnt%100),
        'desc': name
    }
    msg = json.dumps(data)
    try:
        s.send(msg.encode())
        print("<---{}".format(msg))
        # time.sleep(1)
        data = s.recv(2048).decode()
        print('--->{}'.format(name, data))
    except KeyboardInterrupt:
        print("canceled by the user")
        break
    except Exception as ex:
        print("Exception:", ex.message)
        # break





s.close()
