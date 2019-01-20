from ThreadedCon import Connection
import time
from struct import unpack

ip = "127.0.0.1"
port = 8090
data = ""

con = Connection(ip, port, data)
con.start()


con.receive(2)
print("created")
while(not con.connected):
   time.sleep(0.2)
# end while
while(con.rec):
   time.sleep(0.2)
# end while
unpack("<h", con.data)[0]
print(con.data, unpack("<h", con.data)[0])
time.sleep(5)
print("Done sleeping")
con.cont = False
