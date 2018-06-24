#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IAgent.h"

class IWorld
{
    public:
	IWorld();
	IWorld(std::string name);
	~IWorld();

	void update(double delta);

	//////////////////////////////////////

	void add_new_agent(std::shared_ptr<IAgent> agent);


    protected:
	/** overload this */
	void update_world(double detla);

    private:

	/** calls update function on all
	 *  active agents */
	void update_agents(double delta);

	//////////////////////////////////////

	/** world name */
	std::string m_str_name;
	/** vector of living agents */
	std::vector<std::shared_ptr<IAgent>> m_vpagents;
};
