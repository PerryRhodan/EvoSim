#include "../../include/worlds/SimpleWorld.h"
#include "../../include/agents/SimpleAgent.h"

SimpleWorld::SimpleWorld()
{
    m_str_name = "simple_world";

    // TODO for testing add an agent here
    std::shared_ptr<SimpleAgent> agent = std::make_shared<SimpleAgent>();
    m_vpagents.push_back(agent);
}

SimpleWorld::~SimpleWorld()
{


}

////////////////////////////////////////

void SimpleWorld::update_world(double delta)
{
    std::cout << "update simple world" << std::endl;


    // update agents
    update_agents(delta);
}

/////////////////////////////////////////

void SimpleWorld::update_agent_reception(SimpleAgent & agent)
{
    std::cout << "update simple agent reception" << std::endl;


}

void SimpleWorld::update_agents(double delta)
{
    for( auto& a : m_vpagents)
    {
	a->update(delta);
	update_agent_reception( (*a) );
    }
}


