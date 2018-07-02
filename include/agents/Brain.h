#pragma once

#include "AgentData.h"
#include "Neuron.h"
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include <iostream>

class Brain
{
    public:
	Brain();
	~Brain();

	void calculate_actions(AgentData::actions & actions
			, AgentData::state state
			, Eigen::Vector3d position
			, Eigen::Vector3d heading
			, AgentData::visibility_food vision_food
			, AgentData::visibility_agents vision_agents);


	// Neurons
	// Input:
        // size, age, energy, pregnancy
        // vision_food
        // vision_agents
        // position, x and y
	// Output:
        // give birth, move foreward, turn left, turn right, eat,
        // and attack	
	std::vector<std::shared_ptr<Neuron>> neuron_layer_hidden_0;
	std::vector<std::shared_ptr<Neuron>> neuron_layer_hidden_1;
	std::vector<std::shared_ptr<Neuron>> neuron_layer_hidden_2;

};
