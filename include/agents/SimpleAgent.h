#pragma once

#include "IAgent.h"
#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "Neuron.h"
#include "Brain.h"
#include "AgentData.h"

class SimpleAgent : public IAgent
{

///////////////////////////////////////////////////////////////////////////////////

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
	Eigen::Vector3d heading; //unit vector of direction

	// current sensor inputs
	AgentData::visibility_food vision_food;
	AgentData::visibility_agents vision_agents;

	// current state
	AgentData::state state;

	// current actions
	AgentData::actions actions;

	// genes
	AgentData::genes genes;

	// memory, remembers the last x events,
	// x is based on genes, and costs 
	// more energy to sustain
	//std::vector<actions> memory_actions;
	//std::vector<position> memory_position;
	//std::vector<vision_food> memory_vision_food;
	//std::vector<vision_agents> memory_vision_agents;
	//std::vector<state> memory_state;

/////////////////////////////////////////////


	Brain brain;




};
