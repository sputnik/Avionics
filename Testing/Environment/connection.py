import socket
# Still have print statements for debugging


class Connection:
   """ A class encapsulating a socket connection"""

   def __init__(self, host, port):
      self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      self.s.bind((host, port))
      print("Bound")
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
