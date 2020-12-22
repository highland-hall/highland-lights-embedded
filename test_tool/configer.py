import struct
import socket

if __name__ == "__main__":
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(('192.168.4.1',8989))
        data = struct.pack('BBB%dsB%ds' % (14,14) ,0,2,14, b'AntennaGarbage', 14,b'foooooo')
        print(data)
        s.sendall(data)
