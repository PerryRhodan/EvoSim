#pragma once



class WorldData
{

    public:

    struct physical_laws {

	double size_energy_cost; // energy cost per size per second
	double base_energy_cost; // base energy cost per second

	double maximum_energy; // maximum energy an agent can store

	double size_base_growth;
	double size_growing_energy_cost;

	double givingbirth_size_cost;
	double givingbirth_energy_cost;

	double movement_energy_cost_per_size;


	double visibility_agents;
	double visibility_food;


	physical_laws()
	{
	    size_energy_cost = 0.0;
	    base_energy_cost = 0.0;

	    maximum_energy = 0.0;

	    size_base_growth = 0.0;
	    size_growing_energy_cost = 0.0;

	    givingbirth_size_cost = 0.0;
	    givingbirth_energy_cost = 0.0;
	    
	    movement_energy_cost_per_size = 0.0;

	    visibility_agents = 0.0;
	    visibility_food = 0.0;
	}
    };

};

