#include "../../include/worlds/IWorld.h"


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

/////////////////////////////////////////////

void IWorld::update(double delta)
{
    update_world(delta);
}


void IWorld::update_world(double delta)
{
    // default world does nothing
    std::cout << "default world update" << std::endl;
}

/////////////////////////////////////////////

