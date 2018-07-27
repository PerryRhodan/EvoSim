#pragma once

#include <iostream>
#include "IWorld.h"
#include "../agents/SimpleAgent.h"
#include <Eigen/Geometry>
#include "WorldData.h"


class SimpleWorld : public IWorld
{




//////////////////////////////////////////////////////////////////////////

    public:
	SimpleWorld();
	~SimpleWorld();

	void update_world(double delta);

	////////////////////////////////////////////

	WorldData::physical_laws physical_laws;

	// tile width and height
	int width;
	int height;
	std::vector<std::vector<double> > tiles; // tiles of food

    private:
	/** update the reception of an agent, ie what an agents 
	 *  picks up based on its position in the world */
	void update_agent_reception(double delta, SimpleAgent & agent);

	void handle_agent_position(double delta, SimpleAgent & agent);
	void handle_agent_actions(double delta, SimpleAgent & agent);

	/** calls update function on all
	 *  active agents, taking delta
	 *  in seconds. */
	void update_agents(double delta);

	/** returns the available food from the given agents position */
	double get_available_food(std::shared_ptr<SimpleAgent> agent);

	/** vector of living agents */
	std::vector<std::shared_ptr<SimpleAgent>> m_vpagents;

};
