//
#include "include/EvoSim.h"

// #include <Eigen/Dense>

//////////////////////////////////////////////////

EvoSim::EvoSim()
{
    
    // create service and timer for iteration calculations	
    m_pio_service = std::make_shared<boost::asio::io_service>();
    m_piteration_timer = std::make_shared<boost::asio::deadline_timer>
	    (*m_pio_service, boost::posix_time::milliseconds(100)); 
  
}

EvoSim::~EvoSim()
{

}

/////////////////////////////////////////////////////

void EvoSim::iteration()
{
    std::cout << "iterating" << std::endl;
    
    m_piteration_timer->expires_at(m_piteration_timer->expires_at() + boost::posix_time::milliseconds(100));
    m_piteration_timer->async_wait(boost::bind(&EvoSim::iteration, this));
}
	
bool EvoSim::run()
{
    m_piteration_timer->async_wait(boost::bind(&EvoSim::iteration, this));
    m_pio_service->run();
    return true;
}

//////////////////////////////////////////////////////
