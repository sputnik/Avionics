import socket
import sys
import os
from subprocess import Popen
import time
from struct import *

print("Started")

HOST = '127.0.0.1'
PORT = 8091


def mysend(conn, msg):
   totalsent = 0
   MSGLEN = len(msg)
   while totalsent < MSGLEN:
      sent = conn.send(msg[totalsent:])
      if sent == 0:
         raise RuntimeError("socket connection broken")
      totalsent = totalsent + sent
   # end while


def send(conn, i, start):
   while True:
      by = pack("!I", 4)
      mysend(conn, bytearray(by))
      i *= 3
      # if i > max 32 bit in size, reset to lower value
      if (i > (2 ** 31 - 1)):
         start = start + 1
         i = start
      # endif
      by = pack("!I", i)
      print("Sending:", i, bytearray(by))
      mysend(conn, by)

      time.sleep(0.5)
   # end while
# end def


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
   s.bind((HOST, PORT))
   print("Waiting for connection....")
   s.listen(5)
   print("Enter # to disconnect.")
   conn, addr = s.accept()
   with conn:
      print('Connection established at ip:{}, port:{}'.format(addr[0], PORT))
      print("--" * 5)
      i = 1
      start = 1
      try:
         send(conn, i, start)
      except:
         print("Connection closed.")
      # end try

# Closes idle window the application is open in. Comment out to not close the window
#p = Popen("stop.bat", cwd=os.getcwd())
