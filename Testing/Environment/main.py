import os
import sys
import traceback
import codecs
import platform
import time
from connection import Connection
from struct import unpack, pack
from util import *
from simulation import *
from bno import BNO
from mpl import MPL

auto = False
ip = '127.0.0.1'
port = 8090
BNO055_ADDRESS_A = b'\x28'
BNO055_ADDRESS_B = b'\x29'
MPL115A2_ADDRESS = b'\x60'
finished_cmd = b'\x01'
time_cmd = b'\x02'
actuate_cmd = b'\x05'
deactuate_cmd = b'\x06'
on_windows = True


def run():
   rerun = True
   while rerun:
      print('Starting test.')
      sim = Simulation()
      with Connection(ip, port, 20) as con:
         try:
            if auto:
               if on_windows:
                  os.startfile(r'run_cpp.bat')
               else:
                  os.system('./run_cpp.sh')
            # end if
            con.connect()
            connected = True
            bno = BNO()
            mpl = MPL()
            last_time = 0
            while connected and sim.iterate():
               if (sim.time - last_time >= 0.099):
                  last_time = sim.time
                  mpl.update_values(sim)
                  bno.update_values(sim)
                  done = False
                  while not done:
                     data = con.receive(1)
                     if not data:
                        print("Client closed connection")
                        connected = False
                        done = True
                     # end if
                     if data == BNO055_ADDRESS_A or data == BNO055_ADDRESS_B:
                        bno.receive(con)
                     elif data == MPL115A2_ADDRESS:
                        mpl.receive(con)
                        print("alt = ",sim.alt, ", vel = ",sim.z_vel)
                     elif data == finished_cmd:
                        done = True
                     elif data == time_cmd:
                        millis = round(sim.time * 1000)
                        packet = bytearray(pack("<L",millis))
                        con.send(packet)
                     elif data == actuate_cmd:
                        sim.actuate()
                        print("Airbrakes actuated")
                     elif data == deactuate_cmd:
                        sim.close_airbrakes()
                        print("Airbrakes closed")
                     else:
                        print("Main: Unknown command received.", bytearray(data))
                     # end if
                  #end while
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
   if platform.system() == 'Linux':
      on_windows = False
   if not auto:
      if(Yes_No_Question("Auto run exe?")):
         auto = True
      # end if
   # end if
   run()
# end if
