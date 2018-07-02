#include "../../include/agents/SimpleAgent.h"



SimpleAgent::SimpleAgent()
{
    
    position(0, 0) = 0.0;
    position(1, 0) = 0.0;
    position(2, 0) = 0.0;
    velocity(0, 0) = 0.0;
    velocity(1, 0) = 0.0;
    velocity(2, 0) = 0.0;
    heading(0, 0) = 0.0;
    heading(1, 0) = 0.0;
    heading(2, 0) = 0.0;



    // TODO for test
    state.size = 10.0;



    // ini initial default brain weights
    std::vector<std::vector<double>> vec_weights;
    vec_weights.push_back(genes.weights_neuron_layer0_neuron0);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron1);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron2);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron3);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron4);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron5);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron6);
    brain.set_weights(vec_weights);
}

SimpleAgent::~SimpleAgent()
{

	
}

////////////////////////////////////////////

void SimpleAgent::receive_parents_traits(SimpleAgent & parent)
{
    //  Initial size and energy depends on parent.
    //  In other words, the bigger the more likely 
    //  for the children to survive?
    state.energy = parent.state.energy / 15.0;
    state.size = parent.state.size / 15.0;

    // position is obviously the same
    position = parent.position;


    // neuron weights
    // TODO


    // set up brain
    std::vector<std::vector<double>> vec_weights;
    vec_weights.push_back(genes.weights_neuron_layer0_neuron0);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron1);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron2);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron3);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron4);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron5);
    vec_weights.push_back(genes.weights_neuron_layer0_neuron6);
    brain.set_weights(vec_weights);

}

/////////////////////////////////////////////

void SimpleAgent::update(double delta)
{
    std::cout << "SimpleAgent:: update agent " << name << std::endl;
    std::cout << "SimpleAgent:: calculate neuron activity... " << std::endl;
    // neural activity to generate actions
    brain.calculate_actions(actions, state, position, heading, vision_food, vision_agents);

    print();
}

/////////////////////////////////////////////////


void SimpleAgent::print()
{
    std::cout << "SimpleAgent::print:" << std::endl;
    std::cout << "Agent:........" << name << std::endl;
    std::cout << "Size:........." << state.size << std::endl;
    std::cout << "Energy:......." << state.energy << std::endl;
    std::cout << "Age:.........." << state.age << std::endl;
    std::cout << "Position:.....[" << position(0,0) << ", " << position(1,0) << "]" << std::endl;

}













