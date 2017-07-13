import time
import datetime
import nnpy
import json


def post_message(server, sleep_time, base):
    # server = 'tcp://127.0.0.1:11111'
    # base = 0
    url = "http://www.stevenround-birdphotography.com/source/image/puffin-"
    sock = nnpy.Socket(nnpy.AF_SP, nnpy.PAIR)
    sock.connect(server)

    while True:
        base = base+1
        name = '{}-{}'.format(datetime.datetime.now(), base)
        data = {
            'desc': name,
            'url': "{}{:02d}.jpg".format(url, base % 100)
        }
        msg = json.dumps(data)
        try:
            sock.send(msg)
            print("<---{}".format(msg))
            time.sleep(sleep_time)
            msg = sock.recv()
            print("--->{}".format(msg.decode()))
        except KeyboardInterrupt:
            print("canceled by keyboard")
            break
        except Exception as ex:
            print("Exception:", ex.message)
            break

if __name__ == '__main__':
    post_message('tcp://127.0.0.1:11111', 0.1, 20)
