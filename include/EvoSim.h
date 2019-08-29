#pragma once

#include <iostream>
#include <memory>
#include <signal.h>
#include <math.h>
#include <thread>
#include <chrono>

//#include <ros/ros.h>
//#include <std_msgs/String.h>


#include "worlds/World.h"
#include "Display.h"


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

	/////////////

	/** the world to be simulated, run a simple world */
	std::shared_ptr<World> m_pworld;



	Display display;

};
