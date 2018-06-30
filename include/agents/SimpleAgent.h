#pragma once

#include "IAgent.h"
#include <iostream>

#include <Eigen/Dense>

class SimpleAgent : public IAgent
{
     // the food values of the areas around the agent
     struct food_in_vision {
	double front;
	double right;
	double left;
	double back;
     
     	food_in_vision() {
	    front = 0.0;
	    right = 0.0;
	    left = 0.0;
	    back = 0.0;
	};
     };


     // the sizes of other agents in the areas around this agent
     struct agent_in_vision {
	double front;
	double right;
	double left;
	double back;

	agent_in_vision() {
	    front = 0.0;
	    right = 0.0;
	    left = 0.0;
	    back = 0.0;
	};
     };

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
