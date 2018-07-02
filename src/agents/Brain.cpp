#include "../../include/agents/Brain.h"




Brain::Brain()
{


}

Brain::~Brain()
{


}

/////////////////////////////////////////////////////////

void Brain::calculate_actions(AgentData::actions & actions
			, AgentData::state state
			, Eigen::Vector3d position
			, Eigen::Vector3d heading
			, AgentData::visibility_food vision_food
			, AgentData::visibility_agents vision_agents)
{ 
    std::vector<double> inputs;
    inputs.push_back(state.size);
    inputs.push_back(state.age);
    inputs.push_back(state.energy);
    inputs.push_back(state.pregnancy);
    inputs.push_back(position(0, 0)); // TODO see if position really works here
    inputs.push_back(position(1, 0));
    inputs.push_back(heading(0, 0));
    inputs.push_back(heading(1, 0));
    inputs.push_back(vision_food.front);
    inputs.push_back(vision_food.right);
    inputs.push_back(vision_food.left);
    inputs.push_back(vision_food.back);
    inputs.push_back(vision_agents.front);
    inputs.push_back(vision_agents.right);
    inputs.push_back(vision_agents.left);
    inputs.push_back(vision_agents.back);



    
	
    // TODO return here for now, as neurons are not yet set up
    // TODO hard code some actions for testing
    std::cout << "Brain:: hardcoding some actions" << std::endl;
    actions.move_forewards = 0.4;
    actions.eat = 0.1;
    
    return;





    std::vector<double> inputs_layer1;
    // set first layer
    for(int k=0; k<neuron_layer_hidden_0.size(); ++k)
    {
	neuron_layer_hidden_0[k]->calculate(inputs);
	inputs_layer1.push_back(neuron_layer_hidden_0[k]->output);
    }

    std::vector<double> inputs_layer2;
    // set second layer
    for(int k=0; k<neuron_layer_hidden_1.size(); ++k)
    {
	neuron_layer_hidden_1[k]->calculate(inputs_layer1);
    	inputs_layer2.push_back(neuron_layer_hidden_1[k]->output);
    }     

    std::vector<double> outputs;
    // set third layer
    for(int k=0; k<neuron_layer_hidden_2.size(); ++k)
    {
	neuron_layer_hidden_2[k]->calculate(inputs_layer2);
	outputs.push_back(neuron_layer_hidden_2[k]->output);
    }


    // set actions based on outputs
    // Output:
    // give birth, move foreward, turn left, turn right, eat,
    // and attack	
    actions.give_birth = outputs[0];
    actions.move_forewards = outputs[1];
    actions.move_backwards = outputs[2];
    actions.turn_right = outputs[3];
    actions.turn_left = outputs[4];
    actions.eat = outputs[5];
    actions.attack = outputs[6]; 

}

