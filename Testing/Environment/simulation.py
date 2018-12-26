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
cd_brake = 1.28
cd_drag = 0.42
area_rocket = .00872677  # meters squared
area_brake = .002419  # meters squared
start_alt = 1219.2  # meters
goal_height = 9144  # meters
weight_i = 355.858  # newtons
mass_i = weight_i / gravity  # kg
weight_f = 253.549  # newtons
mass_f = weight_f / gravity  # kg
start_thrust = 2100  # newtons
time_delta = 0.01
burn_time = 12.8
fuel_burn_rate = (weight_f - weight_i) / burn_time  # newtons per second


def density(altitude):  # density from altitude equation
   return sea_density * (1 + (-.0065 * altitude / 287) ** 4.25363734)
# end def


def normal_drag(dense, vel):  # drag equation from density and velocity for rocket
   return .5 * dense * vel * vel * cd_drag * area_rocket
# end def


def brake_drag(dense, vel):  # drag equation from density and velocity for airbrakes
   return .5 * dense * vel * vel * cd_brake * (area_brake + area_rocket)
# end def


def temperature(altitude):
   return 15.04 - 0.00649 * altitude
# end def


def pressure(temperature):
   return sea_pressure * (((temperature + 273.1) / (288.08)) ** 5.256)
# end def


class Simulation:
   def __init__(self, alt=start_alt):
      self.alt = alt
      self.weight = weight_i
      self.mass = self.weight / gravity
      self.temperature = temperature(self.alt)
      self.pressure = pressure(self.temperature)
      self.x_vel = 0.0
      self.y_vel = 0.0
      self.z_vel = 0.0
      self.x_acc = 0.0
      self.y_acc = 0.0
      self.z_acc = 0.0
      self.time = 0.0
      self.state = State.LAUNCHPAD
      self.launchpad_time = 4.2 + random.random() * 10.0
      self.burn_end_time = self.launchpad_time + burn_time
      self.actuated = False
      self.max_height = 0
      print("Launchpad time = ", self.launchpad_time,
            ", burn end time = ", self.burn_end_time)
   # end def

   def launchpad(self):
      if self.time > self.launchpad_time:
         self.state = State.BURNING
         print("--" * 15)
         print("Switching to burning")
         print("--" * 15)
      # end if
      return True
   # end def

   def burning(self):
      self.alt += self.z_vel * time_delta
      self.temperature = temperature(self.alt)
      self.pressure = pressure(self.temperature)
      dens = density(self.alt).real
      drag = normal_drag(dens, self.z_vel)
      self.weight -= fuel_burn_rate * time_delta
      self.mass = self.weight / gravity
      thrust = start_thrust
      force = thrust - drag - self.weight
      self.z_acc = (force / self.mass)
      self.z_vel += self.z_acc * time_delta
      if (self.time >= self.burn_end_time):
         print("--" * 15)
         print("Switching to coasting")
         print("--" * 15)
         self.state = State.COASTING
         self.weight = weight_f
         self.mass = self.weight / gravity
      # end if
      return True
   # end def

   def coasting(self):
      self.alt += self.z_vel * time_delta
      self.temperature = temperature(self.alt)
      self.pressure = pressure(self.temperature)
      height = self.alt - start_alt
      if height > self.max_height:
         self.max_height = height
      if ((self.z_vel) < 0.0):
         self.state = State.DESCENDING
         print("--" * 15)
         print("Switching to descending")
         print("--" * 15)
      else:
         dens = density(self.alt).real
         if self.actuated:
            drag = brake_drag(dens, self.z_vel)
         else:
            drag = normal_drag(dens, self.z_vel)
         # end if
         force = -self.weight - drag
         self.z_acc = (force / self.mass)
         self.z_vel += self.z_acc * time_delta
      # end if
      return True
   # end def

   def descending(self):
      self.alt += self.z_vel * time_delta
      self.temperature = temperature(self.alt)
      self.pressure = pressure(self.temperature)
      dens = density(self.alt).real
      drag = normal_drag(dens, self.z_vel)
      force = -self.weight - drag
      self.z_acc = (force / self.mass)
      self.z_vel += self.z_acc * time_delta
      if (self.alt < 0):
         print("--" * 15)
         print("Finished test")
         print("--" * 15)
         return False
      else:
         return True
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
      self.time += time_delta
      return (self.switch(self.state)())
      # end def

   def actuate(self):
      self.actuated = True
   # end def

   def close_airbrakes(self):
      self.actuated = False
   # end def

# end class
