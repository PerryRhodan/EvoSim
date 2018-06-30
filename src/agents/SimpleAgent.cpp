#include "../../include/agents/SimpleAgent.h"



SimpleAgent::SimpleAgent()
: size(1.0)
, age(0.0)
, energy(1.0)	
{

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
    energy = parent.energy / 15.0;
    size = parent.size / 15.0;

    // position is obviously the same
    position = parent.position;
}

/////////////////////////////////////////////

void SimpleAgent::update(double delta)
{
    std::cout << "SimpleAgent:: update" << std::endl;

    // rotting
    if(!alive)
    {	
	size -= 0.1 * delta; // TODO genes effect
	return;
    }

    // establish acceleration
    // TODO

    // update position
    position += velocity * delta;
    velocity *= 0.0; // reset velocity

    // consume energy
    // base cost based on size
    energy -= size * 0.1; // TODO based on genes

    // starve off some size if out of energy, or grow in size
    size += energy * 0.1; // TODO based on genes

    // check if died, else update age
    if(size <= 0.0)
	alive = false;
    else
        age += delta;

    print();
}

/////////////////////////////////////////////////

void SimpleAgent::print()
{
    std::cout << "SimpleAgent::print:" << std::endl;
    std::cout << "Agent:........" << name << std::endl;
    std::cout << "Size:........." << size << std::endl;
    std::cout << "Energy:......." << energy << std::endl;
    std::cout << "Age:.........." << age << std::endl;
    std::cout << "Position:....." << position << std::endl;

}













