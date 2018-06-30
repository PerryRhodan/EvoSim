#pragma once

#include "IAgent.h"
#include <iostream>

#include <Eigen/Dense>

class SimpleAgent : public IAgent
{
    public:
	SimpleAgent();
	~SimpleAgent();

	// For now just assume one agent gives birth to a new
	// one, and does not need a mating partner
	void receive_parents_traits(SimpleAgent & parent);


	void update(double delta);

	void print();

//////////////////////////////////////////////
	
	// position and motion
	Eigen::Vector3d position;
	Eigen::Vector3d velocity;

	// current size
	double size;

	// current age
	double age;

	// current energy
	double energy;


};
