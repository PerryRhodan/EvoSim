#pragma once

#include <iostream>
#include "IWorld.h"
#include "../agents/SimpleAgent.h"

class SimpleWorld : public IWorld
{
    public:
	SimpleWorld();
	~SimpleWorld();

	void update_world(double delta);

    private:
	/** update the reception of an agent, ie what an agents 
	 *  picks up based on its position in the world */
	void update_agent_reception(SimpleAgent & agent);

	/** calls update function on all
	 *  active agents, taking delta
	 *  in seconds. */
	void update_agents(double delta);

	/** vector of living agents */
	std::vector<std::shared_ptr<SimpleAgent>> m_vpagents;

};
