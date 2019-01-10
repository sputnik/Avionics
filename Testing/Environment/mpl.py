# Start of MPL registers
MPL115A2_ADDRESS = 0x60
MPL115A2_REGISTER_PRESSURE_MSB = 0x00
MPL115A2_REGISTER_PRESSURE_LSB = 0x01
MPL115A2_REGISTER_TEMP_MSB = 0x02
MPL115A2_REGISTER_TEMP_LSB = 0x03
MPL115A2_REGISTER_A0_COEFF_MSB = 0x04
MPL115A2_REGISTER_A0_COEFF_LSB = 0x05
MPL115A2_REGISTER_B1_COEFF_MSB = 0x06
MPL115A2_REGISTER_B1_COEFF_LSB = 0x07
MPL115A2_REGISTER_B2_COEFF_MSB = 0x08
MPL115A2_REGISTER_B2_COEFF_LSB = 0x09
MPL115A2_REGISTER_C12_COEFF_MSB = 0x0A
MPL115A2_REGISTER_C12_COEFF_LSB = 0x0B
MPL115A2_REGISTER_STARTCONVERSION = 0x12


class MPL:
   def __init__(self):
      self.pressure = 0.0
      self.temperature = 0.0
      print('Init todo')
   #end def

   def set_pressure_temp(self,pressure,temperature):
      self.pressure = pressure
      self.temperature = temperature 

   def receive(self, arg):
      print('receive todo ')
   #end def
#end class
