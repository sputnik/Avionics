import socket
import sys
import os
from subprocess import Popen

print("Started")

HOST = '127.0.0.1'
PORT = 8090

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
   s.bind((HOST, PORT))
   print("Waiting for connection....")
   s.listen(1)
   print("Enter # to disconnect.")
   conn, addr = s.accept()
   with conn:
      print('Connection established at ip:{}, port:{}'.format(addr[0], PORT))
      print("--" * 5)
      while True:
         data = conn.recv(4)
         if not data:
            print("Connection ended")
            break
         else:
            i = int.from_bytes(data, byteorder='little')
            data = conn.recv(i)
         # end if
         print(data[0], " ", data[1], " ", data[2], " ", data[3],
               " ", int.from_bytes(data, byteorder='little'))
      # end while
   # end with
# end with

# Closes idle window the application is open in. Comment out to not close the window
p = Popen("stop.bat", cwd=os.getcwd())
