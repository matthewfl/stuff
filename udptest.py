import socket
import struct

sock = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )

sock.bind( ("", 6667) )

sock.sendto( struct.pack('qii',  0x00, 0, 123), ("95.211.88.49", 80) )

while True:
    data, addr = sock.recvfrom(1024)
    print "data", data
