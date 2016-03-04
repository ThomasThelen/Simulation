#include "stdafx.h"
#include <iostream>>
#include "Eigen/Dense"

using namespace Eigen;
using std::cout;
using std::endl;




// Holds the position, velocity, and acceleration vectors. These are different in each coordinate system.
class Particle
{
public:
	Particle() {};
	Vector3d position;
	Vector3d velocity;
	Vector3d acceleration;
};

// Base class for the intertial and non-intertial coordinate systems. Each system has a basis, represented by unit vectors I,J,K
class CoordinateSystem
{
public:
	Vector3d unitI;
	Vector3d unitJ;
	Vector3d unitK;
	Vector3d position;
	Vector3d velocity;
	Vector3d acceleration;
};



// Inertial Coordinate System
class Absolute : public CoordinateSystem
{
public:
	Absolute() {
	}
	Particle *particle = new Particle();
};

//Non intertial system
class Moving : public CoordinateSystem
{
public:

	Vector3d angularVelocity;
	Vector3d angularAcceleration;
	Particle *particle = new Particle();

	void UpdateNonIntertialFrame(Absolute*);


};


// Updates the particle position, velocity, and acceleration vectors 
//To Do: Make this also update inertial frame -> Make CoordinateSystem & Use value before basis replacement
void Moving::UpdateNonIntertialFrame(Absolute *abs)
{
	this->particle->position = abs->particle->position - this->position;
	this->particle->velocity = abs->particle->velocity - this->velocity - this->angularVelocity.cross(this->particle->position);
	this->particle->acceleration = abs->particle->acceleration - this->acceleration - this->angularAcceleration.cross(this->particle->position) - this->angularVelocity.cross(this->angularVelocity.cross(this->particle->position)) - 2 * (this->angularVelocity.cross(this->particle->velocity));

	// Replace the basis with the moving coordinates
	Vector3d temp1, temp2, temp3; // Temp vectors to hold hold vector-scalar products

	temp1 = this->particle->position(0)*abs->unitI;
	temp2 = this->particle->position(1)*abs->unitJ;
	temp3 = this->particle->position(2)*abs->unitK;
	this->particle->velocity = temp1 + temp2 + temp3;

	temp1 = this->particle->velocity(0)*abs->unitI;
	temp2 = this->particle->velocity(1)*abs->unitJ;
	temp3 = this->particle->velocity(2)*abs->unitK;
	this->particle->velocity = temp1+temp2+temp3;

	temp1 = this->particle->acceleration(0)*abs->unitI;
	temp2 = this->particle->acceleration(1)*abs->unitJ;
	temp3 = this->particle->acceleration(2)*abs->unitK;
	this->particle->acceleration = temp1 + temp2 + temp3;

}



int main()
{
	Absolute *FixedCoordinate = new Absolute();
	Moving *MovingSystem = new Moving();
	
	//Define the fixed coordinate unit basis
	FixedCoordinate->unitI = {1.2, 2.1, -0.5};
	FixedCoordinate->unitJ = {2.21, 1.2, 2.1};
	FixedCoordinate->unitK = {0.5, -0.75, 0.32};
	
	//Describe the particle in terms of the fixed coordinate system
	FixedCoordinate->particle->position = 100, 50,75};
	FixedCoordinate->particle->velocity = { 50,75,-80 };
	FixedCoordinate->particle->acceleration = { 1.4,-4.5,5.0 };

	//Define how the coordinates translationally move
	MovingSystem->position = { 50,100,250 };
	MovingSystem->velocity = { -25,50,-5 };
	MovingSystem->acceleration = { -20,20,45 };

	//Define how the coordinates rotate
	MovingSystem->angularVelocity = { 1.0,-0.5,1.5 };
	MovingSystem->angularAcceleration = { -1.0,0.5,-1.4 };
	//Define the coordinate basis
	MovingSystem->unitI = { 0.5,0.75,0.40 };
	MovingSystem->unitJ = { -0.8,0.9,-0.4};
	MovingSystem->unitK = { 1.3,1.0,1.2 };
	MovingSystem->UpdateNonIntertialFrame(FixedCoordinate);

	cout << "Particle Position Relative to Non-Inertial Frame" << endl;
	cout << MovingSystem->particle->position << endl;
	cout << "Particle Velocity Relative to Non-Inertial Frame" << endl;
	cout << MovingSystem->particle->velocity << endl;
	cout << "Particle Acceleration Relative to Non-Inertial Frame" << endl;
	cout << MovingSystem->particle->acceleration << endl;

    return 0;
}

