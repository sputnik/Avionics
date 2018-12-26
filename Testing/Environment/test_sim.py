from simulation import *

print('Starting')
sim = Simulation()
i = 0
while (sim.iterate()):
   i += 1
   if (i % 20 == 0):
      print("alt = ", sim.alt, ", vel = ",
            sim.z_vel, ", acc = ", sim.z_acc)
   pass
   #print("t = ", sim.time, ", alt = ", sim.alt)
   # end while
print("max h = ", sim.max_height, ", target height = ", goal_height)
print("time = ", sim.time, ", flight_time = ", sim.time - sim.launchpad_time)
