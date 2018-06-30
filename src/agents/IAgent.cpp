#include "../../include/agents/IAgent.h"




IAgent::IAgent()
: alive(true)
, name("default")
{

}

IAgent::~IAgent()
{

}

/////////////////////////////////////////////////////

void IAgent::update(double delta)
{
    // default agent does nothing
}


