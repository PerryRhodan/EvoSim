#pragma once

#include <iostream>
#include <memory>
#include <signal.h>
#include <math.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
//#include <ros/ros.h>
//#include <std_msgs/String.h>


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "worlds/World.h"

class EvoSim
{
    public:
	EvoSim();
	~EvoSim();

	bool run();
	void stop();

	static bool flag_isrunning;


    private:	

	void initialise();

	/** main iteration function */
	void iteration();

	/**  */
	void get_number_agents(int & num_alive, int & num_dead);

	/** */
	void create_new_agents(std::vector< std::shared_ptr<Agent> > current_agents,
								std::vector< std::shared_ptr<Agent> > & new_agents,
								const unsigned int num_agents,
								const double mutation_mod);
	/** */
	int calculate_score(AgentData::State state);
	

	/////////////

	// /** ros node handle */
	// ros::NodeHandle m_ros_nodehandle;

	// /** ros publisher to output simulation status */
	// ros::Publisher m_ros_publisher;

	/////////////

	/** service to run the iteration timer on */
	std::shared_ptr<boost::asio::io_service> m_pio_service;
	/** the timer for update iterations */
	std::shared_ptr<boost::asio::deadline_timer> m_piteration_timer;

	/////////////

	/** the world to be simulated, run a simple world */
	std::shared_ptr<World> m_pworld;

};
