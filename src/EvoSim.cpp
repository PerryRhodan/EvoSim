//
#include "../include/EvoSim.h"


// define static flag to stop the sim
bool EvoSim::flag_isrunning = true;

void sighandler(int sig)
{
    std::cout << "Signal " << sig << " caught..." << std::endl;
    std::cout << "Stopping simulation..." << std::endl;
    EvoSim::flag_isrunning = false;
}


//////////////////////////////////////////////////

EvoSim::EvoSim()
{    
    // create default world
    //m_pworld = std::make_shared<IWorld>(); TODO
    m_pworld = std::make_shared<SimpleWorld>();
    std::cout << "EvoSim using world: " << m_pworld->m_str_name << std::endl;
}

EvoSim::~EvoSim()
{

}

void EvoSim::initialise()
{
    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);
 
    // create service and timer for iteration calculations	
    m_pio_service = std::make_shared<boost::asio::io_service>();
    m_piteration_timer = std::make_shared<boost::asio::deadline_timer>
	    (*m_pio_service, boost::posix_time::milliseconds(100)); 
 
    // create ros publisher
    m_ros_publisher = m_ros_nodehandle.advertise<std_msgs::String>("evosim_status", 1);
}

void EvoSim::stop()
{
    EvoSim::flag_isrunning = false;
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
    if(EvoSim::flag_isrunning)
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
