#pragma once

#include <iostream>
#include "../agents/Agent.h"

#include "WorldData.h"


class World
{

//////////////////////////////////////////////////////////////////////////

    public:
	World();
	~World();

	void update(double delta);

	void restore();

	/** create and add agent with given genes and mutation mod */
	void create_and_add_agent(AgentData::Genes genes
		, AgentData::Genes_neural_weights genes_neural_weights, double mutation_mod);

	////////////////////////////////////////////

	/** world name */
	std::string m_str_name;
	/** physical laws of this world */
	WorldData::Physical_laws physical_laws;

	// tile width and height
	int width;
	int height;
	std::vector<std::vector<double> > tiles; // tiles of food

	
	/** agents */
	std::vector<std::shared_ptr<Agent>> m_vpagents;

    private:
	void update_world(double delta);


	/** update the reception of an agent, ie what an agents 
	 *  picks up based on its position in the world */
	void update_agent_reception(double delta, Agent & agent) const;
	/** */
	void handle_agent_position(double delta, Agent & agent) const;
	/** */
	void handle_agent_actions(double delta, Agent & agent);
	/** calls update function on all active agents, taking delta
	 *  in seconds. */
	void update_agents(double delta);

	/** returns the available food from the given agents position */
	double get_available_food(std::shared_ptr<Agent> agent);



};
