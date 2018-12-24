from connection import Connection
import time
from struct import unpack
from util import *
from simulation import *
import subprocess
import os
import sys
import traceback

manual = False

if len(sys.argv) > 1:
   if 'auto' not in sys.argv:
      manual = True
   # end if
else:
   if(Yes_No_Question("Run exe manually?")):
      manual = True
   # end if
# end if
ip = '127.0.0.1'
port = 8090

rerun = True
while rerun:
   print('Starting connection.')
   with Connection(ip, port, 4) as con:
      try:
         if not manual:
            os.startfile(r'cpp.bat')
         # end if
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
      except Exception as e:
         print("Client connection timed out.")
      # end try
   # end with
   rerun = Yes_No_Question("Rerun test?")
# end while
print("Ending testing")
