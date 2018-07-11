#pragma once

#include <iostream>
#include "IWorld.h"
#include "../agents/SimpleAgent.h"

class SimpleWorld : public IWorld
{

    struct physical_laws {

	double size_energy_cost; // energy cost per size per second
	double base_energy_cost; // base energy cost per second

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

	    size_base_growth = 0.0;
	    size_growing_energy_cost = 0.0;

	    givingbirth_size_cost = 0.0;
	    givingbirth_energy_cost = 0.0;
	    
	    movement_energy_cost_per_size = 0.0;

	    visibility_agents = 0.0;
	    visibility_food = 0.0;
	}
    };





//////////////////////////////////////////////////////////////////////////

    public:
	SimpleWorld();
	~SimpleWorld();

	void update_world(double delta);

	////////////////////////////////////////////

	physical_laws physical_laws;

	// tile width and height
	int width;
	int height;
	std::vector<std::vector<double> > tiles; // tiles of food

    private:
	/** update the reception of an agent, ie what an agents 
	 *  picks up based on its position in the world */
	void update_agent_reception(double delta, SimpleAgent & agent);

	void update_agent_position(double delta, SimpleAgent & agent);
	void update_agent_actions(double delta, SimpleAgent & agent);
	void update_agent_stats(double delta, SimpleAgent & agent);

	/** calls update function on all
	 *  active agents, taking delta
	 *  in seconds. */
	void update_agents(double delta);

	/** vector of living agents */
	std::vector<std::shared_ptr<SimpleAgent>> m_vpagents;

};
