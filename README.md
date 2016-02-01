#Aero

This folder contains various simulations pertaining to aerodynamic & orbital mechanic simulations.

### Ideal Rocket Equation

This python script explores the role mass plays on a rocket's delta v.

![](https://github.com/ThomasThelen/Simulations/blob/master/Aero/Ideal%20Rocket%20Equation/DryWeight.png)

One way to use this graph is by asking the question:

Given a desired delta_v, what percent of my total mass has to be fuel? 

To answer this, you would go to the delta_v value on the x-axis and move up to the curve, then move left to the y-axis.

For example, if you wanted a delta v of 3000, it would require your dry mass to be about 70% of the rocket's mass. Note that this is specific for the rocket's parameters, seen in the .py file.

![](https://github.com/ThomasThelen/Simulations/blob/master/Aero/Ideal%20Rocket%20Equation/MassRatio.png?raw=true)

This plot shows how . Notice that the delta v gained after a ratio of around 50% becomes linear. 


### Non Ideal Rocket Equation

Includes gravitational drag in the computation of the delta v

### Satellite Motion

This models a satellite orbiting Earth as a function of distance from Earth. It can be used to find various orit parameters including velocity, acceleration, and period.



![](https://github.com/ThomasThelen/Simulations/blob/master/Aero/Satellite%20Motion/figure_1.png?raw=true)

It is clear that as the orbit distance increases, the velociy of the satellite will decrease.

![](https://github.com/ThomasThelen/Simulations/blob/master/Aero/Satellite%20Motion/figure_1-1.png)

The acceleration also decreases as theorbit distance increases.

![](https://github.com/ThomasThelen/Simulations/blob/master/Aero/Satellite%20Motion/figure_1-2.png?raw=true)

Because the acceleration and velocity are decreasing as orbit distance increases, the period will increase. 




#Chemical
Includes simulations pertaining to chemical phenomena. Simulations include

### Chapman Reaction

Simulates atmospheric ozone chemistry. It uses the ODEINT numerical library to solve the system of equations. Each chemical reaction is described as a differential equation. Because some reactions depend on the concentration of species in other reactions, the system becomes coupled. ODEINT solved the system and subsequent concentration profiles are obtained.

PICTURE HERE

### CSTR Reaction

This simulates a single species reaction in a CSTR. The concentration profile is obtained by solving a mass balance on the specie's concentration. This was done by using the ODEINt numerical library. The concentration profile was then plotted with gnuplot.

PICTURE HERE

### Exothermic Water Cooled Reaction

This was a project for the senior process controls course MSU. The objective was to control the temperature of a CSTR with an exothermic reaction. This was achieved by insulating the reactor in a cooling jacked and controlling the temperature by modeling a feedback control loop. The system was modeled with a coupled system of diferential equations. finish talking about each equation

![1 The temperature profile of the reactor. It reaches steady state as the concentration .](http://imgur.com/VPHMm1w.jpg)

The trend is a series of relaxations/compensations from the water controller. Once the temperature rises, the requested water temperature rapidly drops to account for the heat generation. This trend of relaxing/compensating continues until the control system reaches a steady state by damping the response.

![The requested water temperature leveled off as the temperature reached steady state.](http://imgur.com/ltsVuBK.jpg)

The requested water temperature experiened fluctuations until the system was damped out. Its trend is opposite of the temperature profile.

