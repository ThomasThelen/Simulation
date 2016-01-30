#include "stdafx.h"
#include "CSTRRxn.hpp"



int main()
{

	double Ma = 0.33; //The initial condition
	MassBalance mBalance(1.3, 0.35, 2.0, 7.0, 0.05, 0.04); //Initialize a mass balance differential equation
	fprintf(pipe, "set term win\n");
	fprintf(pipe, "plot '-' with lines\n");
	integrate_adaptive(make_controlled(1E-12, 1E-12, stepper_type()), mBalance, Ma, 1.0, 80.0, 1.0, parse_data); //Utilizes a runge kutta method with maximum error of 0.1.
	_pclose(pipe);
	system("pause");
	return 0;
}