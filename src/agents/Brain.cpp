#include "../../include/agents/Brain.h"




Brain::Brain()
{
    // set up the hidden layers
    // TODO for now have only one layer
    // 7 neurons needed for outputs
    for(int k=0; k< 7; k++) {
	neuron_layer_hidden_0.push_back(std::make_unique<Neuron>(18)); // 18 weights for each neuron
//	neuron_layer_hidden_1.push_back(std::make_unique<Neuron>());
//	neuron_layer_hidden_2.push_back(std::make_unique<Neuron>());
    } 

}

Brain::~Brain()
{


}

/////////////////////////////////////////////////////////

void Brain::set_weights(std::vector<std::vector<double>> vec_weights)
{
    if(vec_weights.size() != neuron_layer_hidden_0.size())
 	std::cout << "Brain:: set_weights: Given vec_weights.size does "
	    << "not match neuron_layer size: "
	    << vec_weights.size() << " vs " << neuron_layer_hidden_0.size()
	    << std::endl;
    // for each neuron
    for(int k=0; k<vec_weights.size(); k++)
    {
	// update weights
	neuron_layer_hidden_0[k]->update_weights( vec_weights[k] );	

	std::cout << "Brain::set_weights layer k: " << k << std::endl;
	neuron_layer_hidden_0[k]->print();
    }
}

/////////////////////////////////////////////////////////

void Brain::calculate_actions(AgentData::actions & actions
			, AgentData::state state
			, Eigen::Vector2d position
			, Eigen::Vector2d heading
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
    inputs.push_back(vision_food.center);
    inputs.push_back(vision_agents.front);
    inputs.push_back(vision_agents.right);
    inputs.push_back(vision_agents.left);
    inputs.push_back(vision_agents.back);
    inputs.push_back(vision_agents.center);
    //  = 18

    // print inputs
//    for(int k=0; k<inputs.size(); ++k)
//    {
//	std::cout << "Brain:: input[" << k << "]: " << inputs[k] << std::endl;
//    }

    /*
    std::vector<double> inputs_layer1; 
    */
    // TODO for now have only one layer
    std::vector<double> outputs;
 
    // set first layer
    for(int k=0; k<neuron_layer_hidden_0.size(); ++k)
    {
	neuron_layer_hidden_0[k]->calculate(inputs);
	outputs.push_back(neuron_layer_hidden_0[k]->output);
    }

    /*
    std::vector<double> inputs_layer2;
    // set second layer
    for(int k=0; k<neuron_layer_hidden_1.size(); ++k)
    {
	neuron_layer_hidden_1[k]->calculate(inputs_layer1);
    	inputs_layer2.push_back(neuron_layer_hidden_1[k]->output);
    }     

       // set third layer
    for(int k=0; k<neuron_layer_hidden_2.size(); ++k)
    {
	neuron_layer_hidden_2[k]->calculate(inputs_layer2);
	outputs.push_back(neuron_layer_hidden_2[k]->output);
    }
    */

    // print outputs
//    for(int k=0; k<outputs.size(); ++k)
//    {
//	std::cout << "Brain:: output[" << k << "]: " << outputs[k] << std::endl;
//    }

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

