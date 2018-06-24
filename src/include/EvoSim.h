#pragma once

#include <iostream>
#include <functional>
#include <memory>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>



class EvoSim
{
    public:
	EvoSim();
	~EvoSim();

	void iteration();
	bool run();

    private:

	std::shared_ptr<boost::asio::io_service> m_pio_service;
	std::shared_ptr<boost::asio::deadline_timer> m_piteration_timer;

};
