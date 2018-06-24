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

	/** Updates this agent, taking 
	 *  delta in seconds. */
	virtual void update(double delta);

    private:


};
