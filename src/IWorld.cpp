#include "include/IWorld.h"


IWorld::IWorld()
{
    m_str_name = "default";
}

IWorld::IWorld(std::string name)
{
    m_str_name = name;
}

IWorld::~IWorld()
{

}

////////////////////////////////////////////

void IWorld::add_new_agent(std::shared_ptr<IAgent> agent)
{
    m_vpagents.push_back( agent );
}

/////////////////////////////////////////////

void IWorld::update(double delta)
{
    update_agents(delta);
    update_world(delta);
}

void IWorld::update_agents(double delta)
{
    for (std::vector<std::shared_ptr<IAgent>>::iterator it = m_vpagents.begin();
		    it != m_vpagents.end(); ++it)
    {
	(*it)->update(delta);
    }
}

void IWorld::update_world(double delta)
{
    // default world does nothing
}

/////////////////////////////////////////////

