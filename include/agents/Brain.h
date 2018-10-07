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

	void calculate_actions(AgentData::Actions & actions
			, AgentData::State state
			, Eigen::Vector2d position
			, Eigen::Vector2d heading
			, AgentData::Visibility_food vision_food
			, AgentData::Visibility_agents vision_agents);

	void set_weights(std::vector<std::vector<double>> vec_weights);

	// Neurons
	// Input:
        // size, age, energy, pregnancy
        // vision_food
        // vision_agents
        // position, x and y
	// Output:
        // give birth, move foreward, turn left, turn right, eat,
        // and attack	
	std::vector<std::unique_ptr<Neuron>> neuron_layer_hidden_0;

};
