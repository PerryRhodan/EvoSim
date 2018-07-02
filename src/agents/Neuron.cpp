#include "../../include/agents/Neuron.h"


Neuron::Neuron()
{
    number_inputs = 0;
}

Neuron::Neuron(int in)
{
    for(int i=0; i<in; ++i)
    {
	weights.push_back(0.0);
    }
    number_inputs = in;
}

Neuron::~Neuron()
{

}

void Neuron::update_weights(std::vector<double> neweights)
{
    if(weights.size() != neweights.size()) {
	std::cout << "Neuron: Given new weights vector size of " << neweights.size()
	       	<< " does not match weights vector size of " << weights.size() 
	       	<< std::endl;
	return;
    } 
    for(int i=0; i<weights.size(); ++i)
    {
	weights[i] = neweights[i];
    }
}

//////////////////////////////////////

void Neuron::calculate(std::vector<double> inputs)
{
    if(inputs.size() != weights.size()) {
	std::cout << "Neuron: Given input vector size of " << inputs.size()
	       	<< " does not match weights vector size of " << weights.size() 
	       	<< std::endl;
	return;
    }

    // sum up weighted inputs
    output = 0.0;
    for(int i=0; i<number_inputs; ++i)
    {
	output += inputs[i] * weights[i];
    }

    // activation function (leaky relu)
    if(output < 0)
	output = 0.01 * output;
}
