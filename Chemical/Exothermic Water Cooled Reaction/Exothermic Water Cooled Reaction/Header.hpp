#pragma once
/*////////////////////////////////////////////////////////*/
/*//                  Pre Compiler                      //*/
/*//  To Ccompile:                                      //*/
/*//   1. Download Boost and extraact to c:/Boost       //*/
/*//   2. Download ODIENT and place it in the           //*/
/*//      appropriate boost directories                 //*/
/*//   3. Open this project and go to solution          //*/
/*//   4/ Ensure the include and library references are //*/
/*//      correct.                                      //*/
/*//   5. Download and install gnuplot.                 //*/
/*//   6. Add the exe file to the system path variable  //*/
/*//      under advanced settings in computer-> system  //*/
/*//      properties->advanced system settings->        //*/
/*//      environment variables                         //*/
/*//  example path ;C:\Program Files (x86)\gnuplot\bin\ //*/
/*//                                                    //*/
/*////////////////////////////////////////////////////////*/
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <c:/boost/numeric/odeint.hpp>

using namespace boost::numeric::odeint;



/*/////////////////////////////////////////////////////////*/
/*//               Global   Definitions                  //*/
/*//                                                     //*/
/*//  First define the type that the state type will     //*/
/*//  be. Also globally define the file streams to the   //*/
/*//  GNUplot interface                                  //*/
/*//                                                     //*/
/*/////////////////////////////////////////////////////////*/

typedef boost::array< double, 4 > state_type;
FILE *pipe = _popen("gnuplot -persist", "w");
FILE *pipe1 = _popen("gnuplot -persist", "w");
FILE *pipe2 = _popen("gnuplot -persist", "w");
FILE *pipe3 = _popen("gnuplot -persist", "w");

/*////////////////////////////////////////////////////////*/
/*//                      ODE System                    //*/
/*//                                                    //*/
/*//  The structure below defines a functor that is     //*/
/*//  passed to the integration stepper. It defines the //*/
/*//  coupled differential system.                      //*/
/*//                                                    //*/
/*////////////////////////////////////////////////////////*/


class CSTR {
	double
		volume,
		rate_constant, // Rate constant of the reaction involving A
		concentration_inlet1, // The concentration of species A in the first inlet
		concentration_inlet2, // The concentration of species A in the second inlet
		flow_inlet1,  // Volumetric flow rate of the flow entering the reactor through the first inlet
		flow_inlet2,  // Volumetric flow rate of the flow entering the reactor through the second inlet
		rhoTemp, // The molar density of 
		heat_capacity, // The heat capacity of
		heat_reaction, // The heat of reaction
		heat_transfer_coefficient, // The heat transfer coefficient of 
		surface_area, // The total surface area of 
		taus, // sensor time constant
		taut; // time constant

public:
	CSTR(double V, double k, double Ca1, double Ca2, double rho, double cp, double hr, double Q1, double Q2, double Taut, double Taus, double h, double SA) : volume(V), rate_constant(k), concentration_inlet1(Ca1), concentration_inlet2(Ca2), rhoTemp(rho), heat_capacity(cp), heat_reaction(hr), flow_inlet1(Q1), flow_inlet2(Q2), taut(Taut), taus(Taus), heat_transfer_coefficient(h), surface_area(SA) {} // When the class is initialized, the constructor is called and initializes the equation variables. 
	double error = 0, error_old, kc = 30.0, tr = 0, controller_output_difference = 0;
	void operator() (const state_type &x, state_type &dxdt, const double t)
	{

		error_old = error;
		error = 38 - x[2];
		controller_output_difference = kc*((error - error_old) + (error / taut));
		tr = tr + controller_output_difference;

		dxdt[0] = ((flow_inlet1*concentration_inlet1) + (flow_inlet2*concentration_inlet2) - ((flow_inlet1 + flow_inlet2)*x[0]) - (rate_constant*volume*x[0])) / volume;
		dxdt[1] = ((30 * (flow_inlet1 + flow_inlet2) - ((flow_inlet1 + flow_inlet2)*x[1])) / volume) + ((rate_constant*x[0] * heat_reaction) / (rhoTemp*heat_capacity)) - (heat_transfer_coefficient*surface_area*(x[1] - x[3])) / (rhoTemp*heat_capacity*volume);
		dxdt[2] = (x[1] - x[2]) / taus;
		dxdt[3] = ((tr - x[3]) / taut);
		//x[0]= Ca
		//x[1]= T out
		//x[2]= Sensor temperature
		//x[3]= Tamb
	}
};





/*/////////////////////////////////////////////////////////*/
/*//           Data Plotting Subroutine                  //*/
/*//  ODEINT allows for a subroutne to be run after each //*/
/*//  integration step. The one below outputs the        //*/
/*//  solution to the screen and pipes the data to       //*/
/*//  GNUplot.                                           //*/
/*/////////////////////////////////////////////////////////*/

struct streaming_observer
{

	std::ostream &m_out;
	streaming_observer(std::ostream &out) : m_out(out) {}

	void operator()(const state_type &x, double t) const
	{
		extern FILE *pipe;
		extern FILE *pipe1;
		extern FILE *pipe2;
		extern FILE *pipe3;

		std::cout << "Time: " << t << std::endl;
		std::cout << "    Mass Fraction A : " << x[0] << std::endl;
		std::cout << "    Temperature : " << x[1] << std::endl;
		std::cout << "    Sensor Temperature : " << x[2] << std::endl;
		std::cout << "    Water Temperature : " << x[3] << std::endl;
		fprintf(pipe, "%f, %f\n", t, x[0]);
		fprintf(pipe1, "%f, %f\n", t, x[1]);

		fprintf(pipe2, "%f, %f\n", t, x[2]);
		fprintf(pipe3, "%f, %f\n", t, x[3]);
	}
};



/*/////////////////////////////////////////////////////////*/
/*//              GNUplot Plots / Shutdown               //*/
/*//  This subroutine sets the terminal for each GNUplot //*/
/*//  session and then styles the graphs. When called at //*/
/*//  the end of main(), the if statement fails to hold  //*/
/*//  and the pipes are subsequently closed              //*/
/*/////////////////////////////////////////////////////////*/

void GNUplotStartStop(int state, int graph_type)
{
	extern FILE *pipe;
	extern FILE *pipe1;
	extern FILE *pipe2;
	extern FILE *pipe3;
	if (state == 1)
	{
		if (graph_type == 2)
		{
			fprintf(pipe, "set term win\n");
			fprintf(pipe1, "set term win\n");
			fprintf(pipe2, "set term win\n");
			fprintf(pipe3, "set term win\n");
		}
		if (graph_type == 1)
		{
			fprintf(pipe, "set term dumb\n");
			fprintf(pipe1, "set term dumb\n");
			fprintf(pipe2, "set term dumb\n");
			fprintf(pipe3, "set term dumb\n");
		}

		// Pipe -Concentration
		fprintf(pipe, "set title 'Concentration vs Time'\n");
		fprintf(pipe, "set xlabel 'time'\n");
		fprintf(pipe, "set ylabel 'Concentration'\n");
		fprintf(pipe, "plot '-' with lines\n");

		// Pipe1 -Temperature
		fprintf(pipe1, "set title 'Reactor Temperature '\n");
		fprintf(pipe1, "set xlabel 'Time'\n");
		fprintf(pipe1, "set ylabel 'Temperature(C)'\n");
		fprintf(pipe1, "plot '-' with lines\n");


		// Pipe2 -Sensor Equation
		fprintf(pipe2, "set title 'Sensor Temperature'\n");
		fprintf(pipe2, "set xlabel 'time'\n");
		fprintf(pipe2, "set ylabel 'Sensor Temperature'\n");
		fprintf(pipe2, "plot '-' with lines\n");


		// Pipe3 -Water Temperature
		fprintf(pipe3, "set title 'Water Temperature'\n");
		fprintf(pipe3, "set xlabel 'Time'\n");
		fprintf(pipe3, "set ylabel 'Requested Temperature (C)'\n");
		fprintf(pipe3, "plot '-' with lines\n");
	}


	else
	{
		_pclose(pipe);
		_pclose(pipe1);
		_pclose(pipe2);
		_pclose(pipe3);
	}
}


