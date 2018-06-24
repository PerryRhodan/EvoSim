#pragma once

#include <iostream>
#include <memory>
#include <signal.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ros/ros.h>
#include <std_msgs/String.h>

#include "IWorld.h"


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

	/////////////

	/** ros node handle */
	ros::NodeHandle m_ros_nodehandle;

	/** ros publisher to output simulation status */
	ros::Publisher m_ros_publisher;

	/////////////

	/** service to run the iteration timer on */
	std::shared_ptr<boost::asio::io_service> m_pio_service;
	/** the timer for update iterations */
	std::shared_ptr<boost::asio::deadline_timer> m_piteration_timer;

	/////////////

	/** the world to be simulated */
	std::shared_ptr<IWorld> m_pworld;
};
