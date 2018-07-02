#include "../../include/worlds/SimpleWorld.h"
#include "../../include/agents/SimpleAgent.h"

SimpleWorld::SimpleWorld()
{
    m_str_name = "simple_world";

    // set up physical laws
    physical_laws.size_energy_cost = 0.001;
    physical_laws.size_base_growth = 1.0;



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

/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/////// agent reception of the world
void SimpleWorld::update_agent_reception(double delta, SimpleAgent & agent)
{
    std::cout << "update simple agent reception" << std::endl;
    // TODO handle reception of food and agents

}

/////// agent actions in the world
void SimpleWorld::update_agent_actions(double delta, SimpleAgent & agent)
{
    // TODO handle actions effects on world and
    // agent itself

    // TODO for testing some simple food just bein available
    agent.state.energy += agent.actions.eat * 1.0;

    // TODO apply energy costs for moving, giving birth, etc here


}

/////// agents position and motion
void SimpleWorld::update_agent_position(double delta, SimpleAgent & agent)
{
    // update heading
    // heading(0, 0) TODO

    // establish acceleration
    agent.velocity(0, 0) += agent.heading(0, 0) * agent.actions.move_forewards
	    - agent.heading(0, 0) * agent.actions.move_backwards; // TODO * gene_speed
    agent.velocity(1, 0) += agent.heading(1, 0) * agent.actions.move_forewards
	    - agent.heading(1, 0) * agent.actions.move_backwards;

    // update position
    agent.position += agent.velocity * delta;
    agent.velocity *= 0.0; // reset velocity

}

/////// agents stats
void SimpleWorld::update_agent_stats(double delta, SimpleAgent & agent)
{ 
    // rotting
    if(!agent.alive)
    {	
	agent.state.size -= 0.1 * delta; // TODO genes effect
	return;
    }

    // aging and dying
    if(agent.state.energy <= 0.0)
	agent.alive = false;
    else
	agent.state.age =+ delta;

    // energy consumption
    agent.state.energy -=
	(
	 agent.state.size * physical_laws.size_energy_cost * delta
	 );

    // if energy smaller a percentage of size, convert size to energy
    if(agent.state.energy < agent.genes.energy_from_size_trigger * agent.state.size)
    {
	double converted = agent.genes.energy_from_size_factor * agent.state.size;
	agent.state.size -= converted;
	agent.state.energy += converted;
    }
    
    // size growth
    double growth = physical_laws.size_base_growth * agent.genes.size_growing_factor;
    double energy_cost = growth * physical_laws.size_growing_energy_cost;            
    if(agent.state.energy > energy_cost)
    {	
	agent.state.size += growth;
	agent.state.energy -= energy_cost;
    }

}

////////////////////////////////////////

void SimpleWorld::update_agents(double delta)
{
    for( auto& a : m_vpagents)
    {
	update_agent_position(delta, (*a) );
	update_agent_actions(delta, (*a) );
	update_agent_reception(delta, (*a) );
	update_agent_stats(delta, (*a) );
	a->update(delta);

	//if(a->state.size <= 0)
	// mark for removeal
    }
}


