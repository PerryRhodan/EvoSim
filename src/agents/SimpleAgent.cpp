#include "../../include/agents/SimpleAgent.h"



SimpleAgent::SimpleAgent()
{

	// TODO for test
	state.size = 10.0;

}

SimpleAgent::~SimpleAgent()
{

	
}

////////////////////////////////////////////

void SimpleAgent::receive_parents_traits(SimpleAgent & parent)
{
    //  Initial size and energy depends on parent.
    //  In other words, the bigger the more likely 
    //  for the children to survive?
    state.energy = parent.state.energy / 15.0;
    state.size = parent.state.size / 15.0;

    // position is obviously the same
    position = parent.position;
}

/////////////////////////////////////////////

void SimpleAgent::update(double delta)
{
    std::cout << "SimpleAgent:: update agent " << name << std::endl;
    std::cout << "SimpleAgent:: calculate neuron activity... " << std::endl;
    // neural activity to generate actions
    brain.calculate_actions(actions, state, position, heading, vision_food, vision_agents);

    print();
}

/////////////////////////////////////////////////


void SimpleAgent::print()
{
    std::cout << "SimpleAgent::print:" << std::endl;
    std::cout << "Agent:........" << name << std::endl;
    std::cout << "Size:........." << state.size << std::endl;
    std::cout << "Energy:......." << state.energy << std::endl;
    std::cout << "Age:.........." << state.age << std::endl;
    std::cout << "Position:.....[" << position(0,0) << ", " << position(1,0) << "]" << std::endl;

}













