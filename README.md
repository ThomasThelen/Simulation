#Chemical
Includes simulations pertaining to chemical phenomena. Simulations include

### Chapman Reaction

Simulates atmospheric ozone chemistry. It uses the ODEINT numerical library to solve the system of equations. Each chemical reaction is described as a differential equation. Because some reactions depend on the concentration of species in other reactions, the system becomes coupled. ODEINT solved the system and subsequent concentration profiles are obtained.

PICTURE HERE

### CSTR Reaction

This simulates a single species reaction in a CSTR. The concentration profile is obtained by solving a mass balance on the specie's concentration. This was done by using the ODEINt numerical library. The concentration profile was then plotted with gnuplot.

PICTURE HERE

### Exothermic Water Cooled Reaction

This was a project for the senior process controls course MSU. The objective was to control the temperature of a CSTR with an exothermic reaction. This was achieved by insulating the reactor in a cooling jacked and controlling the temperature by modeling a feedback control loop. The system was modeled with a coupled system of diferential equations. 

![1 The temperature profile of the reactor. It reaches steady state as the concentration .](http://imgur.com/VPHMm1w.jpg "Reactor Temperature vs Time")


![The requested water temperature leveled off as the temperature reached steady state.](http://imgur.com/ltsVuBK.jpg "Requested Water Temperature")




#Aero

###RocketEquation

This python script explores the role mass plays on a rocket's delta v.
