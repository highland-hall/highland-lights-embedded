import struct
import socket
import time

if __name__ == "__main__":
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # wifi config
        # s.connect(('192.168.4.1',8989))
        # data = struct.pack('BBB%dsB%ds' % (14,14) ,0,2,14, b'~~~~~~~~~~~~~~``', 14,b'~~~~~~~~~~~~~~~~')
        # print(data)
        # s.sendall(data)

        s.connect(('10.0.0.6',8989))
        data = struct.pack('<BBBH',0,4,0,1+37+34+37)
        print(data)
        s.sendall(data)
            
        time.sleep(5);
        data = struct.pack('<BBB',0,3,0)
        print(data)
        s.sendall(data)
    
        time.sleep(5)
        data = struct.pack('<BBBHH',0,7,0,1,37)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BBBHH',0,7,0,38,38+33)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BBBHH',0,7,0,38+33+1,38+33+1+37)
        print(data)
        s.sendall(data)
        
        time.sleep(5)
        data = struct.pack('<BBI',0,6,0)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BBI',0,6,1)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BBI',0,6,2)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BB ',0,10)
        print(data)
        s.sendall(data)

    time.sleep(5)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        
        s.connect(('10.0.0.6',8989))
        data = struct.pack('<BBIBBB',0,16,0,127,0,0)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BBIBBB',0,16,1,0,127,0)
        print(data)
        s.sendall(data)

        time.sleep(5)
        data = struct.pack('<BBIBBB',0,16,2,0,0,127)
        print(data)
        s.sendall(data)

