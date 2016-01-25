



##CSTR Simulator
Course: ECHM 44
Date: April 30, 2015
Author: Thomas Thelen



**Introduction**

 Control systems have been used for over 400 years, playing integral roles in automated systems. With the increased resources on the topic and access to computation, engineers have been able to apply the field to industrial processes.[]

**Experiment**

The temperature of a CSTR housing an exothermic reaction was controlled by implementing a proportional-integral controller. A cooling jacket was used as the heat sink. The controller was used to calculate the temperature at which the cold fluid should be to adequately cool the reactor.

The system was described by thee coupled differential equations describing the product concentration, the reactor and sensor temperatures, and the requested cooling water temperature. The ODIENT library, part of BOOST, was used to solve the system by using the classical Runge-Kutta method.

The velocity form of the basic PI algorithm, shown below, was used for its computational simplicity.

 Without any tuning, the controller gave a divergent oscillatory response centered on the set point. Because this can lead to dangerous consequences, the controller was field tuned. The classical field tuning method was used to determine the process tuning constants. This improved the controller response and decreased the overall error.


 The high process gain caused the system to overestimate the cooling temperature, contributing to the first positive temperature spike, seen in Figure 1. The integral time constant was low, also effecting controller output by giving it tighter control. The oscillations are artifacts from the field tuning method.


![1 The temperature profile of the reactor. It reaches steady state as the concentration .](http://imgur.com/VPHMm1w.jpg "Reactor Temperature vs Time")


        The temperature had the greatest error during the first ten minutes of operation. After, the temperature trend followed that of the cooling water, shown in Figure 2. The temperature had a maximum temperature error of 5℃
 and reached steady state around 35 minutes. The controller also let the temperature exceed the set point which may be unsafe.

![The requested water temperature leveled off as the temperature reached steady state.](http://imgur.com/ltsVuBK.jpg "Requested Water Temperature")


        The water temperature needed for steady state operation was approximately 11℃ . After ten minutes, the requested temperature drops below the freezing point of water, presenting a piping problem. The temperature reached an almost constant value at the same time the temperature leveled off.






Works Cited

http://ieeecss.org/CSM/library/1996/june1996/02-HistoryofAutoCtrl.pdf

http://www.facstaff.bucknell.edu/mastascu/econtrolhtml/Intro/Intro1.html


