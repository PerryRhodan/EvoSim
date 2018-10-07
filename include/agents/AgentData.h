#pragma once
#include <vector>
#include <random>

class AgentData
{
    public:
    // the food values of the areas around the agent
    struct Visibility_food {
		double front;
		double right;
		double left;
		double back;
     	double center;

     	Visibility_food() {
			front = 0.0;
			right = 0.0;
			left = 0.0;
			back = 0.0;
			center = 0.0;
		};
    };


    // the sizes of other agents in the areas around this agent
    struct Visibility_agents {
		double front;
		double right;
		double left;
		double back;
		double center;

		Visibility_agents() {
			front = 0.0;
			right = 0.0;
			left = 0.0;
			back = 0.0;
			center = 0.0;
		};
    };

     // actions the agent will do based on neuron outpus
    struct Actions {
		double give_birth;
        double move_forewards;
		double move_backwards;
		double turn_right;
		double turn_left;	
		double eat;
		double attack;

		Actions() {
			give_birth = 0.0;
			move_forewards = 0.0;
			move_backwards = 0.0;
			turn_right = 0.0;
			turn_left = 0.0;
			eat = 0.0;
			attack = 0.0;
		};
    };

    // current state of the agent
    struct State {
    	// current size
		double size;
		// current age
		double age;
		// current energy
		double energy;
		// pregnancy value, maybe need better name
		// Basically the readiness to give birth
		double pregnancy;

		State() {
			size = 0.0;
			age = 0.0;
			energy = 0.0;
			pregnancy = 0.0;
		};
    };

    // Genes modified in mutation
    // The values should all be [0..1]
    // 
    struct Genes {
		double size_growing_energy_cost;
		double size_growing_factor;
		double size_growing_efficiency;
		double pregnancy_growth;
		double movement_speed;
		double movement_energy_efficiency;
		double movement_energy_size_impact;
		double givingbirth_energy_efficiency;
		double givingbirth_size_cost;

		double energy_from_size_trigger;// percentage of size of energy remaining,
							// after which size is converted into energy
		double energy_from_size_factor;
		double energy_from_size_efficiency;



		// learning values below make up a cost function
		// the agent evaluates its current neural weights
		// against
		// TODO 

		Genes()
		{
    	    size_growing_energy_cost = 0.0;
    	    size_growing_factor = 0.0;
    	    size_growing_efficiency = 0.0;
	    	pregnancy_growth = 0.0;
    	    movement_speed = 0.0;
    	    movement_energy_efficiency = 0.0;
			movement_energy_size_impact = 0.0;
			givingbirth_energy_efficiency = 0.0;
			givingbirth_size_cost = 0.0;
			energy_from_size_trigger = 0.0;
			energy_from_size_factor = 0.0;
			energy_from_size_efficiency = 0.0;
		}

		void randomize()
		{
			size_growing_energy_cost = random_double();
			size_growing_factor = random_double();
			size_growing_efficiency = random_double();
			pregnancy_growth = random_double();
			movement_speed = random_double();
			movement_energy_efficiency = random_double();
			movement_energy_size_impact = random_double();
			givingbirth_energy_efficiency = random_double();
			givingbirth_size_cost = random_double();
			energy_from_size_trigger = random_double();
			energy_from_size_factor = random_double();
			energy_from_size_efficiency = random_double();
		}

		double random_double()
		{
			std::random_device rd;
			std::default_random_engine dre(rd());
			std::uniform_int_distribution<int> uniform_dist(1,100);
			return ((double)uniform_dist(dre))/100.0;
		}

		double random_double(double limit)
		{
			double ran = 1.0 - (2.0 * random_double());
			if(ran > limit)
				ran = limit;
			else if(ran < limit)
				ran = -limit;
			return ran;
		}
     
		void mutate(double mutation_mod)
		{
			size_growing_energy_cost 		*= 1.0 + random_double(mutation_mod);
			size_growing_factor 			*= 1.0 + random_double(mutation_mod);
			size_growing_efficiency 		*= 1.0 + random_double(mutation_mod);
			pregnancy_growth 				*= 1.0 + random_double(mutation_mod);
			movement_speed 					*= 1.0 + random_double(mutation_mod);
			movement_energy_efficiency 		*= 1.0 + random_double(mutation_mod);
			movement_energy_size_impact 	*= 1.0 + random_double(mutation_mod);
			givingbirth_energy_efficiency 	*= 1.0 + random_double(mutation_mod);
			givingbirth_size_cost 			*= 1.0 + random_double(mutation_mod);
			energy_from_size_trigger 		*= 1.0 + random_double(mutation_mod);
			energy_from_size_factor 		*= 1.0 + random_double(mutation_mod);
			energy_from_size_efficiency 	*= 1.0 + random_double(mutation_mod);
		}
    };

    // Genes used as weights in the brain
    // These can be adjusted throughout the lifetime
    // of the agent, ie learning!
    struct Genes_neural_weights
    {
		// 7 neurons in first layer (they will contain 18 weights each for the inputs)
		std::vector<double> weights_neuron_layer0_neuron0;
		std::vector<double> weights_neuron_layer0_neuron1;
     	std::vector<double> weights_neuron_layer0_neuron2;
		std::vector<double> weights_neuron_layer0_neuron3;
		std::vector<double> weights_neuron_layer0_neuron4;
		std::vector<double> weights_neuron_layer0_neuron5;
		std::vector<double> weights_neuron_layer0_neuron6;

		Genes_neural_weights()
		{
			// add 18 default values for each of the neurons weights
			for(int k=0; k<18; ++k)
			{
				weights_neuron_layer0_neuron0.push_back(0.0);
				weights_neuron_layer0_neuron1.push_back(0.0);
				weights_neuron_layer0_neuron2.push_back(0.0);
				weights_neuron_layer0_neuron3.push_back(0.0);
				weights_neuron_layer0_neuron4.push_back(0.0);
				weights_neuron_layer0_neuron5.push_back(0.0);
				weights_neuron_layer0_neuron6.push_back(0.0);
			}
		}
	
		void randomize() {
			
			for(int k=0; k<18; ++k)
			{
				weights_neuron_layer0_neuron0[k] = random_double();
				weights_neuron_layer0_neuron1[k] = random_double();
				weights_neuron_layer0_neuron2[k] = random_double();
				weights_neuron_layer0_neuron3[k] = random_double();
				weights_neuron_layer0_neuron4[k] = random_double();
				weights_neuron_layer0_neuron5[k] = random_double();
				weights_neuron_layer0_neuron6[k] = random_double();
			}
		}

		double random_double()
		{
			std::random_device rd;
			std::default_random_engine dre(rd());
			std::uniform_int_distribution<int> uniform_dist(1,100);
			return ((double)uniform_dist(dre))/100.0;
		}

		void mutate(double mutation_mod)
		{
			// TODO
		}
    };

};
