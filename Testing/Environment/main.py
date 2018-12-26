from connection import Connection
import time
from struct import unpack, pack
from util import *
from simulation import *
import subprocess
import os
import sys
import traceback

auto = False
ip = '127.0.0.1'
port = 8090


def run():
   rerun = True
   while rerun:
      print('Starting test.')
      sim = Simulation()
      with Connection(ip, port, 20) as con:
         try:
            if auto:
               os.startfile(r'run_cpp.bat')
            # end if
            con.connect()
            while True:
               print(sim.time)
               print(sim.state)
               data = con.receive(2)
               if not data:
                  break
               # end if
               i = unpack("<h", data)[0]
               if i == 0:
                  break
               # end if
               print(bytearray(data), " ", i, end=" ")
               msg = bytearray(pack(">h", i))
               print("sending ", msg)
               con.send(msg)
               sim.iterate()
            # end while
         except Exception as e:
            exc_type, exc_value, exc_traceback = sys.exc_info()
            print('***Exception while running: ' + str(e))
            print('type: ' + str(exc_type))
            print('Traceback: ')
            traceback.print_tb(exc_traceback)
            print(e)
         # end try
      # end with
      rerun = Yes_No_Question("Rerun test?")
   # end while
   print("Ending testing")
# end def


if __name__ == '__main__':
   if len(sys.argv) > 1:
      if 'auto' in sys.argv:
         auto = True
      # end if
   # end if
   if not auto:
      if(Yes_No_Question("Auto run exe?")):
         auto = True
      # end if
   # end if
   run()
# end if
