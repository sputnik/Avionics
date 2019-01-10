from connection import Connection
import time
from struct import unpack, pack
from util import *
from simulation import *
import subprocess
import os
import sys
import traceback
import codecs
from bno import BNO
from mpl import MPL
auto = False
ip = '127.0.0.1'
port = 8090
BNO055_ADDRESS_A = b'\x28'
BNO055_ADDRESS_B = b'\x29'
MPL115A2_ADDRESS = b'\x60'

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
            BNO_R = BNO()
            MPL_R = MPL()
            while sim.iterate():
               data = con.receive(1)
               if not data:
                  break
               # end if
               if data == BNO055_ADDRESS_A or data == BNO055_ADDRESS_B:
                  print('BNO')
               elif data == MPL115A2_ADDRESS:
                  print('MPL')
               # end if
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
