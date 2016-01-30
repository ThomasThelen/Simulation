#include "stdafx.h"
#include "Header.hpp"



int main()
{
	double dt = 0.10; // Time step
					  // Determine which type of graph is wanted
	int choice;

	SetConsoleTitleA("CSTR Control");
	std::cout << "Which type of graph would you like?" << std::endl;
	std::cout << "    1. Graph in the terminal" << std::endl;
	std::cout << "    2. Gnuplot output" << std::endl;
	std::cin >> choice;
	state_type x = { 0, 38, 38, 38 }; // Initial conditions
	CSTR Reactor1(1.3, 0.35, 2.0, 7.0, 32.5, 70, 7300, 0.05, 0.04, 1.0, 0.5, 7.0, 3.7); // Initialize a CSTR insntance
	GNUplotStartStop(1, choice); // Set graph properties

	integrate_const(runge_kutta4< state_type >(), Reactor1, x, 0.0, 60.0, dt, streaming_observer(std::cout)); //Integrates aCSTR with the stepper (runge kutta) and use streaming_observer as the observer

	GNUplotStartStop(0, 0); // Close the gnuplot pipes
	return 0;
}