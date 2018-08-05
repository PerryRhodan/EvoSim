#include "../../include/agents/Agent.h"



Agent::Agent() :
name("default"),
alive(true)
{
    
    position(0, 0) = 0.0;
    position(1, 0) = 0.0;
    velocity(0, 0) = 0.0;
    velocity(1, 0) = 0.0;
    heading(0, 0) = 1.0; // face up by default
    heading(1, 0) = 0.0;


    // TODO for test
    state.size = 10.0;
    state.energy = 10.0;
    genes.randomize();
    genes_neural_weights.randomize();

    // ini initial default brain weights
    std::vector<std::vector<double>> vec_weights;
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron0);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron1);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron2);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron3);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron4);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron5);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron6);
    brain.set_weights(vec_weights);
}

Agent::~Agent()
{

	
}

////////////////////////////////////////////

void Agent::receive_parents_traits(Agent & parent)
{
    //  Initial size and energy depends on parent.
    //  In other words, the bigger the more likely 
    //  for the children to survive?
    state.energy = parent.state.energy / 15.0;
    state.size = parent.state.size / 15.0;

    // position is obviously the same
    position = parent.position;


    // neuron weights
    genes.randomize();

    // set up brain
    std::vector<std::vector<double>> vec_weights;
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron0);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron1);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron2);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron3);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron4);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron5);
    vec_weights.push_back(genes_neural_weights.weights_neuron_layer0_neuron6);
    brain.set_weights(vec_weights);

}

/////////////////////////////////////////////

void Agent::update(double delta, WorldData::physical_laws laws
					, double available_food)
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Agent:: available_food: " << available_food << std::endl;
 

    // rotting
    if(!alive)
    {	
        state.size -= 0.1 * delta; // TODO genes effect
        return;
    }	

    // aging and dying
    if(state.energy <= 0.0)
	    alive = false;
    else
	    state.age += delta;

    // neural activity to generate actions
    brain.calculate_actions(actions, state, position, heading, vision_food, vision_agents);

    // TODO for testing some simple food just bein available
    double food_to_eat = actions.eat * 1;
    if(available_food < food_to_eat)
	    food_to_eat = available_food;
   
    state.energy += food_to_eat; // TODO * efficiency, etc

    // energy consumption
    state.energy -=
	(
        state.size * laws.size_energy_cost +
        laws.base_energy_cost
	) * delta;

    // if energy smaller a percentage of size, convert size to energy
    if(state.energy < genes.energy_from_size_trigger * state.size)
    {
        double converted = genes.energy_from_size_factor * state.size;
        if(converted >= state.size)
            converted = state.size * 0.9;

        state.size -= converted;
    	state.energy += converted * genes.energy_from_size_efficiency;
    }
    
    // size growth
    double growth = laws.size_base_growth * genes.size_growing_factor;
    double energy_cost = growth * laws.size_growing_energy_cost;            
    if(state.energy > energy_cost)
    {	
        state.size += growth * genes.size_growing_efficiency;
        state.energy -= energy_cost;
    }

    // cap energy to max
    if(state.energy > laws.maximum_energy)
    	state.energy = laws.maximum_energy;

    // pregnancy growth
    




    print();

}

/////////////////////////////////////////////////


void Agent::print()
{
    std::cout << "Agent::print:" << std::endl;
    std::cout << "Name:........" << name << std::endl;
    std::cout << "Size:........." << state.size << std::endl;
    std::cout << "Energy:......." << state.energy << std::endl;
    std::cout << "Age:.........." << state.age << std::endl;
    std::cout << "Position:.....[" << position(0,0) << ", " << position(1,0) << "]" << std::endl;
}













