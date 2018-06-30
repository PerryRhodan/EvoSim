#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "../agents/IAgent.h"

class IWorld
{
    public:
	IWorld();
	IWorld(std::string name);
	~IWorld();

	void update(double delta);

	//////////////////////////////////////


	/** world name */
	std::string m_str_name;
	

    private:


    protected:
	/** update world itself */
	virtual void update_world(double detla);

	//////////////////////////////////////

};
