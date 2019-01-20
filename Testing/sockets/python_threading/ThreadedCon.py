import socket
import threading
import time
# Still have print statements for debugging


class Connection(threading.Thread):
   """ A class encapsulating a socket connection"""

   def __init__(self, host, port, data):
      threading.Thread.__init__(self)
      self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      self.s.bind((host, port))
      self.data = data
      self.connected = False
      self.send = False
      self.rec = False
      self.len = 0
      self.cont = True
   # end def

   def _connect(self):
      self.s.listen(1)
      self.conn, self.addr = self.s.accept()
      print("Connected")
      self.connected = True
   # end def

   def _send(self, msg):
      totalsent = 0
      MSGLEN = len(msg)
      while totalsent < MSGLEN:
         sent = self.conn.send(msg[totalsent:])
         if sent == 0:
            raise RuntimeError("socket connection broken")
         # end if
         totalsent = totalsent + sent
      # end while
      self.send = False
   # end def

   def _receive(self, length):
      data = self.conn.recv(length)
      self.rec = False
      return data
   # end def

   def send(self, msg):
      self.send = True
      self.data = msg
   # end def

   def receive(self, length):
      self.rec = True
      self.len = length

   def run(self):
      while self.cont:
         if not self.connected:
            self._connect()
         elif self.send:
            self._send(self.data)
         elif self.rec:
            self.data = self._receive(self.len)
         else:
            time.sleep(0.1)
         # end if
      # end while
   # end def
# end class
