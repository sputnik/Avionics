
sea_level_pressure = 101.3e3  # Pa
sea_level_density = 1.225  # kg/m^3


class Simulation:
   def __init__(self, alt=0, pressure=sea_level_pressure, density=sea_level_density):
      self.density = density
      self.pressure = pressure
      self.alt = alt
      self.time = 0
   # end def

   def iterate(self):
      self.time += 0.1
   # end def
# end class
