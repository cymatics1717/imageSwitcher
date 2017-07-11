import asyncio
import uvloop
import time
import datetime
import json

asyncio.set_event_loop_policy(uvloop.EventLoopPolicy())

async def clientTask(tag, loop):
    cnt = 0
    reader, writer = await asyncio.open_connection('127.0.0.1', 11111, loop=loop)

    while True:
        cnt = (cnt + 1) % 100
        name = '{}-{}'.format(datetime.datetime.now(), cnt)
        data = {
            'url': "http://www.stevenround-birdphotography.com/source/image/puffin-{:02d}.jpg".format(cnt),
            'desc': name
        }
        print('Send: {}\n'.format(data))
        writer.write(json.dumps(data, indent=4).encode())

        data = await reader.read(100)
        print('Received: {}'.format(data.decode()))
        time.sleep(1)
    print('Close the socket')
    writer.close()


message = 'Hello World!'
loop = asyncio.get_event_loop()
loop.run_until_complete(clientTask(message, loop))
loop.close()