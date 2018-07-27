#include "../../include/worlds/SimpleWorld.h"
#include "../../include/agents/SimpleAgent.h"

SimpleWorld::SimpleWorld()
{
    m_str_name = "simple_world";

    // set up physical laws
    physical_laws.base_energy_cost = 1.0;
    physical_laws.size_energy_cost = 0.1;
    physical_laws.size_base_growth = 1.0;
    physical_laws.maximum_energy = 50.0;

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
    agent->name = "ONE";
    std::shared_ptr<SimpleAgent> agent2 = std::make_shared<SimpleAgent>();
    agent2->name = "TWO";
    std::shared_ptr<SimpleAgent> agent3 = std::make_shared<SimpleAgent>();
    agent3->name = "THREE";
    std::shared_ptr<SimpleAgent> agent4 = std::make_shared<SimpleAgent>();
    agent4->name = "FOUR";
    std::shared_ptr<SimpleAgent> agent5 = std::make_shared<SimpleAgent>();
    agent5->name = "FIVE";

    m_vpagents.push_back(agent);
    m_vpagents.push_back(agent2);
    m_vpagents.push_back(agent3);
    m_vpagents.push_back(agent4);
    m_vpagents.push_back(agent5);
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
void SimpleWorld::handle_agent_actions(double delta, SimpleAgent & agent)
{
    if(!agent.alive)
    {
	// handle rotting
	double food_from_rotting = agent.state.size * 0.1 * delta; // TODO genes
	tiles[agent.position(0,0)][agent.position(1,0)] += food_from_rotting;
	return;
    }
	
    // update world based on the agents actions   
    // reduce food when eating
    double & current_tile
	    = tiles[agent.position(0, 0)][agent.position(1, 0)];
    if(agent.actions.eat > 0)
        current_tile -= agent.actions.eat;
    if(current_tile < 0) current_tile = 0;

    // damage agains other agents on attack
    // TODO for now base on simple distance
    

}

/////// agents position and motion
void SimpleWorld::handle_agent_position(double delta, SimpleAgent & agent)
{
    if(!agent.alive)
	return;
    // update heading
    Eigen::Rotation2D<double> t(agent.actions.turn_right * 0.785398
		    - agent.actions.turn_left * 0.785398); // = 45deg turns

    agent.heading = t.toRotationMatrix() * agent.heading;


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
    if(agent.position(0, 0) < 0)
	agent.position(0, 0) += width;
    if(agent.position(1, 0) >= height)
	agent.position(1, 0) -= height;
    if(agent.position(1, 0) < 0)
	agent.position(1, 0) += height;

    agent.velocity *= 0.0; // reset velocity
}


////////////////////////////////////////

void SimpleWorld::update_agents(double delta)
{
    for( auto& a : m_vpagents)
    {
	// first update agents with their current inputs and states
	a->update(delta, physical_laws, get_available_food(a));
	// handle their actions on the world, including movement
	handle_agent_position(delta, (*a) );
	handle_agent_actions(delta, (*a) );
	// finally update their current reception of the world
	update_agent_reception(delta, (*a) );


	// remove agents that have rotten away completely
	//if(a->state.size <= 0) TODO
	// mark for removeal
    }
}

double SimpleWorld::get_available_food(std::shared_ptr<SimpleAgent> agent)
{
    return tiles[agent->position(0,0)][agent->position(1,0)];
}
