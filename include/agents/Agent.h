#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include "Neuron.h"
#include "Brain.h"
#include "AgentData.h"
#include "../worlds/WorldData.h"

class Agent
{

///////////////////////////////////////////////////////////////////////////////////

    public:
	Agent();
	~Agent();

	// For now just assume one agent gives birth to a new
	// one, and does not need a mating partner
	void receive_parents_traits(Agent & parent);

	// Update with given physical laws of the world
	void update(double delta, WorldData::physical_laws laws
					, double available_food);
	void print();

//////////////////////////////////////////////

	// the agents name, built up and modified from parent name
	std::string name;
	// flag to indicate if this agent is still alive
	bool alive;	

	// position and motion
	Eigen::Vector2d position;
	Eigen::Vector2d velocity;
	Eigen::Vector2d heading; //unit vector of direction


	// current sensor inputs
	AgentData::visibility_food vision_food;
	AgentData::visibility_agents vision_agents;

	// current state
	AgentData::state state;

	// current actions
	AgentData::actions actions;

	// genes
	AgentData::genes genes;
	AgentData::genes_neural_weights genes_neural_weights;


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
