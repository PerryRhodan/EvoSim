//
#include "include/EvoSim.h"

// #include <Eigen/Dense>

//////////////////////////////////////////////////

EvoSim::EvoSim()
{    
    // create default world
    m_pworld = std::make_shared<IWorld>(); 
}

EvoSim::~EvoSim()
{

}

void EvoSim::initialise()
{
    // create service and timer for iteration calculations	
    m_pio_service = std::make_shared<boost::asio::io_service>();
    m_piteration_timer = std::make_shared<boost::asio::deadline_timer>
	    (*m_pio_service, boost::posix_time::milliseconds(100)); 
 
    // create ros publisher
    m_ros_publisher = m_ros_nodehandle.advertise<std_msgs::String>("evosim_status", 1);

    // set flag to keep this running
    flag_isrunning = true;
}

void EvoSim::stop()
{
    flag_isrunning = false;
}

/////////////////////////////////////////////////////

void EvoSim::iteration()
{
    // TODO use Boost logging
    std::cout << "iterating" << std::endl;

    // handle user commands
    // TODO

    // update world
    m_pworld->update(0.100);
 
    // publish current simulation status
    //m_ros_publisher.publish( simulation status  ); TODO

    // restart timer
    if(flag_isrunning)
    {
	m_piteration_timer->expires_at(m_piteration_timer->expires_at() + boost::posix_time::milliseconds(100));
	m_piteration_timer->async_wait(boost::bind(&EvoSim::iteration, this));
    }
 }
	
bool EvoSim::run()
{
    initialise();
    m_piteration_timer->async_wait(boost::bind(&EvoSim::iteration, this));
    m_pio_service->run();
    return true;
}

//////////////////////////////////////////////////////
