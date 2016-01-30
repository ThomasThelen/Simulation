/*////////////////////////////////////////////////////////*/
/*//               Global   Definitions                 //*/
/*//                                                    //*/
/*////////////////////////////////////////////////////////*/



#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <c:/Boost/boost/numeric/odeint.hpp>
using namespace std;
using namespace boost::numeric::odeint;
typedef runge_kutta_dopri5< double, double, double, double, vector_space_algebra, default_operations, never_resizer > stepper_type;

FILE *pipe = _popen("gnuplot -persist", "w");


class MassBalance {
	double volume, rate_constant, concentration_inlet1, concentration_inlet2, flow_inlet1, flow_inlet2, flow_outlet; //All variables used in the differential equation.

public:
	MassBalance(double V, double k, double Ca1, double Ca2, double Q1, double Q2) : volume(V), rate_constant(k), concentration_inlet1(Ca1), concentration_inlet2(Ca2), flow_inlet1(Q1), flow_inlet2(Q2) {} // When the class is initialized, the constructor is called and initializes the equation variables. 

	void operator() (const double Ma, double &dMadt, const double t) //When the instance of the class is passed to the integrator, it acts a function; operator() is automatically passed,
	{
		dMadt = ((flow_inlet1*concentration_inlet1) + (flow_inlet2*concentration_inlet2) - ((flow_inlet1 + flow_inlet2)*Ma) - (rate_constant*volume*Ma)) / volume; // Mass balanace differential equation with Ca as the dependant variable.
	}
};

void parse_data(const double &x, const double t)
{
	extern FILE *pipe;
	cout << "time :" << t << " Mass Fraction A :" << x << endl;

	if (pipe == NULL)
	{
		cout << "Error opening GNUplot" << endl;
	}

	fprintf(pipe, "%f, %f\n", t, x);
	fflush(pipe);
}
#pragma once
