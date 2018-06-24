#pragma once
// Interface for an agent acting in the world
//
//

#include <string>
#include <memory>


class IAgent
{
    public:
	IAgent();
	~IAgent();

    
	////////////////////////////

	void update(double delta);

    private:


};
