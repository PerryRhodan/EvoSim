#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../IAgent.h"

class IWorld
{
    public:
	IWorld();
	IWorld(std::string name);
	~IWorld();

	void update(double delta);

	//////////////////////////////////////

	void add_new_agent(std::shared_ptr<IAgent> agent);


	/** world name */
	std::string m_str_name;
	

    private:

	/** calls update function on all
	 *  active agents, taking delta
	 *  in seconds. */
	void update_agents(double delta);


    protected:
	/** update world itself */
	virtual void update_world(double detla);

	//////////////////////////////////////

	/** vector of living agents */
	std::vector<std::shared_ptr<IAgent>> m_vpagents;
};
