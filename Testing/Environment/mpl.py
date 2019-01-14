from struct import pack

# Start of MPL registers
MPL115A2_ADDRESS = b'\x60'
MPL115A2_REGISTER_PRESSURE_MSB = b'\x00'
MPL115A2_REGISTER_PRESSURE_LSB = b'\x01'
MPL115A2_REGISTER_TEMP_MSB = b'\x02'
MPL115A2_REGISTER_TEMP_LSB = b'\x03'
MPL115A2_REGISTER_A0_COEFF_MSB = b'\x04'
MPL115A2_REGISTER_A0_COEFF_LSB = b'\x05'
MPL115A2_REGISTER_B1_COEFF_MSB = b'\x06'
MPL115A2_REGISTER_B1_COEFF_LSB = b'\x07'
MPL115A2_REGISTER_B2_COEFF_MSB = b'\x08'
MPL115A2_REGISTER_B2_COEFF_LSB = b'\x09'
MPL115A2_REGISTER_C12_COEFF_MSB = b'\x0A'
MPL115A2_REGISTER_C12_COEFF_LSB = b'\x0B'
MPL115A2_REGISTER_STARTCONVERSION = b'\x12'


class MPL:
   def __init__(self):
      self.pressure = 0.0
      self.temperature = 0.0
   # end def

   def update_values(self, sim):
      self.pressure = sim.pressure
      self.temperature = sim.temperature
   # end def

   def deviate_pressure(self, val):
      #TODO, placeholder
      return val * 1.05
   # end def

   def deviate_temperature(self, val):
      #TODO, placeholder
      return val * 1.05
   # end def

   def encode_temp(self):
      return round(self.temperature*1000)
   # end def

   def encode_pres(self):
      return round(self.pressure/5)
   # end def

   def receive(self,con):
      data = con.receive(1)
      if data == MPL115A2_REGISTER_PRESSURE_MSB:
         print("MPL: Sending P=",self.pressure,", T=",self.temperature)
         packet = bytearray(pack(">h",self.encode_pres()))
         packet.extend(bytearray(pack(">h",self.encode_temp())))
         con.send(packet)
      else:
         print("MPL: Unknown command received: ",data)
   # end def
# end class
