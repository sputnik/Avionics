from connection import Connection
import time
from struct import unpack

ip = "127.0.0.1"
port = 8090

with Connection(ip, port) as con:
   con.connect()
   while True:
      data = con.receive(2)
      if not data:
         break
      # end if
      i = unpack("<h", data)[0]
      if i == 0:
         break
      # end if
      print(bytearray(data), " ", i)
   # end while
# end with
