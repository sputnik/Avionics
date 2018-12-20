import socket
import sys
import os
import traceback
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
   x = i
   y = i + 1
   z = y + 1

   while True:
      by = pack("!h", 6)
      mysend(conn, bytearray(by))
      x *= -2
      y *= -2
      z *= -2
      # if i > max 16 bit in size, reset to lower value
      if (z > (2**15 - 1) or z < -(2**15 - 1)):  # 32767
         start = start + 1
         x = start
         y = x + 1
         z = y + 1
      # endif
      by = bytearray(pack("!h", x))
      by.extend(bytearray(pack("!h", y)))
      by.extend(bytearray(pack("!h", z)))

      print("Sending:", x, y, z, by)
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
      except Exception as e:
         exc_type, exc_value, exc_traceback = sys.exc_info()
         print('***Exception while running: ' + str(e))
         print('type: ' + str(exc_type))
         print('Traceback: ')
         traceback.print_tb(exc_traceback)
         print("Connection closed.")
      # end try

# Closes idle window the application is open in. Comment out to not close the window
# p = Popen("stop.bat", cwd=os.getcwd())
