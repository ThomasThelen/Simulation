import math
import matplotlib.pyplot as myPlot


def GetAcceleration(adist):
    acceleration = (G*Mearth)/(adist**2.0)
    return acceleration

def GetVelocity(vdist):
    velocity =math.sqrt((G*Mearth)/vdist)
    return velocity

def GetPeriod(pdist):
    period= math.sqrt((4.0*(pdist**3.0)*math.pi**2.0)/(G*Mearth))
    return period

Mearth =5.98e24 # kg
G = 6.67e-11 #Gravitational Constant NM^2/Kg^2
R=  2.0e5 #Average orbit radius -> Distance form Earth + Earth radius in meters
MaxDistance=3.0e5 #m
DistanceDifference=1000#m The amount added to the current

velocity_FDistance=[] # Holds the velocities corresponding to distance increases
acceleration_FDistance = []
period_FDistance = [] # Keeps track of th edifferent periods
DistanceArray =[] # Keeps track of past distances
# Get Velocity, Period, Acceleration with a changing R
while (R<=MaxDistance):
    velocity_FDistance.append(GetVelocity(R))
    acceleration_FDistance.append(GetAcceleration(R))
    period_FDistance.append(GetPeriod(R)/3600.0) # Convert to hours on the fly
    DistanceArray.append(R/1000) # Convert to km on the fly
    print("R :  ", R)
    R+=DistanceDifference


myPlot.plot( DistanceArray,velocity_FDistance, '-')
myPlot.title("Velocity Change as Orbit Altitude Increases")
myPlot.ylabel("Orbit Velocity (m/s)")
myPlot.xlabel("Orbit Distance (km)")
myPlot.show()

myPlot.plot( DistanceArray,acceleration_FDistance, '-')
myPlot.title("Acceleration Change as Orbit Altitude Increases")
myPlot.ylabel("Orbit Acceleration (m/s^2)")
myPlot.xlabel("Orbit Distance (km)")
myPlot.show()

myPlot.plot( DistanceArray,period_FDistance, '-')
myPlot.title("Period Change as Orbit Altitude Increases")
myPlot.ylabel("Orbit Period (hours)")
myPlot.xlabel("Orbit Distance (km)")
myPlot.show()


exit()

#Source
#"Mathematics of Satellite Motion." Physics Classroom. Web. 25 Jan. 2016.
# <http://www.physicsclassroom.com/class/circles/Lesson-4/Mathematics-of-Satellite-Motion>.