#include "../../include/worlds/World.h"
#include "../../include/agents/Agent.h"

World::World()
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
    std::shared_ptr<Agent> agent = std::make_shared<Agent>();
    agent->name = "ONE";
    // std::shared_ptr<Agent> agent2 = std::make_shared<Agent>();
    // agent2->name = "TWO";
    // std::shared_ptr<Agent> agent3 = std::make_shared<Agent>();
    // agent3->name = "THREE";
    // std::shared_ptr<Agent> agent4 = std::make_shared<Agent>();
    // agent4->name = "FOUR";
    // std::shared_ptr<Agent> agent5 = std::make_shared<Agent>();
    // agent5->name = "FIVE";

    m_vpagents.push_back(agent);
    // m_vpagents.push_back(agent2);
    // m_vpagents.push_back(agent3);
    // m_vpagents.push_back(agent4);
    // m_vpagents.push_back(agent5);
}

World::~World()
{


}

/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void World::update(double delta)
{
    // update the world itself
    update_world(delta);
    // update the agents
    update_agents(delta);
}

////////////////////////////////////////

void World::update_world(double delta)
{
    // TODO
}

/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/////// agent reception of the world
void World::update_agent_reception(double delta, Agent & agent) const
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
void World::handle_agent_actions(double delta, Agent & agent)
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

    // give birth
    if(agent.state.pregnancy > 50.0) // TODO pregnancy required to give birth?
    {
        std::shared_ptr<Agent> offspring = std::make_shared<Agent>();
        offspring->receive_parents_traits(agent, 0.05);
        m_vpagents.push_back(offspring);
        agent.state.pregnancy -= 50.0;
    }

    // damage agains other agents on attack
    // TODO for now base on simple distance
    

}

/////// agents position and motion
void World::handle_agent_position(double delta, Agent & agent) const
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

    //std::cout << "World:: agent.velocity: [" << agent.velocity(0, 0) << ", "
	//   << agent.velocity(1, 0) << "]" << std::endl; 


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

void World::restore()
{
    int width = 10;
    int height = 10;
    for (int w=0; w<width; ++w)
    {
        for (int h=0; h<height; ++h)
        {
            tiles.at(h).at(w) = 10.0;
        }
    }

}

////////////////////////////////////////

void World::update_agents(double delta)
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

double World::get_available_food(std::shared_ptr<Agent> agent)
{
    return tiles[agent->position(0,0)][agent->position(1,0)];
}

////////////////////////////////////////////////////////////////////////

/** create and add agent with given genes and mutation mod */
void World::create_and_add_agent(AgentData::Genes genes
    , AgentData::Genes_neural_weights genes_neural_weights, double mutation_mod)
{
    std::shared_ptr<Agent> newagent = std::make_shared<Agent>(genes, genes_neural_weights);
    newagent->mutate(mutation_mod);
    m_vpagents.push_back(newagent);
}
