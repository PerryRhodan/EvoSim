#pragma once

#include <vector>
#include <iostream>
#include <math.h>

class Neuron
{
    public:
	Neuron();
	Neuron(int in);
	~Neuron();


	// calculate output based on 
	// given inputs
	// and current weights
	void calculate(std::vector<double> inputs);

	// update weights
	void update_weights(std::vector<double> neweights);

	// print current weights
	void print();

//////////////////////////////////////////////////////

	// vector of the weights for each of the inputs
	std::vector<double> weights;

	// # inputs
	int number_inputs;

	// current output value
	double output;
};
