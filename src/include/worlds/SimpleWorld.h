#pragma once

#include <iostream>
#include "IWorld.h"

class SimpleWorld : public IWorld
{
    public:
	SimpleWorld();
	~SimpleWorld();

	void update_world(double delta);	

};
