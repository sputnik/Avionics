from connection import Connection

ip = "127.0.0.1"
port = 8090

con = Connection(ip, port)
print(bytearray(con.receive(2)))
