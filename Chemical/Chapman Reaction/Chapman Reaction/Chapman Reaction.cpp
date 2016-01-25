#include "stdafx.h"
#include "c:/boost/numeric/odeint.hpp"
#include "c:/boost//array.hpp"
#include <vector>

using std::vector;


using namespace boost;
typedef std::vector<double> state_type;




vector<state_type> x_vec;
vector<double> times;
size_t steps;







void Reaction(const state_type& x, state_type & dxdt, double t)
{
	dxdt[0] = 2*k1*iO2-k2*iO*iO2; // Oxygen - d[O]/dt
	dxdt[1] = ; //
}


int main()
{

	const double k1 = 10e-10,
		k2 = 2.0e-33,
		k3 = 10e-3,
		k4 = 10e-15,
		iO = 1.0,
		iO2 = 1.0,
		io3 = 1.0;
    return 0;
}

