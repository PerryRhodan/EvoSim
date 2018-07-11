#include "../../include/worlds/SimpleWorld.h"
#include "../../include/agents/SimpleAgent.h"

SimpleWorld::SimpleWorld()
{
    m_str_name = "simple_world";

    // set up physical laws
    physical_laws.size_energy_cost = 0.1;
    physical_laws.size_base_growth = 1.0;

    // create tiles
    width = 10;
    height = 10;
    for (int w=0; w<width; ++w)
    {
	std::vector<double> foods;
	for (int h=0; h<height; ++h)
	{
	    foods.push_back(10.0);
	}
	tiles.push_back(foods);
    }

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
    if(!agent.alive)
	return;

    int x = agent.position(0, 0);
    int y = agent.position(1, 0);
    int x_front = x + 2*agent.heading(0, 0);
    int y_front = y + 2*agent.heading(1, 0);

    if(x_front >= width)
	x_front -= width;
    if(y_front >= height)
	y_front -= height;

    agent.vision_food.center = tiles[x][y];
    agent.vision_food.front = tiles[x_front][y_front];

}

/////// agent actions in the world
void SimpleWorld::update_agent_actions(double delta, SimpleAgent & agent)
{
    if(!agent.alive)
	return;

    // TODO handle actions effects on world and
    // agent itself

    // TODO for testing some simple food just bein available
    double food_to_eat = agent.actions.eat * 1;
    double food_available = tiles[agent.position(0, 0)][agent.position(1, 0)];
    if(food_available < food_to_eat)
	food_to_eat = food_available;
   
    std::cout << "SimpleWorld:: food_to_eat: " << food_to_eat << std::endl;

    agent.state.energy += food_to_eat; // TODO * efficiency, etc
    tiles[agent.position(0, 0)][agent.position(1, 0)] -= food_to_eat;

    std::cout << "SimpleWorld:: food_available: " << food_available << std::endl;

    // TODO apply energy costs for moving, giving birth, etc here
    // position update is handled in separate function
    

}

/////// agents position and motion
void SimpleWorld::update_agent_position(double delta, SimpleAgent & agent)
{
    if(!agent.alive)
	return;

    // update heading
    // heading(0, 0) TODO

    // establish acceleration
    agent.velocity(0, 0) += agent.heading(0, 0) * agent.actions.move_forewards
	    - agent.heading(0, 0) * agent.actions.move_backwards * agent.genes.movement_speed;
    agent.velocity(1, 0) += agent.heading(1, 0) * agent.actions.move_forewards
	    - agent.heading(1, 0) * agent.actions.move_backwards * agent.genes.movement_speed;

    std::cout << "SimpleWorld:: agent.velocity: [" << agent.velocity(0, 0) << ", "
	   << agent.velocity(1, 0) << "]" << std::endl; 



    // update position
    agent.position += agent.velocity * delta;

    // check tiles boundaries
    if(agent.position(0, 0) >= width)
	agent.position(0, 0) -= width;
    if(agent.position(1, 0) >= height)
	agent.position(1, 0) -= height;

    agent.velocity *= 0.0; // reset velocity

}

/////// agents stats
void SimpleWorld::update_agent_stats(double delta, SimpleAgent & agent)
{
    std::cout << "SimpleWorld:: delta: " << delta << std::endl;

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
	agent.state.age += delta;

    // energy consumption
    agent.state.energy -=
	(
	 agent.state.size * physical_laws.size_energy_cost +
	 physical_laws.base_energy_cost
	 ) * delta;

    // if energy smaller a percentage of size, convert size to energy
    if(agent.state.energy < agent.genes.energy_from_size_trigger * agent.state.size)
    {
	double converted = agent.genes.energy_from_size_factor * agent.state.size;
	if(converted >= agent.state.size)
	    converted = agent.state.size * 0.9;

	agent.state.size -= converted;
	agent.state.energy += converted * agent.genes.energy_from_size_factor;
    }
    
    // size growth
    double growth = physical_laws.size_base_growth * agent.genes.size_growing_factor;
    double energy_cost = growth * physical_laws.size_growing_energy_cost;            
    if(agent.state.energy > energy_cost)
    {	
	agent.state.size += growth;
	agent.state.energy -= energy_cost;
    }

    // pregnancy growth
    

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

	// remove agents that have rotten away completely
	//if(a->state.size <= 0) TODO
	// mark for removeal
    }
}


