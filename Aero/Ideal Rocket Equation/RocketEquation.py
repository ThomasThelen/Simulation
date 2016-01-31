import math
import matplotlib.pyplot as plotter

#For now assume a bipropellant with exhaust velocity of 3.5 km/s
exhaust_velocity=2500
def ComputeDeltaV(initial_mass, dry_mass):
    delta_v=exhaust_velocity*math.log(initial_mass/dry_mass)
    return delta_v

## Compute delta_v for a range of dry masses. In the process, calculate other relationships such as the mass ratio
delta_m=10
initial_mass = 100 #kg
initial_dry_mass = 10 #kg
delta_v_array=[]
initial_mass_array=[]
dry_mass_array = []
mass_ratio_array=[]
initial_mass_array.append(initial_mass)
total_velocity= []


while (initial_dry_mass<=100) :
    dry_mass_array.append(initial_dry_mass)
    mass_ratio_array.append((initial_mass/initial_dry_mass))
    delta_v_array.append(ComputeDeltaV(initial_mass, initial_dry_mass))
    initial_dry_mass+=delta_m
    total_velocity.append(delta_v_array[-1]/exhaust_velocity)

dry_mass_array.reverse()

# Plot delta v vs the dry mass
plotter.plot(delta_v_array, dry_mass_array, '-')
plotter.title("Dry Weight Requirements")
plotter.ylabel("Dry Weight Percent")
plotter.xlabel("Delta V")
plotter.show()

# Plot delta v vs the mass ratio
plotter.plot(delta_v_array,mass_ratio_array, '-')
plotter.title("Relationship between the Mass Ratio and Delta V")
plotter.ylabel("Mass Ratio")
plotter.xlabel("Delta V")
plotter.show()
exit()



