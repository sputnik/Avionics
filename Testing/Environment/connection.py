import socket
# Still have print statements for debugging


class Connection:
   """ A class encapsulating a socket connection"""

   def __init__(self, host, port, timeout):
      self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
      self.s.bind((host, port))
      self.s.settimeout(timeout)
   # end def

   def __enter__(self):
      return self
   # end def

   def __exit__(self, exc_type, exc_value, traceback):
      self.s.close()
      print("Socket closed")
   # end def

   def connect(self):
      self.s.listen(1)
      self.conn, self.addr = self.s.accept()
      print("Connected")
   # end def

   def send(self, msg):
      totalsent = 0
      MSGLEN = len(msg)
      while totalsent < MSGLEN:
         sent = self.conn.send(msg[totalsent:])
         if sent == 0:
            raise RuntimeError("socket connection broken")
         # end if
         totalsent = totalsent + sent
      # end while
   # end def

   def receive(self, length):
      data = self.conn.recv(length)
      return data
   # end def

# end class
