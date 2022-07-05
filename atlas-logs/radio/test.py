import zmq
import time

f = open("test.bin",'rb')
zmq_ctx = zmq.Context()
pub_socket = zmq_ctx.socket(zmq.PUB)
pub_socket.bind("tcp://0.0.0.0:1234")
while True:
    try:
        data = [f.read(32)]
        print(data)
        pub_socket.send_multipart(data)
        time.sleep(0.5)
    except Exception as e:
        print(e)
        break


f.close()