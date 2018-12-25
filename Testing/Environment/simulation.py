from enum import Enum
import random


class State(Enum):
   LAUNCHPAD = 1
   BURNING = 2
   COASTING = 3
   DESCENDING = 4
# end def


sea_pressure = 101.3e3  # Pa
sea_density = 1.225  # kg/m^3
gravity = 9.81  # meters per second squared
time_delta = 0.01  # seconds
cd_brake = 1.28
cd_drag = 0.42
area_rocket = .00872677  # meters squared
area_brake = .002419  # meters squared
start_alt = 1219.2  # meters
goal_height = 9144  # meters
weight_i = 355.858  # newtons
weight_f = 253.549  # newtons
start_thrust = 1800  # newtons
fuel_burn_rate = 9.4730555556  # newtons per second


def density(altitude):  # density from altitude equation
   return sea_density * (1 + (-.0065 * altitude / 287) ** 4.25363734)
# end def


def drag(dense, vel):  # drag equation from density and velocity for rocket
   return .5 * dense * vel * vel * cd_drag * area_rocket
# end def


def brake_drag(dense, vel):  # drag equation from density and velocity for airbrakes
   return .5 * dense * vel * vel * cd_brake * (area_brake + area_rocket)
# end def


class Simulation:
   def __init__(self, alt=start_alt, pres=sea_pressure):
      self.density = density(alt)
      self.pressure = pres
      self.alt = alt
      self.x_vel = 0.0
      self.y_vel = 0.0
      self.z_vel = 0.0
      self.x_acc = 0.0
      self.y_acc = 0.0
      self.z_acc = 0.0
      self.time = 0.0
      self.state = State.LAUNCHPAD
      self.launchpad_time = 4.2 + random.random() * 10.0
      print("Launchpad time = ", self.launchpad_time)
   # end def

   def launchpad(self):
      if self.time > self.launchpad_time:
         self.state = State.BURNING
      # end if
   # end def

   def burning(self):
      print('burning todo')
      self.state = State.COASTING
   # end def

   def coasting(self):
      print('coasting todo')
      self.state = State.DESCENDING
   # end def

   def descending(self):
      print('descending todo')
      self.state = State.LAUNCHPAD
   # end def

   def switch(self, arg):
      return {
          State.LAUNCHPAD: self.launchpad,
          State.BURNING: self.burning,
          State.COASTING: self.coasting,
          State.DESCENDING: self.descending
      }.get(arg, self.launchpad)
   # end def

   def iterate(self):
      self.time += 0.1
      self.switch(self.state)()
   # end def

# end class
